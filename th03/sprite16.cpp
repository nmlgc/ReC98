/* ReC98
 * -----
 * SPRITE16 display calls
 */

#pragma option -zCSHARED -k-

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "decomp.hpp"
#include "master.hpp"
#include "libs/sprite16/sprite16.h"
#include "th03/sprite16.hpp"

void pascal sprite16_sprites_commit(void)
{
	sprite16_sprites_copy_page(1);
	graph_accesspage(0);
	_AH = SPRITE16_GENERATE_ALPHA;
	geninterrupt(SPRITE16);
}

// Register variables; declare them as local ones and remove this block when
// porting away from 16-bit x86
#define sprite_offset_local (_DI)
#define putpos_left static_cast<int>(_DX)
#define putpos_right static_cast<int>(_BX)
#define clip_left static_cast<int>(_SI)
#define clip_right static_cast<int>(_CX)
#define put_w_words (_AL)
#define should_draw_column (_SI)

#define SETUP_VARS(left, top, sprite_offset) \
	sprite_offset_local = sprite_offset; \
	putpos_left = left; \
	put_w_words = sprite16_put_w.v; \
	_BH ^= _BH; /* upper 8 bits of putpos_right */ \
	static_cast<char>(putpos_right) = put_w_words; \
	putpos_right <<= 4; \
	putpos_right += putpos_left; \
	clip_left = sprite16_clip_left; \
	clip_right = sprite16_clip_right;

#define CALL_PUT(left, top, put_w_words, sprite_offset) \
	_AH = SPRITE16_PUT; \
	_DX = putpos_left; \
	_BX = top; \
	static_cast<int>(_BX) >>= 1; \
	_AL = put_w_words; \
	_CX = sprite16_put_h; \
	_DI = sprite_offset_local; \
	geninterrupt(SPRITE16); \

#define CLIP_LEFT_PART \
	do { \
		putpos_left += 16; \
		put_w_words--; \
		if(FLAGS_ZERO) { \
			return; \
		} \
		sprite_offset_local += (16 / 8); \
	} while(putpos_left < clip_left);

#define CLIP_RIGHT_PART \
	do { \
		putpos_right -= 16; \
		put_w_words--; \
		if(FLAGS_ZERO) { \
			return; \
		} \
	} while(putpos_right >= clip_right);

void pascal sprite16_put(screen_x_t left, screen_y_t top, int sprite_offset)
{
	SETUP_VARS(left, top, sprite_offset);
	if(putpos_right < clip_right) {
		if(putpos_left >= clip_left) {
put:
			CALL_PUT(putpos_left, top, put_w_words, sprite_offset_local);
			return;
		} else if(putpos_right < clip_left) {
			return;
		}
		// Sprite starts left of `clip_left`
		CLIP_LEFT_PART;
		goto put;
	} else if(putpos_left >= clip_right) {
		return;
	}
	// Sprite ends right of `clip_right`
	CLIP_RIGHT_PART;
	goto put;
}

#pragma codestring "\x90"

void pascal sprite16_putx(
	screen_x_t left, screen_y_t top, int sprite_offset, sprite16_put_func_t func
)
{
	SETUP_VARS(left, top, sprite_offset);
	if(putpos_right < clip_right) {
		if(putpos_left >= clip_left) {
put:
			_AH = SPRITE16_PUT;
			_DX = putpos_left;
			_BX = top;
			static_cast<int>(_BX) >>= 1;
			_AL = put_w_words;
			_CX = sprite16_put_h;
			_DI = sprite_offset_local;
			while(1) {
				should_draw_column = func;
				geninterrupt(SPRITE16);
				should_draw_column--;
				if(FLAGS_ZERO) {
					return;
				}
				_BX += _CX;
				_asm cmp	bx, SPRITE16_RES_Y;
				_asm jge	end;
			}
		} else if(putpos_right < clip_left) {
			return;
		}
		// Sprite starts left of `clip_left`
		CLIP_LEFT_PART;
		goto put;
	} else if(putpos_left >= clip_right) {
		return;
	}
	// Sprite ends right of `clip_right`
	CLIP_RIGHT_PART;
	goto put;
end:
}

#pragma codestring "\x90"

void pascal sprite16_put_noclip(
	screen_x_t left, screen_y_t top, int sprite_offset
)
{
	// A completely useless SETUP_VARS variant without the `put_w_words`
	// assignment, which actually makes it incorrect...
	sprite_offset_local = sprite_offset;
	putpos_left = left;
	_BH ^= _BH; /* upper 8 bits of putpos_right */
	static_cast<char>(putpos_right) = put_w_words;
	putpos_right <<= 4;
	putpos_right += putpos_left;

	CALL_PUT(putpos_left, top, sprite16_put_w.v, sprite_offset_local);
}

}

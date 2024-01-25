#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/math/overlap.hpp"
#include "th02/main/playfld.hpp"
#include "th02/main/scroll.hpp"
#include "th02/main/tile/tile.hpp"
#include "th02/main/player/player.hpp"
#include "th02/main/player/bomb.hpp"
#include "th02/sprites/bombpart.h"

extern int bomb_frame;
extern point_t bomb_circle_center;
extern int bomb_circle_frame;
extern bool16 bomb_circle_done;

extern bool16 (near pascal *near playchar_bomb_func)(void);

// Function ordering fails
// -----------------------

// These assume the GRCG to be set to RMW mode, with a tile in the intended
// color.
void pascal near bomb_circle_point_put(screen_x_t left, screen_y_t top);
void pascal near bomb_particle_put_8(screen_x_t left, screen_y_t top, int cel);
void pascal near bomb_smear_put_8(screen_x_t left, screen_y_t column_bottom);
void pascal near bomb_bft_8tiles_put_8(
	screen_x_t left, screen_y_t top, dots8_t dots
);
// -----------------------

void near bomb_circle_update_and_render(void)
;

void pascal near bomb_reimu_a(void);
void pascal near bomb_reimu_c(void);
void pascal near bomb_reimu_b(void);

void near bomb_update_and_render(void)
{
	bool16 done = false;

	if(!bombing) {
		return;
	}
	bomb_frame++;
	if(bomb_circle_done == false) {
		if(bomb_frame <= BOMB_CIRCLE_FRAMES) {
			bomb_circle_update_and_render();
		} else if(bomb_circle_frame == 0) {
			bomb_frame = 0;
			bomb_circle_done++;
		}
	} else if(bomb_circle_done == true) {
		done = playchar_bomb_func();
	}
	if(done) {
		bombing = false;
		player_invincible_via_bomb = false;
		player_invincibility_time = 70;
		palette_100();
	}
}

// ZUN bloat: Needed to circumvent 16-bit promotion in a single comparison.
inline pixel_delta_8_t bomb_particle_h(void) {
	return BOMB_PARTICLE_H;
}

void pascal near bomb_circle_point_put(screen_x_t left, screen_y_t top)
{
	#define vram_top          	static_cast<vram_y_t>(_DX)
	#define first_bit_mirrored	_DX

	register const bomb_particle_dots_t near* sprite;
	pixel_delta_8_t y;
	unsigned int first_bit;

	if(!overlap_xy_ltrb_lt_gt(
		left, top,
		(PLAYFIELD_LEFT - BOMB_PARTICLE_W),
		(PLAYFIELD_TOP  - BOMB_PARTICLE_H),
		PLAYFIELD_RIGHT,
		PLAYFIELD_BOTTOM
	)) {
		return;
	}

	_ES = SEG_PLANE_B;
	vram_top = scroll_screen_y_to_vram(vram_top, top);
	_BX = left;
	vram_offset_shift_fast_asm(di, bx, vram_top);

	// ZUN bloat: Turbo C++ 4.0J would otherwise only ever generate an 8-bit
	// AND.
	asm { and	bx, BYTE_MASK; }

	first_bit = _BX;
	first_bit_mirrored = (sizeof(dots16_t) * BYTE_DOTS);

	// ZUN bloat: first_bit_mirrored -= _BX;
	asm { sub	dx, bx; }

	sprite = sBOMB_CIRCLE;
	y = 0;
	do {
		// ZUN bloat: A manual 16-bit right rotation. Turbo C++ 4.0J has
		// intrinsics for that, which compile into a single ROR instruction:
		//
		// 	*reinterpret_cast<dots16_t __es *>(vo) = __rotr__(
		// 		*sprite, first_bit
		// );
		asm { xor	ax, ax; }
		_AL = *sprite;
		asm { mov	bx, ax; }
		_CX = first_bit;
		_BX >>= _CL;
		asm { mov	cx, dx; }
		_AX <<= _CL;
		asm { add	ax, bx; }
		*reinterpret_cast<dots16_t __es *>(_DI) = _AX;

		vram_offset_add_and_roll(_DI, ROW_SIZE);
		sprite++;
		y++;
	} while(y < bomb_particle_h());

	#undef first_bit_mirrored
	#undef vram_top
}

void pascal near bomb_particle_put_8(screen_x_t left, screen_y_t top, int cel)
{
	#define _DI	static_cast<vram_offset_t>(_DI)

	_ES = SEG_PLANE_B;
	_DX = scroll_screen_y_to_vram(static_cast<vram_y_t>(_DX), top);
	vram_offset_shift_fast_asm(di, left, _DX);

	// ZUN bloat: _SI  = &sBOMB_PARTICLES[cel];
	_SI = reinterpret_cast<uint16_t>(&sBOMB_PARTICLES[0][0]);
	_AX = (cel * sizeof(sBOMB_PARTICLES[0]));
	asm { add	si, ax; }

	_CX = BOMB_PARTICLE_H;
	loop: {
		asm { movsb; }
		vram_offset_add_and_roll(
			_DI, (ROW_SIZE - (BOMB_PARTICLE_W / BYTE_DOTS))
		);
		asm { loop loop; }
	}

	#undef _DI
}

void pascal near bomb_smear_put_8(screen_x_t left, screen_y_t column_bottom_)
{
	#define y            	static_cast<vram_y_t>(_DX)
	#define column_bottom	static_cast<screen_y_t>(_BX)

	_ES = SEG_PLANE_B;
	y = scroll_screen_y_to_vram(y, PLAYFIELD_TOP);
	vram_offset_shift_fast_asm(di, left, y);

	// ZUN bloat: &sBOMB_CIRCLE[BOMB_PARTICLE_H / 2];
	register const bomb_particle_dots_t near* sprite = &sBOMB_CIRCLE[0];
	sprite += ((BOMB_PARTICLE_H / 2) * sizeof(bomb_particle_dots_t));

	_CX = (BOMB_PARTICLE_H / 2);
	y = PLAYFIELD_TOP;
	column_bottom = column_bottom_;
	_AL = static_cast<bomb_particle_dots_t>(-1);
	loop: {
		*reinterpret_cast<bomb_particle_dots_t __es *>(_DI) = _AL;
		vram_offset_add_and_roll(_DI, ROW_SIZE);
		y++;

		// ZUN bloat: if(y >= column_bottom)
		asm { cmp	dx, bx; }
		asm { jl 	still_in_column; }

		// We're in the bottom part; switch to drawing the sprite rather than
		// the constant 0xFF set before the loop.
		_AL = *sprite++;
		_CX--;

	still_in_column:
		// ZUN bloat: do { … } while(_CX > 0);
		asm { cmp	cx, 0; }
		asm { ja 	loop; }
	}

	#undef column_bottom
	#undef y
}

void pascal near bomb_bft_tile_put_8(vram_offset_t vo)
{
	_CX = TILE_H;
	_DI = vo;
	_BX = static_cast<dots_t(TILE_W)>(-1);
	loop: {
		*reinterpret_cast<dots_t(TILE_W) __es *>(_DI) = _BX;
		vram_offset_add_and_roll(_DI, ROW_SIZE);
		asm { loop loop; }
	}
}

// Renders [dots] from BOMBS.BFT as a 8×1 row of 16×16 blocks, covering a total
// size of 128×16 pixels, to (⌊left/8⌋*8, top). Each tile is filled with the
// current GRCG tile if its corresponding bit is 1, or skipped otherwise.
// Conceptually identical to the tiles_bb_*() functions from TH04 and TH05.
void pascal near bomb_bft_8tiles_put_8(
	screen_x_t left, screen_y_t top, dots8_t dots
)
{
	#define tile_cur	static_cast<dots8_t>(_AL)
	#define tiles   	static_cast<dots8_t>(_AH)

	_ES = SEG_PLANE_B;
	_DX = scroll_screen_y_to_vram(static_cast<vram_y_t>(_DX), top);
	vram_offset_shift_fast_asm(di, left, _DX);
	tile_cur = 0x80;
	tiles = dots;
	asm { xor	si, si; }
	do {
		if(tile_cur & tiles) {
			bomb_bft_tile_put_8(_DI);
		}
		tile_cur >>= 1;
		_DI += TILE_VRAM_W;
		_SI++;
	} while(_SI < BYTE_DOTS);

	#undef tiles
	#undef tile_cur
}

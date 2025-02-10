#pragma option -zC_TEXT -zPTEXT -2

#include <stddef.h>
#include "th02/main/spark.hpp"
#include "th02/sprites/sparks.h"
#include "th02/main/playfld.hpp"
#include "th02/main/scroll.hpp"
#include "th02/hardware/pages.hpp"
#include "libs/master.lib/pc98_gfx.hpp"

// ZUN landmine: sparks_add() insists on calling this function using a `near`
// call with the current code segment. This will cause a fixup overflow if this
// function is ever further than 64 KiB away from the call site. Just use the
// declaration from the regular header instead.
void pascal near vector2(int&, int&, unsigned char, int);

// ZUN bloat
#define unneeded_copy	reinterpret_cast<spark_t near *>(_AX)
#define screen_topleft_bytewise(p, offset) \
	reinterpret_cast<SPPoint near *>( \
		(reinterpret_cast<uint8_t near *>(p->screen_topleft) + offset) \
	)

void pascal sparks_add(
	screen_x_t left,
	uscreen_y_t top,
	subpixel_t speed_base,
	int count,
	bool16 as_sprite
)
{
	register spark_t near *p;
	register int group_i;
	Subpixel speed;
	int angle; // ACTUAL TYPE: unsigned char
	uint16_t page_offset;
	int slot_i;

	// Lol? Does this wraparound exist because ZUN was fully aware that the
	// player's Y position could fall below [RES_Y] during the death animation,
	// and he actually wanted these sparks near the top of the playfield? (See
	// player_miss_update_and_render() for context.)
	// ZUN landmine: Proper, arbitrary wrapping would have been safer. (Could
	// be a bug if we discover a call site that actually passes [top] values
	// >800.)
	// ZUN bloat: Also, re-assigning in the conditional branch would have been
	// enough.
	_AX = top;
	if(_AX >= RES_Y) {
		_AX -= RES_Y;
	}
	top = _AX;

	#define left	static_cast<subpixel_t>(left)
	#define top 	static_cast<subpixel_t>(top)

	TO_SP_INPLACE(left);
	TO_SP_INPLACE(top);

	// ZUN bloat: `p = &sparks[sparks_ring_i];`
	p = unneeded_copy = sparks;
	slot_i = _AX = spark_ring_i;
	_CL = sizeof(spark_t);
	asm { imul cl; }
	reinterpret_cast<uint8_t near *>(p) += _AX;

	page_offset = (page_back * sizeof(SPPoint));
	group_i = 0;
	while(group_i < count) {
		p->flag = F_ALIVE;
		p->age = 0;
		_BX = page_offset;
		_DX = left;
		screen_topleft_bytewise(p, _BX)->x.v = _DX;
		_DX = top;
		screen_topleft_bytewise(p, _BX)->y.v = _DX;
		if(!as_sprite) {
			p->render_as = p->default_render_as;
			speed.v = (p->speed_base.v + speed_base);
			angle = p->angle;
		} else {
			p->render_as = SRA_SPRITE;
			speed.v = speed_base;

			// ZUN bloat: `angle = ((group_i * 0x100) / count);`.
			// Turbo C++ 4.0J would have generated this CL left-shift code in
			// 8086 mode, but this function uses ENTER in its prolog, which was
			// only introduced with the 80186.
			_AX = group_i;
			_CL = 8;
			angle = ((static_cast<int>(_AX) << _CL) / count);
		}

		// ZUN bloat: vector2(p->velocity.x.v, p->velocity.y.v, angle, speed);
		static_assert(offsetof(spark_t, velocity.x) == 0x0A);
		static_assert(offsetof(spark_t, velocity.y) == 0x0C);
		asm {
			push	ds;
			db	0x8D, 0x44, 0x0A;
			push	ax;
			push	ds;
			db	0x8D, 0x44, 0x0C;
			push	ax;
			push	angle;
			push	speed;
			nop;
			push	cs;
			call	near ptr vector2;
		}

		group_i++;
		p++;
		slot_i++;
		if(slot_i >= SPARK_COUNT) {
			slot_i = 0;
			p -= SPARK_COUNT;
		}
	}

	// ZUN landmine: `spark_ring_i` should have just been `uint8_t` to begin
	// with.
	// Turbo C++ 4.0J unfortunately can't turn a modulo into `AND m8, imm`.
	static_assert((SPARK_COUNT & (SPARK_COUNT - 1)) == 0);
	_AX = count;
	static_cast<uint8_t>(spark_ring_i) += _AL;
	static_cast<uint8_t>(spark_ring_i) &= (SPARK_COUNT - 1);

	#undef top
	#undef left
}

#pragma codestring "\x90"

// Blits a hardcoded spark sprite. Assumptions:
// • The GRCG is active, and set to the intended color
// • [cel] ≤ SPARK_CELS
void pascal near grcg_spark_sprite_put(screen_x_t left, vram_y_t top, int cel)
{
	#define left_copy	static_cast<screen_x_t>(_BX) // ZUN bloat

	_ES = SEG_PLANE_B;
	left_copy = left;
	_DI = vram_offset_shift_fast(left_copy, top);
	_SI = reinterpret_cast<uint16_t>(&sSPARKS[left_copy & BYTE_MASK][cel][0]);
	_CX = SPARK_H;
	put_loop: {
		asm { movsw; }
		_DI += (ROW_SIZE - sizeof(dots16_t));
		if(static_cast<int16_t>(_DI) >= PLANE_SIZE) {
			_DI -= PLANE_SIZE;
		}
	}
	asm { loop	put_loop; }

	#undef left_copy
}

#pragma codestring "\x90"

void sparks_update_and_render(void)
{
	#define vram_top	static_cast<vram_y_t>(_DI)

	spark_t near *p;
	struct {
		int16_t padding_2;
		Subpixel near *left;
		int16_t padding_1;
		int i;
	} x; // ZUN bloat
	Subpixel near *top;
	screen_x_t screen_left;
	screen_y_t screen_top;

	grcg_setcolor(GC_RMW, 14);
	unneeded_copy = sparks;
	for((p = unneeded_copy, x.i = 0); x.i < SPARK_COUNT; (x.i++ , p++)) {
		if(p->flag != F_ALIVE) {
			continue;
		}

		// Update
		// ------

		x.left = &p->screen_topleft[page_back].x;

		// ZUN bloat: Pointer arithmetic is faster with Turbo C++ 4.0J, but
		// assumes the original structure layout.
		top = (x.left + 1);

		x.left->v += p->velocity.x.v;
		p->velocity.x.v += spark_accel_x.v;
		top->v += p->velocity.y.v;

		screen_top = top->v; // ZUN bloat: Redundant
		screen_left = x.left->to_pixel();
		screen_top = top->to_pixel();

		// ZUN bloat: Could have been assigned below.
		vram_top = screen_top;

		p->velocity.y.v += to_sp(0.0625f);
		p->age++;

		// ZUN quirk: Should have subtracted [SPARK_W] from the left edge
		// rather than the right one...
		if(
			(screen_left < PLAYFIELD_LEFT) ||
			(screen_left >= (PLAYFIELD_RIGHT - SPARK_W)) ||
			(p->age > spark_age_max) ||
			(vram_top >= PLAYFIELD_BOTTOM) ||
			(vram_top <= (PLAYFIELD_TOP - SPARK_H))
		) {
			p->flag = F_REMOVE;
			continue;
		}
		// ------

		// Render
		// ------
		vram_top = scroll_screen_y_to_vram(
			static_cast<uvram_y_t>(vram_top), vram_top
		);

		// ZUN bloat: Yes, Turbo C++ can't hoist identical instructions in two
		// branches out of the loop, but this micro-optimization saves a mere
		// 4 bytes.
		//
		// if(p->render_as == SRA_DOT) {
		// 	grcg_pset(screen_left, vram_top);
		// } else {
		// 	spark_sprite_put(screen_left, vram_top, (p->age % SPARK_CELS));
		// }
		asm {
			push	screen_left;
			push	di;
		}
		if(p->render_as == SRA_DOT) {
			asm { nop; push cs; call near ptr grcg_pset; }
		} else {
			_AX = (p->age % SPARK_CELS);
			asm {
				push	ax;
				call	near ptr grcg_spark_sprite_put;
			}
		}
		// ------
	}
	grcg_off();

	#undef vram_top
}

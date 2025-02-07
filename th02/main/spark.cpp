#pragma option -zC_TEXT -2

#include "th02/main/spark.hpp"
#include "th02/sprites/sparks.h"
#include "th02/main/playfld.hpp"
#include "th02/main/scroll.hpp"
#include "th02/hardware/pages.hpp"
#include "libs/master.lib/pc98_gfx.hpp"

// ZUN bloat
#define unneeded_copy	reinterpret_cast<spark_t near *>(_AX)

void pascal near grcg_spark_sprite_put(screen_x_t left, vram_y_t top, int cel)
;

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

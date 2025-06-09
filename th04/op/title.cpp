#include "th04/op/op.hpp"
#include "th04/sprites/op_cdg.hpp"
#include "th04/snd/snd.h"
#include "th04/shiftjis/fnshared.hpp"
#include "th04/resident.hpp"
#include "th03/formats/pi.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/v_colors.hpp"
#include "th01/hardware/grcg.hpp"
#include "libs/master.lib/pc98_gfx.hpp"

void near main_cdg_load(void)
{
	op_cdg_load_shared();
	cdg_load_all_noalpha(CDG_PIC, "sl.cd2");
}

void near main_cdg_free(void)
{
	cdg_free_all();
}

void near op_animate(void)
{
	enum {
		SLIDE_CEL_COUNT = 6,
		COL_BLACK = 0,
		FADE_SPEED = 4,
		FADE_DURATION = ((0x100 / FADE_SPEED) - 1),
	};

	// ZUN bloat: Declaring these inline as needed would have yielded better
	// register allocation. As usual.
	int i;
	int j;
	int comp;
	uint8_t k;
	page_t page_shown;

	palette_settone(0);
	graph_accesspage(1);

	// ZUN bloat: Filling both pages using TDW mode would be faster.
	// (One combined piece of bloat because it's really nitpicky.)
	grcg_setcolor(GC_RMW, V_WHITE);
	grcg_boxfill_8(0, 0, (RES_X - 1), (RES_Y - 1));
	grcg_off();
	graph_copy_page(0);

	pi_load(0, "op5b.pi");
	pi_load(1, "op4b.pi");
	pi_load(2, "op3b.pi");
	pi_load(3, "op2b.pi");
	pi_load(4, "op1b.pi");
	pi_load(5, "op0b.pi");
	pi_palette_apply(0);
	palette_black_in(4);

	graph_showpage(0);
	graph_accesspage(1);

	// Slide-in animation
	#define frame i
	#define tone j
	#define cel k
	frame = 0;
	cel = 0;
	tone = 100;
	page_shown = 0;
	while(frame < 28) {
		if(((frame % 4) == 0) && (cel < SLIDE_CEL_COUNT)) {
			pi_put_8(0, 38, cel);
			cel++;
			graph_accesspage(page_shown);
			page_shown = (1 - page_shown);
			graph_showpage(page_shown);
		}
		palette_settone(tone);
		tone += 2;
		frame_delay(1);
		frame++;
	}
	#undef cel
	#undef tone
	#undef frame

	// Flash
	palette_settone(200);
	graph_showpage(0);
	graph_accesspage(0); // ZUN bloat: Redundant, we switch to page 1 below

	// ZUN bloat: Should have looped over [SLIDE_CEL_COUNT].
	pi_free(0);
	pi_free(1);
	pi_free(2);
	pi_free(3);
	pi_free(4);
	pi_free(5);

	if(resident->demo_num == 0) {
		snd_load(BGM_MENU_MAIN_FN, SND_LOAD_SONG);
		snd_kaja_func(KAJA_SONG_PLAY, 0);
	}

	graph_accesspage(1);
	pi_fullres_load_palette_apply_put_free(0, MENU_MAIN_BG_FN);
	graph_copy_page(0);

	// Black-and-white fade-in
	#define col i
	for(col = 0; col < COLOR_COUNT; col++) {
		Palettes[col].set(0xFF, 0xFF, 0xFF);
	}
	palette_show(); // ZUN bloat: Redundant
	palette_settone(100);
	#undef col

	// ZUN bloat: Could have looped over just [brightness].
	#define frame i
	#define brightness k
	frame = 0;
	brightness = 0xF0;
	while(frame < (0xF0 / 16)) {
		// master.lib shifts the initial #F0F0F0 color to #FFF, thus keeping
		// the previous color and avoiding tearing on the first frame of this
		// effect.
		Palettes[COL_BLACK].c.r = brightness;
		Palettes[COL_BLACK].c.g = brightness;
		Palettes[COL_BLACK].c.b = brightness;
		palette_show();
		frame_delay(1);
		frame++;
		brightness -= 16;
	}
	#undef brightness
	#undef frame

	// Fade to the .PI palette. Note how we already freed the PI above!
	#define frame i
	#define col j
	#define white_point k
	frame = 0;
	white_point = (0x100 - FADE_SPEED);
	while(frame < FADE_DURATION){
		for(col = 1; col < COLOR_COUNT; col++) {
			for(comp = 0; comp < COMPONENT_COUNT; comp++) {
				if(pi_headers[0].palette[col].v[comp] < Palettes[col].v[comp]) {
					Palettes[col].v[comp] = white_point;
				}
			}
		}
		palette_show();
		frame_delay(1);
		frame++;
		white_point -= static_cast<int>(FADE_SPEED);
	}
	#undef white_point
	#undef col
	#undef frame

	pi_palette_apply(0);
}

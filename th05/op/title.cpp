#include "th01/hardware/grcg.hpp"
#include "th02/hardware/frmdelay.h"
#include "th04/op/op.hpp"
#include "th04/shiftjis/fnshared.hpp"
#include "th05/formats/pi.hpp"
#include "th05/resident.hpp"
#include "th04/sprites/op_cdg.hpp"

void near main_cdg_load(void)
{
	op_cdg_load_shared();
	cdg_load_single_noalpha((CDG_PIC + PLAYCHAR_REIMU), "sl00.cdg", 0);
	cdg_load_single_noalpha((CDG_PIC + PLAYCHAR_MARISA), "sl01.cdg", 0);
	cdg_load_single_noalpha((CDG_PIC + PLAYCHAR_MIMA), "sl02.cdg", 0);
	cdg_load_single_noalpha((CDG_PIC + PLAYCHAR_YUUKA), "sl03.cdg", 0);
	cdg_load_single(CDG_CLEARED, "slcl.cdg", 0);
	cdg_load_single_noalpha(CDG_PIC_NOT_CLEARED, "sl04.cdg", 0);
}

void near main_cdg_free(void)
{
	cdg_free_all();
}

void near op_animate(void)
{
	enum {
		ROLL_CELS = 8,
		ROLL_FRAMES_PER_CEL = 8,
		ROLL_DURATION = (ROLL_CELS * ROLL_FRAMES_PER_CEL),

		FADE_CELS = PI_MASK_COUNT,
		FADE_FRAMES_PER_CEL = 4,
		FADE_DURATION = (FADE_CELS * FADE_FRAMES_PER_CEL),
	};

	struct {
		// ZUN bloat: One variable is enough...
		page_t show;
		page_t access;

		void wait_and_flip(void) {
			frame_delay(1);
			graph_accesspage(access);
			graph_showpage(show);
			access = show;
			show = (1 - show);
		}
	} page;

	palette_black();
	pi_load(0, "op2a.pi");
	pi_load(1, "op2b.pi");
	pi_load(2, "op2c.pi");
	pi_load(3, "op2d.pi");
	pi_load(4, "op2e.pi");
	pi_load(5, "op2f.pi");
	pi_load(6, "op2g.pi");
	pi_load(7, "op2h.pi");

	// ZUN bloat: Changed again below, and the palette is black anyway.
	graph_accesspage(0);
	graph_showpage(0);

	// Not the same as graph_clear(), which uses hardware palette color #0.
	grcg_setcolor(GC_RMW, 1);
	graph_accesspage(1);	grcg_boxfill_8(0, 0, (RES_X - 1), (RES_Y - 1));
	graph_accesspage(0);	grcg_boxfill_8(0, 0, (RES_X - 1), (RES_Y - 1));
	grcg_off();
	graph_copy_page(1); // ZUN bloat: You've just cleared both pages...

	page.access = 1;
	page.show = 0;

	graph_accesspage(0);

	// ZUN landmine: Should be page 1. .PI blitting is quite slow, and might
	// cause tearing on slower systems on the first frame of the loop below.
	graph_showpage(0);

	{for(int frame = 0; frame < ROLL_DURATION; frame++) {
		// Blit to both pages
		if((frame % ROLL_FRAMES_PER_CEL) <= (2 - 1)) {
			pi_palette_apply(frame / ROLL_FRAMES_PER_CEL);
			pi_put_8(0, 278, (frame / ROLL_FRAMES_PER_CEL));
		}
		page.wait_and_flip();
		palette_settone((100 - ROLL_DURATION) + frame);
	}}

	// The pi_load() call below automatically does this for slot 0.
	{for(int i = 1; i < ROLL_CELS; i++) {
		pi_free(i);
	}}

	// ZUN bloat: The loop above already blitted the animation to both pages.
	// Full page copies are quite slow on PC-98, and this might take longer
	// than one frame.
	graph_copy_page(1);

	if(resident->demo_num == 0) {
		snd_load(BGM_MENU_MAIN_FN, SND_LOAD_SONG);
		snd_kaja_func(KAJA_SONG_PLAY, 0);
	}

	pi_load(0, MENU_MAIN_BG_FN);
	graph_accesspage(0);

	// ZUN landmine: Should also be page 1. Masked .PI blitting is even slower.
	// When fixing this landmine, the frame_delay() also needs to be reduced by
	// 1; wait_and_flip() adds another delay frame before the flip, during
	// which the first pi_put_masked_8() call would remain invisible.
	graph_showpage(0);
	frame_delay(16);

	{for(int frame = 0; frame < FADE_DURATION; frame++) {
		// Blit to both pages
		if((frame % FADE_FRAMES_PER_CEL) <= (2 - 1)) {
			pi_put_masked_8(0, 0, 0, (frame / FADE_FRAMES_PER_CEL));
		}
		page.wait_and_flip();
	}}

	// Blit the original, unmasked image
	graph_accesspage(1);
	graph_showpage(0);

	// Doing this might have been better before the masked blitting loop. But
	// if the palettes of the roll animation images and the final title image
	// don't match up, there will be a sudden jump *somewhere*.
	pi_palette_apply(0);

	pi_put_8(0, 0, 0);
	pi_free(0);
	graph_copy_page(0); // ZUN bloat: Slower than a second call to pi_put_8()!
}

#include "game/bgimage.hpp"
#include "th01/hardware/grcg.hpp"
#include "th02/hardware/frmdelay.h"
#include "th03/sprites/pi_mask.hpp"
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
		page_t access;

		void wait_and_flip(void) {
			frame_delay(1);
			graph_accesspage(access);
			access ^= 1;
			graph_showpage(access);
		}
	} page;

	palette_settone(0);
	pi_load(0, "op2a.pi");
	pi_load(1, "op2b.pi");
	pi_load(2, "op2c.pi");
	pi_load(3, "op2d.pi");
	pi_load(4, "op2e.pi");
	pi_load(5, "op2f.pi");
	pi_load(6, "op2g.pi");
	pi_load(7, "op2h.pi");

	// Not the same as graph_clear(), which uses hardware palette color #0.
	grcg_setcolor(GC_RMW, 1);
	graph_accesspage(1);	grcg_boxfill_8(0, 0, (RES_X - 1), (RES_Y - 1));
	graph_accesspage(0);	grcg_boxfill_8(0, 0, (RES_X - 1), (RES_Y - 1));
	grcg_off();

	page.access = 1;

	graph_accesspage(0);

	// ZUN landmine: Should be page 1. .PI blitting is quite slow, and might
	// cause tearing on slower systems on the first frame of the loop below.
	graph_showpage(0);

	{for(int frame = 0; frame < ROLL_DURATION; frame++) {
		// Blit to both pages
		if((frame % ROLL_FRAMES_PER_CEL) <= (PAGE_COUNT - 1)) {
			pi_palette_apply(frame / ROLL_FRAMES_PER_CEL);
			pi_put_8(0, 278, (frame / ROLL_FRAMES_PER_CEL));
		}
		page.wait_and_flip();

		// ZUN bug: Off by one; the last iteration will leave [PaletteTone] at
		// 99, not 100, which does in fact significantly darken the image.
		palette_settone((100 - ROLL_DURATION) + frame);
	}}

	{for(int i = 0; i < ROLL_CELS; i++) {
		pi_free(i);
	}}

	if(resident->demo_num == 0) {
		snd_load(BGM_MENU_MAIN_FN, SND_LOAD_SONG);
		snd_kaja_func(KAJA_SONG_PLAY, 0);
	}

	GrpSurface_LoadPI(bgimage, &Palettes, MENU_MAIN_BG_FN);

	// ZUN bug: This one starts with a screen tearing landmine caused by slow
	// .PI blitting onto the shown page. However, it then turns out that shown
	// page = accessed page shifts the timing of the whole animation back by
	// one frame:
	// • The first cel is shown for one additional frame as the CRT beam also
	//   draws it *before* the first flip in the loop below. Every other cel
	//   only appears on screen *after* the flip.
	// • Since the code immediately quits out of the loop after the last flip
	//   and draws the original unmasked image on the next frame, it also cuts
	//   one frame from the last cel.
	// In the end, we end up with a frame timing of 5-4-4-3 instead of the
	// intended 4-4-4-4.
	graph_accesspage(0);
	graph_showpage(0);
	frame_delay(16);

	{for(int frame = 0; frame < FADE_DURATION; frame++) {
		// Blit to both pages
		if((frame % FADE_FRAMES_PER_CEL) <= (PAGE_COUNT - 1)) {
			bgimage.or_masked(
				0, 0, &PI_MASKS[frame / FADE_FRAMES_PER_CEL][0], PI_MASK_H
			);
		}
		page.wait_and_flip();
	}}

	// Blit the original, unmasked image
	graph_accesspage(0);
	graph_showpage(0);

	// Doing this might have been better before the masked blitting loop. But
	// if the palettes of the roll animation images and the final title image
	// don't match up, there will be a sudden jump *somewhere*.
	palette_show();

	bgimage.write(0, 0);
}

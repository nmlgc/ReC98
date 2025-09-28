#pragma option -zCMAINE_01_TEXT

#include "th05/end/allcast.hpp"
#include "th05/snd/snd.h"
#include "th05/formats/pi.hpp"
#include "th05/playchar.h"
#include "th05/resident.hpp"
#include "th02/hardware/frmdelay.h"
#include "th01/hardware/grcg.hpp"
#include "game/cutscene.hpp"
#include "libs/master.lib/pc98_gfx.hpp"

// Constants
// ---------

// ZUN landmine: Should be 7 (「Project of TOUHOU」 + 5 games + Credits), but
// ZUN sets it to 8, presumably for micro-optimization reasons. In exchange,
// though, the final call to screen_fadeout_animate_and_advance() unnecessarily
// calls pi_load() with a `nullptr` filename parameter.
static const int SCREEN_COUNT = 8;

static const vc_t COL_BLACK = 14;
static const screen_y_t CUTSCENE_PIC_TOP = ((RES_Y / 2) - (CUTSCENE_PIC_H / 2));
// ---------

// State
// -----

int measure_cur;
int frames_half;
int measure_target;
extern page_t page_shown;

// During screen_line_next_animate(), this is 1 more than the ID of the current
// screen shown!
int loaded_screen_id;

int line_id_total;
extern int line_id_on_screen;
static playchar_t playchar;
// -----

// Strings
// -------

extern const char *BG_FN[PLAYCHAR_COUNT][SCREEN_COUNT];

// ZUN bloat: We need (log₂(4) × [PLAYCHAR_COUNT] × 7) = 56 *bits* of
// information here, not 64 *bytes*. Using 2-bit values would probably be
// overkill, but a change to uint8_t would be free.
extern int BG_QUARTER[PLAYCHAR_COUNT][SCREEN_COUNT];
// -------

// Function ordering fails
// -----------------------

bool near wait_flip_and_check_measure_target(void);
// -----------------------

bool near screen_line_next_animate(void)
;

void pascal near screen_fadeout_animate_and_advance(
	screen_x_t pic_left, screen_y_t pic_top
)
{
	int quarter = BG_QUARTER[playchar][loaded_screen_id];

	palette_black_out(2);

	// ZUN bloat: Filling both pages using TDW mode would be faster.
	// (One combined piece of bloat because it's really nitpicky.)
	grcg_setcolor(GC_RMW, COL_BLACK);
	graph_accesspage(1); grcg_boxfill_8(0, 0, (RES_X - 1), (RES_Y - 1));
	graph_accesspage(0); grcg_boxfill_8(0, 0, (RES_X - 1), (RES_Y - 1));
	wait_flip_and_check_measure_target();
	grcg_off();

	// ZUN bloat: palette_100() could be reduced to a [PaletteTone] assignment
	// because [Palettes] remains unchanged until pi_palette_apply().
	palette_100();
	pi_palette_apply(0);

	for(int i = 0; i < (PI_MASK_COUNT * PAGE_COUNT); i++) {
		// ZUN quirk: Dividing by 4 reduces this animation to only the first
		// two mask patterns shown at an interval of 4 double frames, rather
		// than showing the full 4 masks at a 2-double-frame interval. But
		// given that the text later only even uses a single mask, ZUN most
		// likely did this on purpose to make this sequence feel more languid
		// and relaxed. It does look rather hectic with 4 masks.
		pi_put_quarter_masked_8(pic_left, pic_top, 0, quarter, (i / 4));
		wait_flip_and_check_measure_target();
	}

	pi_put_quarter_8(pic_left, pic_top, 0, quarter);
	wait_flip_and_check_measure_target();
	pi_put_quarter_8(pic_left, pic_top, 0, quarter);

	// ZUN landmine: Loading the .PI image for the next screen seems like a
	// productive use of the upcoming intentional delay, until you realize that
	// we've already spent 52 frames since hitting the [measure_target] for
	// this entire function. Since this load call is guaranteed to take
	// multiple frames on a 66 MHz system, it will return with the current BGM
	// measure even further ahead of [measure_target], which in turn increases
	// the chance that another text cue will have to catch up to that target.
	// The correct place for this call would have been in front of the
	// 30-measure delay below.
	loaded_screen_id++;
	if(loaded_screen_id < SCREEN_COUNT) {
		pi_load(0, BG_FN[playchar][loaded_screen_id]);
	}

	do {
		measure_target += 2;
		while(!wait_flip_and_check_measure_target()) {
		}
	} while(!screen_line_next_animate());

	measure_target += 30;
	while(!wait_flip_and_check_measure_target()) {
	}
}

bool near wait_flip_and_check_measure_target(void)
{
	frame_delay(2);

	graph_accesspage(page_shown);
	graph_showpage(page_shown = (1 - page_shown));

	frames_half++;
	measure_cur = snd_bgm_measure();
	if(measure_cur < 0) {
		// ZUN bug: 「Peaceful Romancer」 is timed using beats as measures. So,
		// 22×2 frames translates to (44 / 56.423) ≈ 780 ms = 76.94 BPM, which
		// is wholly unrelated to 「Peaceful Romancer」's ≈145-147 BPM.
		// While this might look like a quirk, it's much more likely that ZUN
		// actually intended 22 *regular* frames here, which would translate to
		// the much closer (22 / 56.423) ≈ 390 ms = 153.88 BPM.
		measure_cur = (frames_half / 22);
	}
	return (measure_cur >= measure_target);
}

void near allcast_animate(void)
{
	extern const char EXED[];
	line_id_total = 0;
	playchar = static_cast<playchar_t>(resident->playchar);
	palette_settone(0);

	// Not as redundant as it seems. palette_black_out() immediately sets
	// [PaletteTone] to 100, and we'd be fading out the last state of VRAM once
	// again on the first call to screen_fadeout_animate_and_advance() if we
	// didn't clear VRAM here.
	// ZUN bloat: Still, TDW mode would have been more performant.
	grcg_setcolor(GC_RMW, COL_BLACK);
	graph_accesspage(1); grcg_boxfill_8(0, 0, (RES_X - 1), (RES_Y - 1));
	graph_accesspage(0); grcg_boxfill_8(0, 0, (RES_X - 1), (RES_Y - 1));
	grcg_off();

	loaded_screen_id = 0;
	pi_load(0, BG_FN[playchar][0]);

	// Ensure that [COL_BLACK] actually is black during the first fade-out.
	pi_palette_apply(0);

	snd_load(EXED, SND_LOAD_SONG);
	snd_kaja_func(KAJA_SONG_PLAY, 0);

	// ZUN quirk: screen_fadeout_animate_and_advance() starts with a (blocking)
	// call to palette_black_out(2). The 2-measure delay loop here is supposed
	// to delay past 「Peaceful Romancer」's anacrusis and breaks at its first
	// downbeat, but said black-out call ensures that the animation starts
	// about two beats behind what you'd expect.
	measure_target = 2;
	while(!wait_flip_and_check_measure_target()) {
	}

	// ZUN bloat: Could be reduced to a [PaletteTone] assignment because we're
	// about to black out anyway.
	palette_100();

	// ZUN bloat: Should loop over [SCREEN_COUNT] after defusing its landmine.
	screen_fadeout_animate_and_advance(CUTSCENE_PIC_LEFT, CUTSCENE_PIC_TOP);
	screen_fadeout_animate_and_advance(CUTSCENE_PIC_LEFT, CUTSCENE_PIC_TOP);
	screen_fadeout_animate_and_advance(CUTSCENE_PIC_LEFT, CUTSCENE_PIC_TOP);
	screen_fadeout_animate_and_advance(CUTSCENE_PIC_LEFT, CUTSCENE_PIC_TOP);
	screen_fadeout_animate_and_advance(CUTSCENE_PIC_LEFT, CUTSCENE_PIC_TOP);
	screen_fadeout_animate_and_advance(CUTSCENE_PIC_LEFT, CUTSCENE_PIC_TOP);
	screen_fadeout_animate_and_advance(CUTSCENE_PIC_LEFT, CUTSCENE_PIC_TOP);

	measure_target += 16;
	while(!wait_flip_and_check_measure_target()) {
	}

	palette_black_out(4);

	pi_free(0);
	graph_accesspage(0);
	graph_showpage(0);
}

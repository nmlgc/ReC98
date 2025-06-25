#pragma option -zCMAINE_01_TEXT

#include "th05/end/allcast.hpp"
#include "th05/snd/snd.h"
#include "th05/playchar.h"
#include "th02/hardware/frmdelay.h"
#include "libs/master.lib/pc98_gfx.hpp"

// Constants
// ---------

// ZUN bloat: Should be 7 (「Project of TOUHOU」 + 5 games + Credits), but ZUN
// sets it to 8, presumably for micro-optimization reasons.
static const int SCREEN_COUNT = 8;
// ---------

// State
// -----

#define playchar allcast_playchar

int measure_cur;
int frames_half;
int measure_target;
extern page_t page_shown;
int loaded_screen_id;
int line_id_total;
extern int line_id_on_screen;
playchar_t playchar;
// -----

// Function ordering fails
// -----------------------

bool near wait_flip_and_check_measure_target(void);
// -----------------------

bool near wait_flip_and_check_measure_target(void)
{
	frame_delay(2);

	graph_accesspage(page_shown);
	graph_showpage(page_shown = (1 - page_shown));

	frames_half++;
	measure_cur = snd_bgm_measure();
	if(measure_cur < 0) {
		// ZUN quirk: 「Peaceful Romancer」 is timed using beats as measures.
		// So, 22×2 frames translates to (44 / 56.423) ≈ 780 ms = 76.94 BPM,
		// which is wholly unrelated to 「Peaceful Romancer」's ≈145-147 BPM.
		measure_cur = (frames_half / 22);
	}
	return (measure_cur >= measure_target);
}

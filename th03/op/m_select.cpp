/// Character selection menu
/// ------------------------

#pragma option -zPgroup_01

#include "th03/op/m_select.hpp"
#include "libs/master.lib/master.hpp"
#include "th03/common.h"
#include "th03/formats/cdg.h"
extern "C" {
#include "th03/formats/hfliplut.h"
}
#include "th03/formats/scoredat.hpp"
#include "th03/shiftjis/fns.hpp"
#include "th03/sprites/op_cdg.hpp"

/// State
/// -----

extern bool input_locked[PLAYER_COUNT];
extern playchar_t sel[PLAYER_COUNT];
extern bool sel_confirmed[PLAYER_COUNT];
extern page_t page_shown;
extern unsigned int fadeout_frames;
/// -----

#include "th03/formats/score_ld.cpp"

unsigned char near playchars_available_load(void)
{
	unsigned char ret = PLAYCHAR_COUNT_LOCKED;
	for(int i = RANK_EASY; i < (RANK_LUNATIC + 1); i++) {
		if(scoredat_load_and_decode(static_cast<rank_t>(i))) {
			return PLAYCHAR_COUNT_LOCKED;
		}
		if(hi.score.cleared == SCOREDAT_CLEARED) {
			ret = PLAYCHAR_COUNT;
		}
	}
	return ret;
}

// Coincidentally, these were the only characters available in the trial
// version.
void near select_cdg_load_part1_of_4(void)
{
	extern const char SELECT_EXTRA_FOR_PLAYCHAR_FN[];

	hflip_lut_generate();

	static_assert(PLAYCHAR_COUNT >= 3);
	for(int i = 0; i < 3; i++) {
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0);
	}
	cdg_load_all_noalpha(CDG_EXTRA_FOR_PLAYCHAR, SELECT_EXTRA_FOR_PLAYCHAR_FN);
}

void near select_cdg_load_part2_of_4(void)
{
	extern const char PLAYCHAR_PIC_UNKNOWN_FN[];
	extern const char SELECT_STATS_FN[];
	extern const char SELECT_EXTRA_BG_FN[];

	// ZUN bloat: Shouldn't this be exclusively loaded for Story Mode?
	cdg_load_single((CDG_PIC_SELECTED + 1), PLAYCHAR_PIC_UNKNOWN_FN, 0);

	cdg_load_single_noalpha(CDG_STATS, SELECT_STATS_FN, 0);
	cdg_load_single_noalpha(CDG_EXTRA_BG, SELECT_EXTRA_BG_FN, 0);
}

void near select_cdg_load_part3_of_4(void)
{
	extern const char SELECT_EXTRA_FOR_PLAYCHAR_FN[];

	// ZUN bloat: Redundant, PID 0 always has to select a character before the
	// game shows the image in this slot.
	cdg_load_single((CDG_PIC_SELECTED + 0), PLAYCHAR_PIC_FN[PLAYCHAR_REIMU], 0);

	static_assert(PLAYCHAR_COUNT >= 6);
	for(int i = 3; i < 6; i++) {
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0);
	}
}

#define select_cdg_load_part4_of_4() { \
	static_assert(PLAYCHAR_COUNT <= 9); \
	for(int i = 6; i < 9; i++) { \
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0); \
	} \
} \

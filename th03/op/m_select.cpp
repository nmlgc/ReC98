/// Character selection menu
/// ------------------------

#pragma option -zPgroup_01

#include "pc98.h"
#include "libs/master.lib/master.hpp"
#include "th03/common.h"
#include "th03/playchar.hpp"
#include "th03/formats/scoredat.hpp"

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

#include "th02/formats/scoredat.hpp"
#include "th02/gaiji/gaiji.h"
#include "th02/core/globals.hpp"
#include "th02/common.h"

extern scoredat_section_t hi;

// Slightly differs from the same function in ZUN_RES.COM!
void scoredat_defaults_set(void)
{
	for(int i = 0; i < SCOREDAT_PLACES; i++) {
		int c;

		// ZUN bloat: Probably leftover debug code? This function only ever
		// gets called if HUUHI.DAT doesn't exist, in which case [hi] can't be
		// anything other than zero-initialized, and all code that would write
		// to [cleared] immediately saves this file afterward.
		// (Also, this could have been done outside the loop!1!!)
		#if (BINARY == 'M')
			hi.score.cleared = 0;
		#endif

		hi.score.score[i] = (10000 - (i * 1000));
		hi.score.stage[i] = (MAIN_STAGE_COUNT - (i >> 1));
		for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
			hi.score.g_name[i][c] = gs_BULLET;
		}
		hi.score.g_name[i][SCOREDAT_NAME_LEN] = 0;
		hi.score.date[i].da_year = 1900;
		hi.score.date[i].da_day = 1;
		hi.score.date[i].da_mon = 1;
		hi.score.shottype[i] = 1;
	}
}

#include "th02/scorelod.c"

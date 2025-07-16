#pragma option -zCSCORE_TEXT

#include "th04/formats/scoredat/scoredat.hpp"
#include "libs/master.lib/master.hpp"
#include "th01/rank.h"
#if (GAME == 5)
#include "th05/playchar.h"
#else
#include "th04/playchar.h"
#endif
#include "th04/gaiji/gaiji.h"
#include "th04/shiftjis/fnshared.hpp"

static const int SCORE_INITIAL_DIGIT = ((GAME == 5) ? 6 : 5);

void near scoredat_recreate(void)
{
	int i;
	int place;

	// ZUN bloat
#if (GAME == 5)
	#define c place
#else
	int c;
#endif

	// ACTUAL TYPE: gaiji_th04_t
	unsigned char digit = (gb_0 + 10 - (10 / SCOREDAT_PLACES));

	for(i = 0; i < SCOREDAT_PLACES; i++) {
		hi.score.cleared = SCOREDAT_NOT_CLEARED;
		for(c = 0; c < SCORE_DIGITS; c++) {
			hi.score.g_score[i].digits[c] = gb_0;
		}

		if(i == 0) {
			hi.score.g_score[i].digits[SCORE_INITIAL_DIGIT - 0] = gb_1;
		} else {
			hi.score.g_score[i].digits[SCORE_INITIAL_DIGIT - 1] = digit;

			// ZUN bloat: `digit -= (10 / SCOREDAT_PLACES);` would work for
			// both games.
#if (GAME == 4)
			static_assert(SCOREDAT_PLACES == 10);
			digit--;
#else
			digit -= (10 / SCOREDAT_PLACES);
#endif
		}

		// ZUN landmine: This assigns decreasing stage numbers even for TH05's
		// Extra Stage, which should default to a constant 1 according to the
		// loop below.
		// Classifying this as a landmine because it's impossible for the
		// MAINE.EXE version of this code to ever run within our criteria of
		// observability – OP.EXE will have always regenerated [SCOREDAT_FN] if
		// it didn't exist or was corrupted, so this code can only ever run if
		// the file was somehow modified or deleted from outside the game while
		// it was running.
#if ((GAME == 5) && (BINARY == 'E'))
		hi.score.g_stage[i] = (gb_6 - i);
#elif (GAME == 4)
		hi.score.g_stage[i] = (gb_5 - (i / 2));
#endif

		for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
			hi.score.g_name[i][c] = gs_DOT;
		}
		hi.score.g_name[i][SCOREDAT_NAME_LEN] = g_NULL;
	}

	#undef c

#if (BINARY != 'O')
	#undef SCOREDAT_FN
	extern const char SCOREDAT_FN[];
#endif
	file_create(SCOREDAT_FN);
	for(i = 0; i < (RANK_COUNT * PLAYCHAR_COUNT); i++) {
#if ((GAME == 5) && (BINARY == 'O'))
		for(place = 0; place < SCOREDAT_PLACES; place++) {
			if((i % RANK_COUNT) == RANK_EXTRA) {
				hi.score.g_stage[place] = gb_1;
			} else {
				hi.score.g_stage[place] = (gb_1 + SCOREDAT_PLACES - place);
			}
		}
#endif
		// Well, OK, if you like to fully obfuscate the format by giving every
		// section its own encraption key...
		scoredat_encode_func();
		file_write(&hi, sizeof(hi));
		scoredat_decode_func();
	}
	file_close();
}

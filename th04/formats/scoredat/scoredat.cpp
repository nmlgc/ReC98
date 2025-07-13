#pragma option -zCSCORE_TEXT

#include "th04/formats/scoredat/scoredat.hpp"
#include "th04/formats/scoredat/impl.hpp"
#include "th04/gaiji/gaiji.h"
#include "th04/shiftjis/fnshared.hpp"
#include "libs/master.lib/master.hpp"

uint8_t pascal near scoredat_decode(scoredat_section_t& section)
{
	int i;
	int sum;
	scoredat_decode_section(section, sum, i);
	return (section.score_sum - sum);
}

void pascal near scoredat_encode(scoredat_section_t& section)
{
	int i;
	scoredat_sum(section.score_sum, i, section);

	section.key1 = irand();
	section.key2 = irand();

	uint8_t feedback = 0;
	i = (sizeof(scoredat_section_t) - 1);
	while(i >= offsetof(scoredat_section_t, score)) {
		scoredat_encode_byte_at(
			(reinterpret_cast<uint8_t *>(&section) + i),
			feedback,
			section.key1,
			section.key2
		);
		i--;
	}
}

inline int scoredat_section_i(playchar_t playchar, rank_t rank) {
	return ((playchar * RANK_COUNT) + rank);
}

size_t pascal near scoredat_section_offset(playchar_t playchar, rank_t rank)
{
	return (scoredat_section_i(playchar, rank) * sizeof(scoredat_section_t));
}

static const int SCORE_INITIAL_DIGIT = ((GAME == 5) ? 6 : 5);

#if (GAME == 5)
bool in_maine;
#endif

void near scoredat_recreate(void)
{
	int i;
	int c;

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
			digit -= (10 / SCOREDAT_PLACES);
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
#if (GAME == 5)
		if(in_maine) {
			hi.score.g_stage[i] = (gb_6 - i);
		}
#elif (GAME == 4)
		hi.score.g_stage[i] = (gb_5 - (i / 2));
#endif

		for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
			hi.score.g_name[i][c] = gs_DOT;
		}
		hi.score.g_name[i][SCOREDAT_NAME_LEN] = g_NULL;
	}

	file_create(SCOREDAT_FN);
	for(i = 0; i < (RANK_COUNT * PLAYCHAR_COUNT); i++) {
#if (GAME == 5)
		if(!in_maine) {
			for(int place = 0; place < SCOREDAT_PLACES; place++) {
				if((i % RANK_COUNT) == RANK_EXTRA) {
					hi.score.g_stage[place] = gb_1;
				} else {
					hi.score.g_stage[place] = (gb_1 + SCOREDAT_PLACES - place);
				}
			}
		}
#endif
		// Well, OK, if you like to fully obfuscate the format by giving every
		// section its own encraption key...
		scoredat_encode(hi);
		file_write(&hi, sizeof(hi));
		scoredat_decode(hi);
	}
	file_close();
}

bool pascal near scoredat_load(playchar_t playchar, rank_t rank)
{
	if(file_ropen(SCOREDAT_FN)) {
		file_seek(scoredat_section_offset(playchar, rank), SEEK_SET);
		file_read(&hi, sizeof(scoredat_section_t));
		file_close();

		if(scoredat_decode(hi) == 0) {
			return false;
		}
	}
	scoredat_recreate();
	return true;
}

void pascal near scoredat_save(playchar_t playchar, rank_t rank)
{
	scoredat_encode(hi);

	file_append(SCOREDAT_FN);
	file_seek(scoredat_section_offset(playchar, rank), SEEK_SET);
	file_write(&hi, sizeof(scoredat_section_t));
	file_close();
}

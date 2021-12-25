#pragma option -zPgroup_01

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/rank.h"
#include "th03/common.h"
#include "th03/score.h"
#include "th03/playchar.hpp"
#include "th03/resident.hpp"
#include "th03/sprites/regi.h"
#include "th03/formats/cdg.h"
#include "th03/formats/pi.hpp"
}
#include "th03/formats/scoredat.hpp"

#include "th03/formats/score_ld.cpp"
#include "th03/formats/score_es.cpp"

static const int PLACE_NONE = -1;

void near regist_load_and_put_initial(void)
{
	enum {
		RANK_IMAGE_W = 320,
		RANK_IMAGE_H = 88,
	};

	extern unsigned char near *rank_image_fn;
	extern const char regib_pi[];
	extern const char regi2_bft[];
	extern const char regi1_bft[];

	palette_black();
	graph_accesspage(0);
	graph_showpage(0);

	pi_load_put_8_free(0, regib_pi);

	// Kind of assumes that we only show this screen once for the lifetime of
	// the process.
	rank_image_fn[3] += resident->rank;

	cdg_load_single(0, rank_image_fn, 0);
	cdg_put_8((RES_X - RANK_IMAGE_W), (RES_Y - RANK_IMAGE_H), 0);
	cdg_free(0);

	super_entry_bfnt(regi2_bft);
	super_entry_bfnt(regi1_bft);

	graph_copy_page(1);
	graph_accesspage(0);
}

inline int score_digit_as_regi(int digit) {
	return (REGI_0 + resident->score_last[0].digits[digit]);
}

int near regist_score_enter_from_resident(void)
{
	int place;
	int shift;
	int c;

	for(place = 0; place < SCOREDAT_PLACES; place++) {
		for(c = (SCORE_DIGITS - 1); c >= 0; c--) {
			if(score_digit_as_regi(c) > hi.score.score[place][c + 1]) {
				goto found;
			} else if(score_digit_as_regi(c) < hi.score.score[place][c + 1]) {
				break;
			}
		}
	}
	if(place == SCOREDAT_PLACES) {
		return PLACE_NONE;
	}

found:
	if(place < (SCOREDAT_PLACES - 1)) {
		for(shift = (SCOREDAT_PLACES - 2); shift >= place; shift--) {
			for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
				hi.score.name[shift + 1][c] = hi.score.name[shift][c];
			}
			for(c = 0; c < sizeof(hi.score.score[0]); c++) {
				hi.score.score[shift + 1][c] = hi.score.score[shift][c];
			}
			hi.score.stage[shift + 1] = hi.score.stage[shift];
			hi.score.playchar[shift + 1] = hi.score.playchar[shift];
		}
	}

	for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
		hi.score.name[place][c] = REGI_ASCII(' ');
	}

	for(c = 1; c < (SCORE_DIGITS + 1); c++) {
		hi.score.score[place][c] = REGI_DIGIT(
			resident->score_last[0].digits[c - 1]
		);
	}
	hi.score.score[place][0] = static_cast<regi_patnum_t>(
		REGI_3 - resident->rem_credits
	);

	if(resident->story_stage == STAGE_ALL) {
		hi.score.stage[place] = REGI_ALL;
	} else {
		hi.score.stage[place] = REGI_DIGIT(resident->story_stage);
	}

	hi.score.playchar[place].v = (resident->playchar_paletted[0].char_id() + 1);
	return place;
}

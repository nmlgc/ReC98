#pragma option -zPgroup_01

#include <stddef.h>
#include "platform.h"
#include "th03/common.h"
#include "th03/score.hpp"
#include "th03/playchar.hpp"
#include "th03/sprites/regi.h"
#include "th03/formats/scoredat.hpp"
#include "th03/formats/scorecry.hpp"

void near scoredat_decode(void)
{
	uint8_t near *p = reinterpret_cast<uint8_t near *>(&hi);
	int i = 0;
	uint8_t tmp;

	while(i < (offsetof(scoredat_section_t, score.key1) - 1)) {
		scoredat_decode_byte_at(p, tmp, hi.score.key1, hi.score.key2);
		i++;
		p++;
	}
	p[0] = (hi.score.key1 + hi.score.key2 + p[0]);
}

void near scoredat_recreate(void)
{
	int i;
	int j;
	uint8_t regi = REGI_9; // regi_patnum_t

	for(i = 0; i < SCOREDAT_PLACES; i++) {
		for(j = 0; j < SCOREDAT_NAME_LEN; j++) {
			hi.score.name[i][j] = REGI_PERIOD;
		}
		for(j = 0; j < sizeof(hi.score.score[0]); j++) {
			hi.score.score[i][j] = REGI_0;
		}
		hi.score.playchar[i].set_none();
		hi.score.stage[i] = REGI_1;
	}

	hi.score.score[0][4] = REGI_1;
	j = 1;
	while(j < SCOREDAT_PLACES) {
		hi.score.score[j][3] = static_cast<regi_patnum_t>(regi);
		j++;
		regi--;
	}
	hi.score.cleared = SCOREDAT_NOT_CLEARED;

	for(i = RANK_EASY; i < (RANK_LUNATIC + 1); i++) {
		scoredat_encode_and_save(static_cast<rank_t>(i));
		scoredat_decode();
	}
}

bool near scoredat_sum_invalid(void)
{
	int i;
	uint16_t sum = 0;
	uint8_t near *p;

	scoredat_sum(sum, p, i);
	return (hi.sum != sum) ? true : false;
}

#include "platform.h"
#include "master.hpp"
#include "th04/formats/scoredat.hpp"
#include "th04/op/clear.hpp"
#include "th05/resident.hpp"
#include "th05/op/op.hpp"

scoredat_section_t hi;
scoredat_section_t hi2;
static uint8_t scoredat_unused; // ZUN bloat

unsigned char rank;
unsigned char cleared_with[PLAYCHAR_COUNT][RANK_COUNT];
bool extra_unlocked;

void near cleardata_and_regist_view_sprites_load(void)
{
	int playchar;

	extra_unlocked = false;
	for(playchar = PLAYCHAR_REIMU; playchar < PLAYCHAR_COUNT; playchar++) {
		rank = RANK_EASY;
		while(rank < RANK_COUNT) {
			if(scoredat_load_for(playchar)) {
				break;
			}
			cleared_with[playchar][rank] = hi.score.cleared;
			if(cleared_with[playchar][rank] != SCOREDAT_CLEARED) {
				cleared_with[playchar][rank] = false;
			}
			if(rank < RANK_EXTRA) {
				extra_unlocked |= cleared_with[playchar][rank];
			}
			rank++;
		}
	}

	rank = resident->rank;
	super_entry_bfnt("scnum.bft");
	super_entry_bfnt("hi_m.bft");

	for(playchar = PLAYCHAR_REIMU; playchar < PLAYCHAR_COUNT; playchar++) {
		// MODDERS: Iterate over ranks instead
		extra_playable_with[playchar] = (
			cleared_with[playchar][RANK_EASY] |
			cleared_with[playchar][RANK_NORMAL] |
			cleared_with[playchar][RANK_HARD] |
			cleared_with[playchar][RANK_LUNATIC]
		);
	}
}

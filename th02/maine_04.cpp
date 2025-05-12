/* ReC98
 * -----
 * Code segment #4 of TH02's MAINE.EXE
 */

#include "th02/hiscore/regist.cpp"

#include "th02/score.c"

score_t score_highest;
scoredat_section_t hi;

void pascal score_highest_get(void)
{
	scoredat_init();
	score_highest = (hi.score.score[0] >= score) ? hi.score.score[0] : score;
}

int scoredat_is_extra_unlocked(void)
{
	int game_clear_constants[SHOTTYPE_COUNT] = GAME_CLEAR_CONSTANTS;
	char rank_save = rank;
	for(rank = 0; (int)rank < SHOTTYPE_COUNT; rank++) {
		scoredat_load();
		if(game_clear_constants[rank] != hi.score.cleared) {
			rank = rank_save;
			return 0;
		}
	}
	rank = rank_save;
	return 1;
}

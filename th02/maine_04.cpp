/* ReC98
 * -----
 * Code segment #4 of TH02's MAINE.EXE
 */

// Required to ensure the correct order of strings in `th02/score.c`?!
#pragma option -d-

#include "th01/math/clamp.hpp"
#include "th02/resident.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"

#include "th02/hiscore/regist.cpp"

#include "th02/score.c"

score_t score_highest;
scoredat_section_t hi;

inline void scoredat_init() {
	if(!file_exist(SCOREDAT_FN)) {
		scoredat_defaults_set();
	} else {
		scoredat_load();
	}
}

void score_enter(void)
{
	int name_pos = 0;
	int place;
	int shift;
	int c;
	int row;
	int col;
	int input_locked;
	unsigned char input_delay;
	scoredat_init();
	if(hi.score.score[SCOREDAT_PLACES - 1] > score) {
		scores_put(-1);
		key_delay();
		return;
	}
	for(place = SCOREDAT_PLACES - 1; place > 0; place--) {
		if(hi.score.score[place-1] > score) {
			break;
		}
	}
	for(shift = SCOREDAT_PLACES - 1; shift > place; shift--) {
		hi.score.score[shift] = hi.score.score[shift-1];
		for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
			hi.score.g_name[shift][c] = hi.score.g_name[shift-1][c];
		}
		hi.score.stage[shift] = hi.score.stage[shift-1];
		hi.score.date[shift].da_year = hi.score.date[shift-1].da_year;
		hi.score.date[shift].da_mon = hi.score.date[shift-1].da_mon;
		hi.score.date[shift].da_day = hi.score.date[shift-1].da_day;
		hi.score.shottype[shift] = hi.score.shottype[shift-1];
	}
	hi.score.score[place] = score;
	hi.score.stage[place] = STAGE_ALL;
	getdate(&hi.score.date[place]);
	hi.score.shottype[place] = resident->shottype;
	for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
		hi.score.g_name[shift][c] = gs_BULLET;
	}
	scores_put(place);

	col = 0;
	row = 0;
	key_det = 0;
	input_locked = 1;
	input_delay = 0;

	#define alphabet_cursor_move(coord, coord_max, ring_direction, col, row) \
		alphabet_putca(col, row, TX_WHITE); \
		ring_direction(coord, coord_max - 1); \
		alphabet_putca(col, row, TX_GREEN | TX_REVERSE);

	do {
		input_reset_sense();
		if(!input_locked) {
			if(key_det & INPUT_UP) {
				alphabet_cursor_move(row, ALPHABET_ROWS, ring_dec, col, row);
			}
			if(key_det & INPUT_DOWN) {
				alphabet_cursor_move(row, ALPHABET_ROWS, ring_inc, col, row);
			}
			if(key_det & INPUT_LEFT) {
				alphabet_cursor_move(col, ALPHABET_COLS, ring_dec, col, row);
			}
			if(key_det & INPUT_RIGHT) {
				alphabet_cursor_move(col, ALPHABET_COLS, ring_inc, col, row);
			}
			if(key_det & INPUT_SHOT || key_det & INPUT_OK) {
				/* Yeah, it sucks that ZUN checks against the indices into the
				* alphabet structure rather than against the gaiji values. */
				if(row != 2 || col < 13) {
					hi.score.g_name[place][name_pos] = gALPHABET[row][col];
					if(name_pos == 5) {
						alphabet_putca(col, row, TX_WHITE);
						col = ALPHABET_ENTER_COL;
						row = ALPHABET_ENTER_ROW;
						alphabet_putca(col, row, TX_GREEN | TX_REVERSE);
					}
					clamp_inc(name_pos, 5);
				} else if(col == 13) {
					hi.score.g_name[place][name_pos] = gb_SP;
					clamp_inc(name_pos, 5);
				} else if(col == 14) {
					clamp_dec(name_pos, 0);
					hi.score.g_name[place][name_pos] = gb_SP;
				} else if(col == 15) {
					clamp_inc(name_pos, 5);
				} else if(col == 16) {
					break;
				}
				scoredat_name_puts(place, name_pos);
			}
			if(key_det & INPUT_BOMB) {
				hi.score.g_name[place][name_pos] = gb_SP;
				clamp_dec(name_pos, 0);
				scoredat_name_puts(place, name_pos);
			}
			if(key_det & INPUT_CANCEL) {
				break;
			}
		}
		frame_delay(1);
		input_locked = key_det;
		if(input_locked) {
			input_delay++;
			if(input_delay > 30 && (input_delay & 1) == 0) {
				input_locked = 0;
			}
		} else {
			input_delay = 0;
		}
	} while(1);
	scoredat_save();
}

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

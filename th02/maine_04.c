/* ReC98
 * -----
 * Code segment #4 of TH02's MAINE.EXE
 */

#include "th02\th02.h"
#include "th02/score.h"
#include "th02\score.c"
#include "th02\scoreenc.c"

long score_highest;
scoredat_section_t hi;

void pascal scoredat_defaults_set(void)
{
	int i;
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		int c;
		hi.score.points[i] = 10000 - (i * 1000);
		hi.score.stage[i] = 5 - (i >> 1);
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

#include "th02\scorelod.c"

#define scoredat_init() \
	if(!file_exist(SCOREDAT_FN)) { \
		scoredat_defaults_set(); \
	} else { \
		scoredat_load(); \
	}

// Slightly differs from the same function in OP.EXE!
void pascal score_points_put(unsigned y, long points, unsigned atrb)
{
	int x;
	int digit;
	long divisor = 10000000;
	long result;
	char putting = 0;
	for(x = 26; x < 26 + (8 * 2); x += 2) {
		result = (points / divisor) % 10;
		divisor /= 10;
		digit = result + GB_DIGITS;
		if(result) {
			putting = 1;
		}
		if(putting) {
			gaiji_putca(x, y, digit, atrb);
		}
	}
}

#define ALPHABET_PUTCA(col, row, atrb) \
	gaiji_putca(10 + (col * 2), 18 + row, gALPHABET[row][col], atrb);

void pascal near scores_put(int place_to_highlight)
{
	unsigned atrb = TX_WHITE;
	int i;
	int col;
	gaiji_putsa(20, 2, gbHI_SCORE, TX_GREEN);
	gaiji_putsa(12, 4, gbNAME, TX_GREEN);
	gaiji_putsa(28, 4, gbPOINT, TX_GREEN);
	gaiji_putsa(42, 4, gbST, TX_GREEN);
	if(place_to_highlight != -1) {
		for(i = 0; i < ALPHABET_ROWS; i++) {
			for(col = 0; col < ALPHABET_COLS; col++) {
				ALPHABET_PUTCA(col, i, TX_WHITE);
			}
		}
		ALPHABET_PUTCA(0, 0, TX_GREEN | TX_REVERSE);
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		ATRB_SET(i);
		gaiji_putsa(10, 6+i, (const char*)hi.score.g_name[i], atrb);
		score_points_put(6+i, hi.score.points[i], atrb);
		if(hi.score.stage[i] != STAGE_ALL) {
			gaiji_putca(44, 6+i, hi.score.stage[i] + GB_DIGITS, atrb);
		} else {
			gaiji_putca(44, 6+i, gs_ALL, atrb);
		}
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		ATRB_SET(i);
		if(i != 9) {
			gaiji_putca(6, 6+i, GB_DIGITS+i+1, atrb);
		} else {
			gaiji_putca(4, 15, gb_1_, atrb);
			gaiji_putca(6, 15, gb_0_, atrb);
		}
	}
}

void pascal near alphabet_putca(int col, int row, unsigned atrb)
{
	ALPHABET_PUTCA(col, row, atrb);
}

void pascal near scoredat_name_puts(int place, int char_to_highlight)
{
	gaiji_putsa(10, 6 + place, (const char*)hi.score.g_name[place], TX_GREEN);
	gaiji_putca(
		10 + (char_to_highlight * 2),
		6 + place,
		hi.score.g_name[place][char_to_highlight],
		TX_GREEN | TX_REVERSE
	);
}

void pascal scoredat_save(void)
{
	SCOREDAT_ENCODE();
	file_append(SCOREDAT_FN);
	file_seek(rank * sizeof(hi), 0);
	file_write(&hi, sizeof(hi));
	file_close();
}

void pascal score_enter(void)
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
	if(hi.score.points[SCOREDAT_PLACES - 1] > score) {
		scores_put(-1);
		key_delay();
		return;
	}
	for(place = SCOREDAT_PLACES - 1; place > 0; place--) {
		if(hi.score.points[place-1] > score) {
			break;
		}
	}
	for(shift = SCOREDAT_PLACES - 1; shift > place; shift--) {
		hi.score.points[shift] = hi.score.points[shift-1];
		for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
			hi.score.g_name[shift][c] = hi.score.g_name[shift-1][c];
		}
		hi.score.stage[shift] = hi.score.stage[shift-1];
		hi.score.date[shift].da_year = hi.score.date[shift-1].da_year;
		hi.score.date[shift].da_mon = hi.score.date[shift-1].da_mon;
		hi.score.date[shift].da_day = hi.score.date[shift-1].da_day;
		hi.score.shottype[shift] = hi.score.shottype[shift-1];
	}
	hi.score.points[place] = score;
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

	#define ALPHABET_CURSOR_MOVE(coord, max, direction) \
		alphabet_putca(col, row, TX_WHITE); \
		RING_##direction(coord, ALPHABET_##max - 1); \
		alphabet_putca(col, row, TX_GREEN | TX_REVERSE);

	// Otherwise, this leads to more levels of indentation than I would like.
	#define INPUTS if(key_det & INPUT_UP) { \
		ALPHABET_CURSOR_MOVE(row, ROWS, DEC); \
	} \
	if(key_det & INPUT_DOWN) { \
		ALPHABET_CURSOR_MOVE(row, ROWS, INC); \
	} \
	if(key_det & INPUT_LEFT) { \
		ALPHABET_CURSOR_MOVE(col, COLS, DEC); \
	} \
	if(key_det & INPUT_RIGHT) { \
		ALPHABET_CURSOR_MOVE(col, COLS, INC); \
	} \
	if(key_det & INPUT_SHOT || key_det & INPUT_OK) { \
		/* Yeah, it sucks that ZUN checks against the indices into the
		 * alphabet structure rather than against the gaiji values. */ \
		if(row != 2 || col < 13) { \
			hi.score.g_name[place][name_pos] = gALPHABET[row][col]; \
			if(name_pos == 5) { \
				alphabet_putca(col, row, TX_WHITE); \
				col = 16; \
				row = 2; \
				alphabet_putca(col, row, TX_GREEN | TX_REVERSE); \
			} \
			CLAMP_INC(name_pos, 5); \
		} else if(col == 13) { \
			hi.score.g_name[place][name_pos] = gb_SP; \
			CLAMP_INC(name_pos, 5); \
		} else if(col == 14) { \
			CLAMP_DEC(name_pos, 0); \
			hi.score.g_name[place][name_pos] = gb_SP; \
		} else if(col == 15) { \
			CLAMP_INC(name_pos, 5); \
		} else if(col == 16) { \
			break; \
		} \
		scoredat_name_puts(place, name_pos); \
	} \
	if(key_det & INPUT_BOMB) { \
		hi.score.g_name[place][name_pos] = gb_SP; \
		CLAMP_DEC(name_pos, 0); \
		scoredat_name_puts(place, name_pos); \
	} \
	if(key_det & INPUT_CANCEL) { \
		break; \
	}

	do {
		input_sense();
		if(!input_locked) {
			INPUTS;
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
	score_highest = hi.score.points[0] >= score ? hi.score.points[0] : score;
}

int pascal scoredat_is_extra_unlocked(void)
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

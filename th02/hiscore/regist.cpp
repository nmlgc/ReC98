#include "th02/hiscore/regist.h"
#include "th02/main/playfld.hpp"
#if (BINARY == 'M')
#include "th02/main/stage/stage.hpp"
#endif
#include "th02/formats/scoredat.hpp"
#include "th02/gaiji/gaiji.h"
#include "th02/gaiji/score_p.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"
#include "th02/core/globals.hpp"
#include "th02/resident.hpp"
#include "th02/common.h"
#include "th01/math/clamp.hpp"
#include "libs/master.lib/pc98_gfx.hpp"

extern scoredat_section_t hi;

// Gaiji strings
// -------------

extern const unsigned char gbHI_SCORE[];
extern const unsigned char gALPHABET[ALPHABET_ROWS][ALPHABET_COLS];
extern const unsigned char gbNAME[];
extern const unsigned char gbPOINT[];
extern const unsigned char gbST[];

// Should be calculated via `sizeof()` once the strings can be emitted here.
static const tram_cell_amount_t TABLE_TITLE_W = (8 * GAIJI_TRAM_W);
static const tram_cell_amount_t TABLE_HEADER_NAME_W = (4 * GAIJI_TRAM_W);
static const tram_cell_amount_t TABLE_HEADER_STAGE_W = (2 * GAIJI_TRAM_W);
// -------------

// Coordinates
// -----------

static const tram_cell_amount_t TABLE_NAME_W = (
	SCOREDAT_NAME_LEN * GAIJI_TRAM_W
);
static const tram_cell_amount_t TABLE_SCORE_W = (SCORE_DIGITS * GAIJI_TRAM_W);

// ZUN quirk: Center-aligned in MAIN.EXE, right-aligned in MAINE.EXE.
static const tram_x_t TABLE_PLACE_SINGLE_X = (
	PLAYFIELD_TRAM_LEFT + GAIJI_TRAM_W
);
static const tram_x_t TABLE_PLACE_DOUBLE_LEFT = (
	PLAYFIELD_TRAM_LEFT + (BINARY == 'M')
);

static const tram_x_t TABLE_NAME_LEFT = (
	TABLE_PLACE_SINGLE_X + (2 * GAIJI_TRAM_W)
);
static const tram_x_t TABLE_SCORE_LEFT = (
	TABLE_NAME_LEFT + TABLE_NAME_W + (2 * GAIJI_TRAM_W)
);
static const tram_x_t TABLE_STAGE_X = (
	TABLE_SCORE_LEFT + TABLE_SCORE_W + GAIJI_TRAM_W
);

static const tram_x_t TABLE_TITLE_LEFT = (
	PLAYFIELD_TRAM_CENTER_X - (TABLE_TITLE_W / 2)
);
static const tram_x_t TABLE_HEADER_NAME_LEFT = (
	TABLE_NAME_LEFT + ((TABLE_NAME_W / 2) - (TABLE_HEADER_NAME_W / 2))
);

// ZUN quirk: Not correctly aligned in either binary; the proper alignment
// should probably depend on the highest score's number of digits. Could be a
// bug, but with both binaries being closer to (inconsistently) left-aligning
// this one, ZUN's intention is not all too clear.
static const tram_x_t TABLE_HEADER_SCORE_LEFT = (
	TABLE_SCORE_LEFT + 1 + (BINARY == 'E')
);

// ZUN bug: Misaligned in MAIN.EXE.
static const tram_x_t TABLE_HEADER_STAGE_LEFT = (
	TABLE_STAGE_X - (TABLE_HEADER_STAGE_W - GAIJI_TRAM_W) - (BINARY == 'M')
);

static const tram_y_t TABLE_TITLE_Y = (PLAYFIELD_TRAM_TOP + 1);
static const tram_y_t TABLE_HEADER_Y = (TABLE_TITLE_Y + 2);
static const tram_y_t TABLE_PLACES_TOP = (TABLE_HEADER_Y + 2);

inline tram_y_t table_place_y(int i) {
	return (TABLE_PLACES_TOP + i);
}

static const tram_x_t ALPHABET_LEFT = TABLE_NAME_LEFT;
static const tram_y_t ALPHABET_TOP = (TABLE_PLACES_TOP + SCOREDAT_PLACES + 2);
// -----------

// Slightly differs from the same function in ZUN_RES.COM!
void scoredat_defaults_set(void)
{
	for(int i = 0; i < SCOREDAT_PLACES; i++) {
		int c;

#if (BINARY == 'M')
		// ZUN bloat: Probably leftover debug code? This function only ever
		// gets called if HUUHI.DAT doesn't exist, in which case [hi] can't be
		// anything other than zero-initialized, and all code that would write
		// to [cleared] immediately saves this file afterward.
		// (Also, this could have been done outside the loop!1!!)
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

void pascal score_put(tram_y_t y, score_t score, tram_atrb2 atrb)
{
	#define on_digit_at(x, gaiji) { \
		gaiji_putca(x, y, gaiji, atrb); \
	}
	gaiji_score_put_to(TABLE_SCORE_LEFT, score, on_digit_at);
	#undef on_digit_at
}

// ZUN bloat: Should use the function throughout.
#define alphabet_putca_macro(col, row, atrb) { \
	gaiji_putca( \
		(ALPHABET_LEFT + (col * GAIJI_TRAM_W)), \
		(ALPHABET_TOP + row), \
		gALPHABET[row][col], \
		atrb \
	); \
}

void pascal near scores_put(int place_to_highlight)
{
	tram_atrb2 atrb = TX_WHITE;
	int i;
	int col;
	gaiji_putsa(TABLE_TITLE_LEFT, TABLE_TITLE_Y, gbHI_SCORE, TX_GREEN);
	gaiji_putsa(TABLE_HEADER_NAME_LEFT, TABLE_HEADER_Y, gbNAME, TX_GREEN);
	gaiji_putsa(TABLE_HEADER_SCORE_LEFT, TABLE_HEADER_Y, gbPOINT, TX_GREEN);
	gaiji_putsa(TABLE_HEADER_STAGE_LEFT, TABLE_HEADER_Y, gbST, TX_GREEN);
	if(place_to_highlight != -1) {
		for(i = 0; i < ALPHABET_ROWS; i++) {
			for(col = 0; col < ALPHABET_COLS; col++) {
				alphabet_putca_macro(col, i, TX_WHITE);
			}
		}
		alphabet_putca_macro(0, 0, (TX_GREEN | TX_REVERSE));
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		score_atrb_set(atrb, i, place_to_highlight);
		gaiji_putsa(
			TABLE_NAME_LEFT,
			table_place_y(i),
			reinterpret_cast<const char*>(hi.score.g_name[i]),
			atrb
		);
		score_put(table_place_y(i), hi.score.score[i], atrb);
		if(hi.score.stage[i] != STAGE_ALL) {
			gaiji_putca(
				TABLE_STAGE_X,
				table_place_y(i),
				(hi.score.stage[i] + gb_0),
				atrb
			);
		} else {
			gaiji_putca(TABLE_STAGE_X, table_place_y(i), gs_ALL, atrb);
		}
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		score_atrb_set(atrb, i, place_to_highlight);
		if(i != (SCOREDAT_PLACES - 1)) {
			gaiji_putca(
				TABLE_PLACE_SINGLE_X, table_place_y(i), (gb_1 + i), atrb
			);
		} else {
			gaiji_putca(
				(TABLE_PLACE_DOUBLE_LEFT + (0 * GAIJI_TRAM_W)),
				table_place_y(SCOREDAT_PLACES - 1),
				gb_1,
				atrb
			);
			gaiji_putca(
				(TABLE_PLACE_DOUBLE_LEFT + (1 * GAIJI_TRAM_W)),
				table_place_y(SCOREDAT_PLACES - 1),
				gb_0,
				atrb
			);
		}
	}
}

void pascal near alphabet_putca(int col, int row, tram_atrb2 atrb)
{
	alphabet_putca_macro(col, row, atrb);
}

void pascal near scoredat_name_puts(int place, int char_to_highlight)
{
	gaiji_putsa(
		TABLE_NAME_LEFT,
		table_place_y(place),
		reinterpret_cast<const char*>(hi.score.g_name[place]),
		TX_GREEN
	);
	gaiji_putca(
		(TABLE_NAME_LEFT + (char_to_highlight * GAIJI_TRAM_W)),
		table_place_y(place),
		hi.score.g_name[place][char_to_highlight],
		(TX_GREEN | TX_REVERSE)
	);
}

#include "th02/scoreenc.c"

void scoredat_save(void)
{
	scoredat_encode();
	file_append(SCOREDAT_FN);
	file_seek((rank * sizeof(hi)), SEEK_SET);
	file_write(&hi, sizeof(hi));
	file_close();
}

inline void scoredat_init() {
	if(!file_exist(SCOREDAT_FN)) {
		scoredat_defaults_set();
	} else {
		scoredat_load();
	}
}

void regist_menu(void)
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

	// For MAINE.EXE, this is done in MAIN.EXE right before launching into the
	// former binary. The verdict screen also needs the multiplied and
	// continue-added value and is always shown before this menu, so it *kinda*
	// makes sense? (Counted as bloat in the header comment.)
#if (BINARY == 'M')
	score *= 10;
	score += resident->continues_used;
#endif

	if(hi.score.score[SCOREDAT_PLACES - 1] > score) {
		scores_put(-1);
		key_delay();
		return;
	}

	for(place = (SCOREDAT_PLACES - 1); place > 0; place--) {
		if(hi.score.score[place-1] > score) {
			break;
		}
	}
	for(shift = (SCOREDAT_PLACES - 1); shift > place; shift--) {
		hi.score.score[shift] = hi.score.score[shift - 1];
		for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
			hi.score.g_name[shift][c] = hi.score.g_name[shift - 1][c];
		}
		hi.score.stage[shift] = hi.score.stage[shift - 1];
		hi.score.date[shift].da_year = hi.score.date[shift - 1].da_year;
		hi.score.date[shift].da_mon = hi.score.date[shift - 1].da_mon;
		hi.score.date[shift].da_day = hi.score.date[shift - 1].da_day;
		hi.score.shottype[shift] = hi.score.shottype[shift - 1];
	}
	hi.score.score[place] = score;

	// ZUN bloat: Could have also been turned into a parameter to avoid
	// compiling this twice.
#if (BINARY == 'E')
	hi.score.stage[place] = STAGE_ALL;
#else
	hi.score.stage[place] = (stage_id + 1);
#endif

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
		ring_direction(coord, (coord_max - 1)); \
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
				// ZUN bloat: Checking against the gaiji values would have been
				// clearer than checking against indices into the alphabet
				// structure.
				if((row != 2) || (col < 13)) {
					hi.score.g_name[place][name_pos] = gALPHABET[row][col];
					if(name_pos == (SCOREDAT_NAME_LEN - 1)) {
						alphabet_putca(col, row, TX_WHITE);
						col = ALPHABET_ENTER_COL;
						row = ALPHABET_ENTER_ROW;
						alphabet_putca(col, row, TX_GREEN | TX_REVERSE);
					}
					clamp_inc(name_pos, (SCOREDAT_NAME_LEN - 1));
				} else if(col == 13) {
					hi.score.g_name[place][name_pos] = gb_SP;
					clamp_inc(name_pos, (SCOREDAT_NAME_LEN - 1));
				} else if(col == 14) {
					clamp_dec(name_pos, 0);
					hi.score.g_name[place][name_pos] = gb_SP;
				} else if(col == 15) {
					clamp_inc(name_pos, (SCOREDAT_NAME_LEN - 1));
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
			if((input_delay > 30) && ((input_delay & 1) == 0)) {
				input_locked = 0;
			}
		} else {
			input_delay = 0;
		}
	} while(1);
	scoredat_save();
}

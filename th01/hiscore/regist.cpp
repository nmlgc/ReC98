// High Score menu
// ---------------

#include <string.h>
#include "platform/x86real/pc98/page.hpp"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/math/clamp.hpp"
#include "th01/hardware/input.hpp"
#include "th01/hardware/graph.h"
#include "th01/formats/scoredat.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/grp2xscs.hpp"
#include "th01/hiscore/regist.hpp"
#include "th01/shiftjis/regist.hpp"

// Null-terminated version of scoredat_name_t, used internally.
typedef ShiftJISKanjiBuffer<SCOREDAT_NAME_KANJI + 1> scoredat_name_z_t;

#define TITLE_LEFT 48
#define TITLE_TOP 0
static const screen_x_t TITLE_BACK_LEFT = 0;
static const screen_y_t TITLE_BACK_TOP = (RES_Y - GLYPH_H);
static const pixel_t TITLE_BACK_W = 288;
static const pixel_t TITLE_BACK_H = GLYPH_H;
static const screen_x_t TITLE_BACK_RIGHT = (TITLE_BACK_LEFT + TITLE_BACK_W);
static const screen_y_t TITLE_BACK_BOTTOM = (TITLE_BACK_TOP + TITLE_BACK_H);

/// Table
/// -----

#define TABLE_TOP 48
#define TABLE_ROW_H GLYPH_H
#define TABLE_BODY_TOP (TABLE_TOP + TABLE_ROW_H)

#define table_row_top(place) (TABLE_BODY_TOP + (place * TABLE_ROW_H))

// Recursively defining column positions \o/
inline screen_x_t table_left(int x_kanji) {
	return 32 + (x_kanji * GLYPH_FULL_W);
}

inline screen_x_t table_place_left(int x_kanji) {
	return table_left(x_kanji);
}

inline screen_x_t table_name_left(int x_kanji) {
	return table_place_left(7 + x_kanji);
}

inline screen_x_t table_score_left(int x_kanji) {
	return table_name_left(SCOREDAT_NAME_KANJI + 5 + x_kanji);
}

inline screen_x_t table_stage_route_left(int x_kanji) {
	return table_score_left(SCORE_DIGITS + 3 + x_kanji);
}

inline screen_x_t table_stage_left(int x_kanji) {
	return table_stage_route_left(1 + x_kanji);
}

// Code generation actually prohibits this from being a Point!
static screen_x_t entered_name_left;
static screen_y_t entered_name_top;
/// -----

void graph_putkanji_fx(
	screen_x_t left, screen_y_t top, int16_t col_and_fx, shiftjis_kanji_t kanji
)
{
	shiftjis_kanji_t str[2];
	str[0] = kanji;
	str[1] = '\0';
	graph_putsa_fx(left, top, col_and_fx, reinterpret_cast<shiftjis_t *>(str));
}

/// Alphabet
/// --------

static const screen_y_t ALPHABET_TOP = 240;
static const pixel_t MARGIN_W = 32;
static const pixel_t KANJI_PADDING_X = 16;
static const pixel_t KANJI_PADDING_Y = 8;

static const pixel_t KANJI_PADDED_W = (GLYPH_FULL_W + KANJI_PADDING_X);
static const pixel_t KANJI_PADDED_H = (GLYPH_H + KANJI_PADDING_Y);

#define KANJI_PER_ROW \
	((RES_X - (MARGIN_W * 2)) / KANJI_PADDED_W)

#define relative_top(row) \
	((row) * KANJI_PADDED_H)

inline pixel_t relative_top_for(int kanji_id) {
	return relative_top(kanji_id / KANJI_PER_ROW);
}

#define row_ceil(count) \
	((count + (KANJI_PER_ROW - 1)) / KANJI_PER_ROW)

#define left_for(kanji_id) \
	((((kanji_id) % KANJI_PER_ROW) * KANJI_PADDED_W) + MARGIN_W)

#define alphabet_putca_fx(top_for_0, i, fx, kanji) { \
	graph_putkanji_fx( \
		left_for(i), (top_for_0 + relative_top_for(i)), fx, kanji \
	); \
}

#define alphabet_putsa_fx(top_for_0, i, fx, str) { \
	graph_putsa_fx(left_for(i), (top_for_0 + relative_top_for(i)), fx, str); \
}

#define A_TO_Z_COUNT 26
#define NUM_COUNT 10
static const int SYM_COUNT = (sizeof(ALPHABET_SYMS) / sizeof(shiftjis_kanji_t));

// Rows
static const screen_y_t LOWER_TOP = ALPHABET_TOP;
static const screen_y_t LOWER2_TOP = (LOWER_TOP + relative_top(1));
static const screen_y_t UPPER_TOP = (
	LOWER_TOP + relative_top(row_ceil(A_TO_Z_COUNT))
);
static const screen_y_t UPPER2_TOP = (UPPER_TOP + relative_top(1));
static const screen_y_t SYM_TOP = (
	UPPER_TOP + relative_top(row_ceil(A_TO_Z_COUNT))
);
static const screen_y_t NUM_TOP = (SYM_TOP + relative_top(row_ceil(SYM_COUNT)));

// Columns
static const screen_x_t A_TO_Z_2_END_LEFT = left_for(
	A_TO_Z_COUNT - KANJI_PER_ROW
);
static const screen_x_t SPACE_LEFT = left_for(NUM_COUNT);
static const screen_x_t LEFT_COLUMN = (KANJI_PER_ROW - 3);
static const screen_x_t LEFT_LEFT =  left_for(LEFT_COLUMN + 0);
static const screen_x_t RIGHT_LEFT = left_for(LEFT_COLUMN + 1);
static const screen_x_t ENTER_LEFT = left_for(LEFT_COLUMN + 2);
/// --------

void alphabet_put_initial()
{
	int16_t col_and_fx = (COL_REGIST_REGULAR | FX_WEIGHT_BOLD);
	shiftjis_kanji_t kanji;
	int i;

	kanji = KANJI_b;
	for(i = 1; i < A_TO_Z_COUNT; i++) {
		alphabet_putca_fx(LOWER_TOP, i, col_and_fx, kanji);
		kanji += 0x100;
	}
	graph_putsa_fx(
		MARGIN_W,
		LOWER_TOP,
		(COL_REGIST_SELECTED | FX_WEIGHT_BOLD | FX_REVERSE),
		ALPHABET_A
	);

	kanji = KANJI_A;
	for(i = 0; i < A_TO_Z_COUNT; i++) {
		alphabet_putca_fx(UPPER_TOP, i, col_and_fx, kanji);
		kanji += 0x100;
	}

	for(i = 0; i < SYM_COUNT; i++) {
		kanji = ALPHABET_SYMS[i];
		alphabet_putca_fx(SYM_TOP, i, col_and_fx, kanji);
	}

	kanji = KANJI_0;
	for(i = 0; i < NUM_COUNT; i++) {
		alphabet_putca_fx(NUM_TOP, i, col_and_fx, kanji);
		kanji += 0x100;
	}
	alphabet_putsa_fx(NUM_TOP, i, col_and_fx, ALPHABET_SPACE);	i = LEFT_COLUMN;
	alphabet_putca_fx(NUM_TOP, i, col_and_fx, KANJI_LEFT); 	i++;
	alphabet_putca_fx(NUM_TOP, i, col_and_fx, KANJI_RIGHT);	i++;
	alphabet_putca_fx(NUM_TOP, i, col_and_fx, KANJI_ENTER);	i++;
}

inline void header_cell_put(screen_x_t left, const char str[]) {
	graph_putsa_fx(
		left, TABLE_TOP, (COL_REGIST_SELECTED | FX_WEIGHT_BLACK), str
	);
}

#define place_cell_put(top, col_and_fx, str) \
	graph_putsa_fx(table_place_left(0), top, col_and_fx, str)

void regist_put_initial(
	int entered_place,
	score_t entered_score,
	int entered_stage,
	shiftjis_kanji_t entered_route,
	const scoredat_name_z_t names_z[SCOREDAT_PLACES]
)
{
	const unsigned char name_blank[SCOREDAT_NAME_BYTES + 1] = REGIST_NAME_BLANK;

	page_access(0);

	header_cell_put(table_place_left(0), REGIST_HEADER_PLACE);
	header_cell_put(table_name_left(0), REGIST_HEADER_NAME);
	header_cell_put(table_score_left(0), REGIST_HEADER_SCORE);
	header_cell_put(table_stage_route_left(0), REGIST_HEADER_STAGE_ROUTE);

	for(int i = 0; i < SCOREDAT_PLACES; i++) {
		#define stage_expr(i, entered_place, expr) \
			(i != entered_place && scoredat_stages[i] expr) || \
			(i == entered_place && entered_stage expr)

		#define col_and_fx_text (place_col | FX_WEIGHT_BOLD)

		vc_t place_col = (
			(i == entered_place) ? COL_REGIST_SELECTED : COL_REGIST_REGULAR
		);
		vram_y_t top = table_row_top(i);

		switch(i) {
		case 0:	place_cell_put(top, col_and_fx_text, REGIST_PLACE_0);	break;
		case 1:	place_cell_put(top, col_and_fx_text, REGIST_PLACE_1);	break;
		case 2:	place_cell_put(top, col_and_fx_text, REGIST_PLACE_2);	break;
		case 3:	place_cell_put(top, col_and_fx_text, REGIST_PLACE_3);	break;
		case 4:	place_cell_put(top, col_and_fx_text, REGIST_PLACE_4);	break;
		case 5:	place_cell_put(top, col_and_fx_text, REGIST_PLACE_5);	break;
		case 6:	place_cell_put(top, col_and_fx_text, REGIST_PLACE_6);	break;
		case 7:	place_cell_put(top, col_and_fx_text, REGIST_PLACE_7);	break;
		case 8:	place_cell_put(top, col_and_fx_text, REGIST_PLACE_8);	break;
		case 9:	place_cell_put(top, col_and_fx_text, REGIST_PLACE_9);	break;
		}
		graph_putsa_fx(
			table_name_left(0),
			top,
			col_and_fx_text,
			(i == entered_place) ? name_blank : names_z[i].byte
		);
		graph_putfwnum_fx(
			table_score_left(0),
			top,
			(place_col | FX_WEIGHT_BLACK),
			SCORE_DIGITS,
			(entered_place == i) ? entered_score : scoredat_score[i],
			0,
			false
		);
		if(stage_expr(i, entered_place, < SCOREDAT_CLEARED)) {
			graph_putfwnum_fx(
				table_stage_left(0),
				top,
				col_and_fx_text,
				2,
				(i == entered_place) ? entered_stage : scoredat_stages[i],
				0,
				false
			);
		} else if(stage_expr(i, entered_place, == SCOREDAT_CLEARED_MAKAI)) {
			graph_putsa_fx(
				table_stage_left(0), top, col_and_fx_text, REGIST_STAGE_MAKAI
			);
		} else if(stage_expr(i, entered_place, == SCOREDAT_CLEARED_JIGOKU)) {
			graph_putsa_fx(
				table_stage_left(0), top, col_and_fx_text, REGIST_STAGE_JIGOKU
			);
		}
		graph_putsa_fx(
			table_stage_left(2), top, col_and_fx_text, REGIST_STAGE_ROUTE_DASH
		);
		graph_putkanji_fx(
			table_stage_left(3),
			top,
			col_and_fx_text,
			(i == entered_place) ? entered_route : scoredat_routes[i]
		);
		if(entered_place == i) {
			entered_name_left = table_name_left(0);
			entered_name_top = table_row_top(i);
		}
		#undef col_and_fx_text
		#undef stage_expr
	}
}

shiftjis_kanji_t alphabet_kanji_at(screen_x_t left, screen_y_t top)
{
	const int column = ((left - left_for(0)) / KANJI_PADDED_W);
	switch(top) {
	case LOWER_TOP: 	return (KANJI_a + (column * 0x100));
	case LOWER2_TOP:	return (KANJI_a + ((column + KANJI_PER_ROW) * 0x100));
	case UPPER_TOP: 	return (KANJI_A + (column * 0x100));
	case UPPER2_TOP:	return (KANJI_A + ((column + KANJI_PER_ROW) * 0x100));
	case SYM_TOP:   	return ALPHABET_SYMS[column];
	case NUM_TOP:
		if(left < SPACE_LEFT) {
			return (KANJI_0 + (column * 0x100));
		} else if(left == SPACE_LEFT) {
			return KANJI_SPACE;
		} else if(left == LEFT_LEFT) {
			return KANJI_LEFT;
		} else if(left == RIGHT_LEFT) {
			return KANJI_RIGHT;
		} else if(left == ENTER_LEFT) {
			return KANJI_ENTER;
		}
	}
	return '\0';
}

void alphabet_put_at(screen_x_t left, screen_y_t top, bool16 is_selected)
{
	shiftjis_kanji_t kanji = alphabet_kanji_at(left, top);

	egc_copy_rect_1_to_0_16(left, top, KANJI_PADDED_W, GLYPH_H);

	int16_t col_and_fx = (FX_WEIGHT_BOLD | (
		!is_selected ? COL_REGIST_REGULAR : (FX_REVERSE | COL_REGIST_SELECTED)
	));

	switch(kanji) {
	case '\0':
		break;
	case KANJI_SPACE:
		graph_putsa_fx(left, top, col_and_fx, ALPHABET_SPACE);
		break;
	default:
		graph_putkanji_fx(left, top, col_and_fx, kanji);
		break;
	}
}

enum regist_shot_ret_t {
	RS_REGULAR = 0,
	RS_ENTER = 1,
	RS_NAME_CURSOR_AT_END = 2,
};

regist_shot_ret_t regist_on_shot(
	screen_x_t left,
	screen_y_t top,
	scoredat_name_z_t &entered_name,
	int &entered_name_cursor
)
{
	regist_shot_ret_t ret = RS_REGULAR;
	shiftjis_kanji_t kanji = alphabet_kanji_at(left, top);

	switch(kanji) {
	case '\0':
		break;
	case KANJI_LEFT:
		clamp_dec(entered_name_cursor, 0);
		break;
	case KANJI_RIGHT:
		clamp_inc(entered_name_cursor, (SCOREDAT_NAME_KANJI - 1));
		break;
	case KANJI_ENTER:
		return RS_ENTER;
	default:
		entered_name.t[entered_name_cursor] = kanji;
		if(entered_name_cursor < (SCOREDAT_NAME_KANJI - 1)) {
			entered_name_cursor++;
		} else {
			ret = RS_NAME_CURSOR_AT_END;
		}
		break;
	}

	egc_copy_rect_1_to_0_16(
		entered_name_left,
		entered_name_top,
		(SCOREDAT_NAME_KANJI * GLYPH_FULL_W),
		GLYPH_H
	);
	graph_putsa_fx(
		entered_name_left,
		entered_name_top,
		(COL_REGIST_SELECTED | FX_WEIGHT_BOLD),
		entered_name.ubyte
	);

	graph_putkanji_fx(
		(entered_name_left + (entered_name_cursor * GLYPH_FULL_W)), entered_name_top,
		COL_REGIST_SELECTED,
		KANJI_UNDERSCORE
	);
	return ret;
}

enum regist_input_ret_t {
	RI_REGULAR = 0,
	RI_ENTER = 1,
	RI_NONE = 2,

	_regist_input_ret_t_FORCE_INT16 = 0x7FFF
};

regist_input_ret_t regist_on_input(
	screen_x_t &left, screen_y_t &top,
	scoredat_name_z_t& entered_name, int& entered_name_cursor,
	bool jump_to_enter_when_name_cursor_at_end
)
{
	if(input_up == true) {
		alphabet_put_at(left, top, false);

		top -= KANJI_PADDED_H;
		if(top < LOWER_TOP) {
			top = NUM_TOP;
		}
		if(top == LOWER2_TOP && left >= A_TO_Z_2_END_LEFT) {
			top = LOWER_TOP;
		}
		if(top == UPPER2_TOP && left >= A_TO_Z_2_END_LEFT) {
			top = UPPER_TOP;
		}
		if(top == NUM_TOP && left > SPACE_LEFT && left < LEFT_LEFT) {
			top = SYM_TOP;
		}

		alphabet_put_at(left, top, true);
		input_up = false;
	} else if(input_down == true) {
		alphabet_put_at(left, top, false);

		top += KANJI_PADDED_H;
		if(top > NUM_TOP) {
			top = LOWER_TOP;
		}
		if(top == LOWER2_TOP && left >= A_TO_Z_2_END_LEFT) {
			top = UPPER_TOP;
		}
		if(top == UPPER2_TOP && left >= A_TO_Z_2_END_LEFT) {
			top = SYM_TOP;
		}
		if(top == NUM_TOP && left > SPACE_LEFT && left < LEFT_LEFT) {
			top = LOWER_TOP;
		}

		alphabet_put_at(left, top, true);
		input_down = false;
	} else if(input_lr == INPUT_LEFT) {
		alphabet_put_at(left, top, false);

		left -= KANJI_PADDED_W;
		if(left < left_for(0)) {
			left = left_for(KANJI_PER_ROW - 1);
		}
		if(top == LOWER2_TOP && left >= A_TO_Z_2_END_LEFT) {
			left = left_for(A_TO_Z_COUNT - 1);
		}
		if(top == UPPER2_TOP && left >= A_TO_Z_2_END_LEFT) {
			left = left_for(A_TO_Z_COUNT - 1);
		}
		if(top == NUM_TOP && left > SPACE_LEFT && left < LEFT_LEFT) {
			left = SPACE_LEFT;
		}

		alphabet_put_at(left, top, true);
		input_lr = 0;
	} else if(input_lr == INPUT_RIGHT) {
		alphabet_put_at(left, top, false);

		left += KANJI_PADDED_W;
		if(left > left_for(KANJI_PER_ROW - 1)) {
			left = left_for(0);
		}
		if(top == LOWER2_TOP && left >= A_TO_Z_2_END_LEFT) {
			left = left_for(0);
		}
		if(top == UPPER2_TOP && left >= A_TO_Z_2_END_LEFT) {
			left = left_for(0);
		}
		if(top == NUM_TOP && left > SPACE_LEFT && left < LEFT_LEFT) {
			left = LEFT_LEFT;
		}

		alphabet_put_at(left, top, true);
		input_lr = 0;
	} else if(input_shot == true) {
		switch(regist_on_shot(left, top, entered_name, entered_name_cursor)) {
		case RS_REGULAR:
			break;
		case RS_ENTER:
			return RI_ENTER;
		case RS_NAME_CURSOR_AT_END:
			if(jump_to_enter_when_name_cursor_at_end) {
				alphabet_put_at(left, top, false);

				left = ENTER_LEFT;
				top = NUM_TOP;

				alphabet_put_at(left, top, true);
			}
			break;
		}
		input_shot = false;
	} else if(input_strike == true) {
		regist_on_shot(LEFT_LEFT, NUM_TOP, entered_name, entered_name_cursor);
		input_strike = false;
	} else {
		return RI_NONE;
	}
	return RI_REGULAR;
}

void regist_name_enter(int entered_place, bool cleared)
{
	// The Game Over variant in REIIDEN.EXE features a hidden timeout that
	// force-enters a high score name after 1000… *keyboard inputs*? Not
	// frames? Why. Like, how do you even realistically get to such a number.
	// (Best guess: It's a hidden easter egg to amuse players who place
	// drinking glasses on cursor keys. Or beer bottles.)
	unsigned int timeout = 0;

	scoredat_name_z_t entered_name;
	screen_x_t left;
	screen_y_t top;
	int entered_name_cursor;
	int i;

	entered_name_cursor = 0;
	left = left_for(0);
	top = LOWER_TOP;

	for(i = 0; i < SCOREDAT_NAME_BYTES; i++) {
		entered_name.ubyte[i] = ' ';
	}
	entered_name.ubyte[SCOREDAT_NAME_BYTES] = '\0';

	input_reset_sense();
	while(1) {
		input_sense(false);
		int input_ret = regist_on_input(
			left, top, entered_name, entered_name_cursor, !cleared
		);
		// Code generation for FUUIN.EXE forces these to be in separate
		// statements...
		if(input_ret == RI_ENTER) {
			break;
		}
		if(input_ok) {
			break;
		}
		if(!cleared && (timeout > 1000)) {
			break;
		}
		if(input_ret == RI_NONE) {
			continue;
		}
		frame_delay(4);
		timeout++;
	}
	input_ok = false;
	for(i = 0; i < SCOREDAT_NAME_BYTES; i++) {
		scoredat_names[
			(entered_place * SCOREDAT_NAME_BYTES) + i
		] = entered_name.ubyte[i];
	}
	scoredat_save();
}

static const int PLACE_NONE = (SCOREDAT_PLACES + 20);

void regist_menu(
	score_t score,
	int16_t stage_num_or_scoredat_constant,
	shiftjis_kanji_t route
)
{
	const bool cleared = (
		stage_num_or_scoredat_constant >= (SCOREDAT_CLEARED - 10)
	);
	scoredat_name_z_t names[SCOREDAT_PLACES];
	long place;

	page_access(1);
	graph_putsa_fx(
		TITLE_BACK_LEFT,
		(cleared ? TITLE_TOP : TITLE_BACK_TOP),
		(COL_REGIST_REGULAR | FX_WEIGHT_BOLD | FX_CLEAR_BG),
		REGIST_TITLE[rank]
	);

	if(!cleared) {
		graph_2xscale_byterect_1_to_0_slow(
			TITLE_LEFT, TITLE_TOP,
			TITLE_BACK_LEFT, TITLE_BACK_TOP, TITLE_BACK_W, TITLE_BACK_H
		);
		graph_move_byterect_interpage(
			TITLE_BACK_LEFT, TITLE_BACK_TOP,
			TITLE_BACK_RIGHT, TITLE_BACK_BOTTOM,
			TITLE_BACK_LEFT, TITLE_BACK_TOP,
			0
		);
		page_access(0);
	} else {
		graph_2xscale_byterect_1_to_0_slow(
			TITLE_LEFT, TITLE_TOP,
			TITLE_BACK_LEFT, TITLE_TOP, TITLE_BACK_W, TITLE_BACK_H
		);
	}

	if(scoredat_load()) {
		return;
	}
	for(place = 0; place < SCOREDAT_PLACES; place++) {
		scoredat_name_get(place, names[place].ubyte);
	}
	for(place = 0; place < SCOREDAT_PLACES; place++) {
		if(score >= scoredat_score[place]) {
			break;
		}
	}

	input_reset_sense();

	if(place < SCOREDAT_PLACES) {
		for(long shift = (SCOREDAT_PLACES - 1); shift > place; shift--) {
			strcpy(names[shift].byte, names[shift - 1].byte);
			scoredat_score[shift] = scoredat_score[shift - 1];
			scoredat_stages[shift] = scoredat_stages[shift - 1];
			scoredat_routes[shift] = scoredat_routes[shift - 1];
		}
		long p = (SCOREDAT_NAMES_SIZE - 1);
		while(((place * SCOREDAT_NAME_BYTES) + SCOREDAT_NAME_BYTES) <= p) {
			scoredat_names[p] = scoredat_names[p - SCOREDAT_NAME_BYTES];
			p--;
		}
		regist_put_initial(
			place, score, stage_num_or_scoredat_constant, route, names
		);
		alphabet_put_initial();

		scoredat_score[place] = score;
		scoredat_stages[place] = stage_num_or_scoredat_constant;
		scoredat_routes[place] = route;

		// Writes the new name to scoredat_names[] and calls scoredat_save()
		regist_name_enter(place, cleared);

		scoredat_free();
		return;
	}
	regist_put_initial(
		PLACE_NONE, score, stage_num_or_scoredat_constant, route, names
	);
	input_ok = true;
	input_shot = true;
	while(1) {
		input_sense(false);
		if(!input_ok || !input_shot) {
			break;
		}
	}
	scoredat_free();
}

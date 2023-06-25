#include "th01/math/clamp.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/grp2xscs.hpp"
#include "th01/v_colors.hpp"
#include "th01/score.h"
#include "th01/hiscore/regist.hpp"

// Null-terminated version of scoredat_name_t, used internally.
typedef ShiftJISKanjiBuffer<SCOREDAT_NAME_KANJI + 1> scoredat_name_z_t;

// Byte-wise access to [scoredat_routes].
inline int8_t& scoredat_route_byte(int place, int byte) {
	if(byte == 0) {
		return scoredat_routes[place * SCOREDAT_ROUTE_LEN];
	}
	return scoredat_routes[(place * SCOREDAT_ROUTE_LEN) + byte];
}

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
	graph_printf_fx(left_for(i), (top_for_0 + relative_top_for(i)), fx, str); \
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

inline uint8_t kanji_hi(sshiftjis_kanji_swapped_t kanji) {
	return (kanji >> 8);
}

inline uint8_t kanji_lo(sshiftjis_kanji_swapped_t kanji) {
	return (kanji & 0xFF);
}
/// --------

void alphabet_put_initial()
{
	int16_t col_and_fx = (COL_REGIST_REGULAR | FX_WEIGHT_BOLD);
	shiftjis_kanji_swapped_t kanji;
	int i;
	graph_putkanji_fx_declare();

	kanji = KANJI_b;
	for(i = 1; i < A_TO_Z_COUNT; i++) {
		alphabet_putca_fx(LOWER_TOP, i, col_and_fx, kanji);
		kanji++;
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
		kanji++;
	}

	for(i = 0; i < SYM_COUNT; i++) {
		kanji = ALPHABET_SYMS[i];
		alphabet_putca_fx(SYM_TOP, i, col_and_fx, kanji);
	}

	kanji = KANJI_0;
	for(i = 0; i < NUM_COUNT; i++) {
		alphabet_putca_fx(NUM_TOP, i, col_and_fx, kanji);
		kanji++;
	}
	alphabet_putsa_fx(NUM_TOP, i, col_and_fx, ALPHABET_SPACE);	i = LEFT_COLUMN;
	alphabet_putsa_fx(NUM_TOP, i, col_and_fx, ALPHABET_LEFT); 	i++;
	alphabet_putsa_fx(NUM_TOP, i, col_and_fx, ALPHABET_RIGHT);	i++;
	alphabet_putsa_fx(NUM_TOP, i, col_and_fx, ALPHABET_ENTER);	i++;
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
	const sshiftjis_t entered_route[SCOREDAT_ROUTE_LEN + 1],
	const scoredat_name_z_t names_z[SCOREDAT_PLACES]
)
{
	const unsigned char name_blank[SCOREDAT_NAME_BYTES + 1] = REGIST_NAME_BLANK;

	graph_accesspage_func(0);

	header_cell_put(table_place_left(0), REGIST_HEADER_PLACE);
	header_cell_put(table_name_left(0), REGIST_HEADER_NAME);
	header_cell_put(table_score_left(0), REGIST_HEADER_SCORE);
	header_cell_put(table_stage_route_left(0), REGIST_HEADER_STAGE_ROUTE);

	for(int i = 0; i < SCOREDAT_PLACES; i++) {
		#define stage_expr(i, entered_place, expr) \
			(i != entered_place && scoredat_stages[i] expr) || \
			(i == entered_place && entered_stage expr)

		#define col_and_fx_text (place_col | FX_WEIGHT_BOLD)

		#if (BINARY == 'E')
			#define place_col ((i == entered_place) \
				? COL_REGIST_SELECTED \
				: COL_REGIST_REGULAR \
			)
			#define top table_row_top(i)
		#else
			vc2 place_col = (
				(i == entered_place) ? COL_REGIST_SELECTED : COL_REGIST_REGULAR
			);
			vram_y_t top = table_row_top(i);
		#endif

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
		regist_route_put(
			table_stage_left(3),
			top,
			col_and_fx_text,
			(i == entered_place) ? entered_route[0] : scoredat_route_byte(i, 0),
			(i == entered_place) ? entered_route[1] : scoredat_route_byte(i, 1)
		);
		if(entered_place == i) {
			entered_name_left = table_name_left(0);
			entered_name_top = table_row_top(i);
		}
		#undef top
		#undef place_col
		#undef col_and_fx_text
		#undef stage_expr
	}
}

#define alphabet_left_to_column(left) \
	((left - left_for(0)) / KANJI_PADDED_W)

#define alphabet_if(kanji, left, top, on_space, on_left, on_right, on_enter) \
	if(top == LOWER_TOP) { \
		kanji = (KANJI_a + alphabet_left_to_column(left)); \
	} else if(top == LOWER2_TOP) { \
		kanji = (KANJI_a + alphabet_left_to_column(left)) + KANJI_PER_ROW; \
	} else if(top == UPPER_TOP) { \
		kanji = (KANJI_A + alphabet_left_to_column(left)); \
	} else if(top == UPPER2_TOP) { \
		kanji = (KANJI_A + alphabet_left_to_column(left)) + KANJI_PER_ROW; \
	} else if(top == SYM_TOP) { \
		kanji = ALPHABET_SYMS[alphabet_left_to_column(left)]; \
	} else if(top == NUM_TOP && left < SPACE_LEFT) { \
		kanji = (KANJI_0 + alphabet_left_to_column(left)); \
	} else if((top == NUM_TOP) && (left == SPACE_LEFT)) { \
		on_space \
	} else if((top == NUM_TOP) && (left == LEFT_LEFT)) { \
		on_left \
	} else if((top == NUM_TOP) && (left == RIGHT_LEFT)) { \
		on_right \
	} else if((top == NUM_TOP) && (left == ENTER_LEFT)) { \
		on_enter \
	}

void alphabet_put_at(screen_x_t left, screen_y_t top, bool16 is_selected)
{
	sshiftjis_kanji_swapped_t kanji = '\0';

	egc_copy_rect_1_to_0_16(left, top, KANJI_PADDED_W, GLYPH_H);

	int16_t col_and_fx = (FX_WEIGHT_BOLD | (
		!is_selected ? COL_REGIST_REGULAR : (FX_REVERSE | COL_REGIST_SELECTED)
	));

	alphabet_if(kanji, left, top,
		{ graph_printf_fx(left, top, col_and_fx, ALPHABET_SPACE); },
		{ graph_printf_fx(left, top, col_and_fx, ALPHABET_LEFT); },
		{ graph_printf_fx(left, top, col_and_fx, ALPHABET_RIGHT); },
		{ graph_printf_fx(left, top, col_and_fx, ALPHABET_ENTER); }
	);
	if(kanji != '\0') {
		graph_putkanji_fx_declare();
		graph_putkanji_fx(left, top, col_and_fx, kanji);
	}
}

#if (BINARY == 'M')
	bool regist_jump_to_enter = false;
#endif

#define set_kanji_at(name, pos, kanji) { \
	name[(pos * 2) + 0] = kanji_hi(kanji); \
	name[(pos * 2) + 1] = kanji_lo(kanji); \
}

int regist_on_shot(
	screen_x_t left,
	screen_y_t top,
	scoredat_name_z_t &entered_name,
	int &entered_name_cursor
)
{
	shiftjis_kanji_swapped_t kanji = '\0';
	shiftjis_t cursor_str[SCOREDAT_NAME_BYTES + 1] = REGIST_NAME_SPACES;

	alphabet_if(kanji, left, top,
		{ kanji = KANJI_SP; },
		{ clamp_dec(entered_name_cursor, 0); },
		{ clamp_inc(entered_name_cursor, (SCOREDAT_NAME_KANJI - 1)); },
		{ return 1; }
	);

	if(kanji != '\0') {
		set_kanji_at(entered_name.ubyte, entered_name_cursor, kanji);
		#if (BINARY == 'M')
			if(entered_name_cursor == (SCOREDAT_NAME_KANJI - 1)) {
				regist_jump_to_enter = true;
			}
		#endif
		if(entered_name_cursor < (SCOREDAT_NAME_KANJI - 1)) {
			entered_name_cursor++;
		}
	}

	egc_copy_rect_1_to_0_16(
		entered_name_left,
		entered_name_top,
		(SCOREDAT_NAME_KANJI * GLYPH_FULL_W),
		GLYPH_H
	);
	graph_printf_s_fx(
		entered_name_left,
		entered_name_top,
		(COL_REGIST_SELECTED | FX_WEIGHT_BOLD),
		entered_name.ubyte
	);

	set_kanji_at(cursor_str, entered_name_cursor, KANJI_UNDERSCORE);
	graph_printf_s_fx(
		entered_name_left, entered_name_top, COL_REGIST_SELECTED, cursor_str
	);
	return 0;
}

enum regist_input_ret_t {
	RI_REGULAR = 0,
	RI_ENTER = 1,
	RI_NONE = 2,

	_regist_input_ret_t_FORCE_INT16 = 0x7FFF
};

regist_input_ret_t regist_on_input(
	screen_x_t &left, screen_y_t &top,
	scoredat_name_z_t& entered_name, int& entered_name_cursor
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
		if(regist_on_shot(left, top, entered_name, entered_name_cursor)) {
			return RI_ENTER;
		}
		#if (BINARY == 'M')
			if(regist_jump_to_enter) {
				alphabet_put_at(left, top, false);

				left = ENTER_LEFT;
				top = NUM_TOP;

				alphabet_put_at(left, top, true);
				regist_jump_to_enter = false;
			}
		#endif
		input_shot = false;
	} else if(input_strike == true) {
		regist_on_shot(LEFT_LEFT, NUM_TOP, entered_name, entered_name_cursor);
		input_strike = false;
	} else {
		return RI_NONE;
	}
	return RI_REGULAR;
}

#if (BINARY == 'E')
	inline void scoredat_free(void) {
#else
	void scoredat_free(void)
{
#endif
	delete[] scoredat_names;
	delete[] scoredat_stages;
	delete[] scoredat_routes;
	delete[] scoredat_score;
}

void scoredat_save(void)
{
	FILE* fp;
	const char magic[sizeof(SCOREDAT_MAGIC)] = SCOREDAT_MAGIC; // ZUN bloat
	char fn[16];
	scoredat_fn(fn);

	if( (fp = fopen(fn, "wb")) == nullptr) {
		return;
	}
	write(fileno(fp), magic, sizeof(SCOREDAT_MAGIC) - 1);
	for(int i = 0; i < SCOREDAT_NAMES_SIZE; i++) {
		scoredat_names[i] = scoredat_name_byte_encode(scoredat_names[i]);
	}
	write(fileno(fp), scoredat_names, SCOREDAT_NAMES_SIZE);
	write(fileno(fp), scoredat_score, (sizeof(score_t) * SCOREDAT_PLACES));
	write(fileno(fp), scoredat_stages, (sizeof(int16_t) * SCOREDAT_PLACES));
	write(
		fileno(fp),
		scoredat_routes,
		(sizeof(shiftjis_kanji_t) * SCOREDAT_PLACES)
	);
	fclose(fp);
}

void regist_name_enter(int entered_place)
{
	scoredat_name_z_t entered_name;
	regist_input_timeout_declare();
	screen_x_t left;
	screen_y_t top;
	int entered_name_cursor;
	int i;

	entered_name_cursor = 0;
	regist_input_timeout_reset();
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
			left, top, entered_name, entered_name_cursor
		);
		// Code generation for FUUIN.EXE forces these to be in separate
		// statements...
		if(input_ret == RI_ENTER) {
			break;
		}
		if(input_ok) {
			break;
		}
		regist_input_timeout_if_reached({ break; });
		if(input_ret == RI_NONE) {
			continue;
		}
		frame_delay(4);
		regist_input_timeout_inc();
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
static const int SCOREDAT_NOT_CLEARED = (SCOREDAT_CLEARED - 10);

void regist(
	score_t score,
	int16_t stage_num_or_scoredat_constant,
	const sshiftjis_t route[SCOREDAT_ROUTE_LEN + 1]
)
{
	scoredat_name_z_t names[SCOREDAT_PLACES];
	const shiftjis_t* RANKS[RANK_COUNT] = REGIST_TITLE_RANKS;
	long place;

	regist_bg_put(stage_num_or_scoredat_constant);

	graph_accesspage_func(1);

	regist_title_put(
		TITLE_BACK_LEFT,
		stage_num_or_scoredat_constant,
		RANKS,
		(COL_REGIST_REGULAR | FX_WEIGHT_BOLD | FX_CLEAR_BG)
	);
	// On page 1, the title should now at (TITLE_BACK_LEFT, TITLE_BACK_TOP) if
	// not cleared, or at (TITLE_BACK_LEFT, TITLE_TOP) if cleared.

	graph_accesspage_func(0);
	if(stage_num_or_scoredat_constant < SCOREDAT_NOT_CLEARED) {
		graph_2xscale_byterect_1_to_0_slow(
			TITLE_LEFT, TITLE_TOP,
			TITLE_BACK_LEFT, TITLE_BACK_TOP, TITLE_BACK_W, TITLE_BACK_H
		);
		graph_move_byterect_interpage(
			TITLE_BACK_LEFT, TITLE_BACK_TOP,
			TITLE_BACK_RIGHT, TITLE_BACK_BOTTOM,
			TITLE_BACK_LEFT, TITLE_BACK_TOP,
			0, 1
		);
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
			scoredat_route_byte(shift, 0) = scoredat_route_byte(shift, -2);
			scoredat_route_byte(shift, 1) = scoredat_route_byte(shift, -1);
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
		scoredat_route_byte(place, 0) = route[0];
		scoredat_route_byte(place, 1) = route[1];

		// Writes the new name to scoredat_names[] and calls scoredat_save()
		regist_name_enter(place);

		_ES = FP_SEG(graph_accesspage_func); // Yes, no point to this at all.
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
	_ES = FP_SEG(graph_accesspage_func); // Yes, no point to this at all.
	scoredat_free();
}

// Global state that is defined here for some reason
// -------------------------------------------------

score_t* scoredat_score;
// -------------------------------------------------

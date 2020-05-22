#include "th01/hardware/egc.h"
#include "th01/hardware/grp2xscs.h"
#include "th01/hardware/input.hpp"
#include "th01/hardware/vsync.h"

#define COL_SELECTED 3
#define COL_REGULAR 7

#define TITLE_LEFT 48
#define TITLE_TOP 0
static const int TITLE_BACK_LEFT = 0;
static const int TITLE_BACK_TOP = (RES_Y - GLYPH_H);
static const int TITLE_BACK_W = 288;
static const int TITLE_BACK_H = GLYPH_H;
static const int TITLE_BACK_RIGHT = (TITLE_BACK_LEFT + TITLE_BACK_W);
static const int TITLE_BACK_BOTTOM = (TITLE_BACK_TOP + TITLE_BACK_H);

/// Table
/// -----
#define POINT_DIGITS 7

#define TABLE_TOP 48
#define TABLE_ROW_H GLYPH_H
#define TABLE_BODY_TOP (TABLE_TOP + TABLE_ROW_H)

#define table_row_top(place) (TABLE_BODY_TOP + (place * TABLE_ROW_H))

// Recursively defining column positions \o/
inline int table_left(int x_kanji) {
	return 32 + (x_kanji * GLYPH_FULL_W);
}

inline int table_place_left(int x_kanji) {
	return table_left(x_kanji);
}

inline int table_name_left(int x_kanji) {
	return table_place_left(7 + x_kanji);
}

inline int table_points_left(int x_kanji) {
	return table_name_left(SCOREDAT_NAME_KANJI + 5 + x_kanji);
}

inline int table_stage_route_left(int x_kanji) {
	return table_points_left(POINT_DIGITS + 3 + x_kanji);
}

inline int table_stage_left(int x_kanji) {
	return table_stage_route_left(1 + x_kanji);
}

// Code generation actually prohibits this from being a Point!
extern int entered_name_left;
extern int entered_name_top;
/// -----

/// Alphabet
/// --------
#define ALPHABET_TOP 240
#define MARGIN_W 32
#define KANJI_PADDING_X 16
#define KANJI_PADDING_Y 8

#define KANJI_PADDED_W (GLYPH_FULL_W + KANJI_PADDING_X)
#define KANJI_PADDED_H (GLYPH_H + KANJI_PADDING_Y)

#define KANJI_PER_ROW \
	((RES_X - (MARGIN_W * 2)) / KANJI_PADDED_W)

#define relative_top(row) \
	((row) * KANJI_PADDED_H)

inline int relative_top_for(int kanji_id)
{
	return relative_top(kanji_id / KANJI_PER_ROW);
}

inline int row_ceil(int count)
{
	return ((count + (KANJI_PER_ROW - 1)) / KANJI_PER_ROW);
}

inline int left_for(int kanji_id)
{
	return (((kanji_id % KANJI_PER_ROW) * KANJI_PADDED_W) + MARGIN_W);
}

#define alphabet_putca_fx(top_for_0, i, fx, fmt_instance, kanji) \
	graph_putkanji_fx( \
		left_for(i), (top_for_0 + relative_top_for(i)), fx, fmt_instance, kanji \
	);

#define alphabet_putsa_fx(top_for_0, i, fx, str) \
	extern const char str[]; \
	graph_printf_fx(left_for(i), (top_for_0 + relative_top_for(i)), fx, str);

#define A_TO_Z_COUNT 26
#define NUM_COUNT 10
// TODO: Should be derived via `sizeof()` once the array is declared here.
#define SYM_COUNT 18
extern const uint16_t ALPHABET_SYMS[];

// Rows
#define LOWER_TOP (ALPHABET_TOP)
#define LOWER2_TOP (LOWER_TOP + relative_top(1))
#define UPPER_TOP (LOWER_TOP + relative_top(row_ceil(A_TO_Z_COUNT)))
#define UPPER2_TOP (UPPER_TOP + relative_top(1))
#define SYM_TOP (UPPER_TOP + relative_top(row_ceil(A_TO_Z_COUNT)))
#define NUM_TOP (SYM_TOP + relative_top(row_ceil(SYM_COUNT)))

// Columns
#define A_TO_Z_2_END_LEFT left_for(A_TO_Z_COUNT - KANJI_PER_ROW)
#define SPACE_LEFT left_for(NUM_COUNT)
#define LEFT_COLUMN (KANJI_PER_ROW - 3)
#define LEFT_LEFT  left_for(LEFT_COLUMN + 0)
#define RIGHT_LEFT left_for(LEFT_COLUMN + 1)
#define ENTER_LEFT left_for(LEFT_COLUMN + 2)

inline uint16_t kanji_swap(uint16_t kanji)
{
	return (kanji << 8) | (kanji >> 8);
}

inline unsigned char kanji_hi(int16_t kanji)
{
	return (kanji >> 8);
}

inline unsigned char kanji_lo(int16_t kanji)
{
	return (kanji & 0xFF);
}
/// --------

void alphabet_put_initial()
{
	int fx = FX(COL_REGULAR, 2, 0);
	uint16_t kanji;
	int i;
#if (BINARY == 'M')
	char kanji_str[3];
#endif

	kanji = kanji_swap('‚‚');
	for(i = 1; i < A_TO_Z_COUNT; i++) {
		alphabet_putca_fx(LOWER_TOP, i, fx, 0, kanji);
		kanji++;
	}
	extern const char ALPHABET_A[];
	graph_putsa_fx(
		MARGIN_W, LOWER_TOP, FX_REVERSE | FX(COL_SELECTED, 2, 0), ALPHABET_A
	);

	kanji = kanji_swap('‚`');
	for(i = 0; i < A_TO_Z_COUNT; i++) {
		alphabet_putca_fx(UPPER_TOP, i, fx, 1, kanji);
		kanji++;
	}

	for(i = 0; i < SYM_COUNT; i++) {
		kanji = ALPHABET_SYMS[i];
		alphabet_putca_fx(SYM_TOP, i, fx, 2, kanji);
	}

	kanji = kanji_swap('‚O');
	for(i = 0; i < NUM_COUNT; i++) {
		alphabet_putca_fx(NUM_TOP, i, fx, 3, kanji);
		kanji++;
	}
	alphabet_putsa_fx(NUM_TOP, i, fx, ALPHABET_SPACE);	i = LEFT_COLUMN;
	alphabet_putsa_fx(NUM_TOP, i, fx, ALPHABET_LEFT); 	i++;
	alphabet_putsa_fx(NUM_TOP, i, fx, ALPHABET_RIGHT);	i++;
	alphabet_putsa_fx(NUM_TOP, i, fx, ALPHABET_ENTER);	i++;
}

inline void header_cell_put(int left, const char str[])
{
	graph_putsa_fx(left, TABLE_TOP, FX(COL_SELECTED, 3, 0), str);
}

#define place_cell_put(top, fx, str) \
	graph_putsa_fx(table_place_left(0), top, fx, str)

void regist_put_initial(
	int entered_place,
	long entered_points,
	int entered_stage,
	const char entered_route[SCOREDAT_ROUTE_LEN + 1],
	const scoredat_name_z_t names_z[SCOREDAT_PLACES]
)
{
	struct hack {
		unsigned char byte[SCOREDAT_NAME_BYTES + 1];
	};
	extern const hack REGIST_NAME_BLANK;
	extern const char REGIST_HEADER_PLACE[];
	extern const char REGIST_HEADER_NAME[];
	extern const char REGIST_HEADER_POINTS[];
	extern const char REGIST_HEADER_STAGE_ROUTE[];
	extern const char REGIST_PLACE_0[];
	extern const char REGIST_PLACE_1[];
	extern const char REGIST_PLACE_2[];
	extern const char REGIST_PLACE_3[];
	extern const char REGIST_PLACE_4[];
	extern const char REGIST_PLACE_5[];
	extern const char REGIST_PLACE_6[];
	extern const char REGIST_PLACE_7[];
	extern const char REGIST_PLACE_8[];
	extern const char REGIST_PLACE_9[];
	extern const char REGIST_STAGE_MAKAI[];
	extern const char REGIST_STAGE_JIGOKU[];
	extern const char REGIST_STAGE_ROUTE_DASH[];

	hack name = REGIST_NAME_BLANK;

	graph_accesspage_func(0);

	header_cell_put(table_place_left(0), REGIST_HEADER_PLACE);
	header_cell_put(table_name_left(0), REGIST_HEADER_NAME);
	header_cell_put(table_points_left(0), REGIST_HEADER_POINTS);
	header_cell_put(table_stage_route_left(0), REGIST_HEADER_STAGE_ROUTE);

	for(int i = 0; i < SCOREDAT_PLACES; i++) {
		#define stage_expr(i, entered_place, expr) \
			(i != entered_place && scoredat_stages[i] expr) || \
			(i == entered_place && entered_stage expr)

		#define fx_text FX(place_col, 2, 0)

		#if (BINARY == 'E')
		# define place_col ((i == entered_place) ? COL_SELECTED : COL_REGULAR)
		# define top table_row_top(i)
		#else
			int place_col = (i == entered_place) ? COL_SELECTED : COL_REGULAR;
			int top = table_row_top(i);
		#endif

		switch(i) {
		case 0:	place_cell_put(top, fx_text, REGIST_PLACE_0);	break;
		case 1:	place_cell_put(top, fx_text, REGIST_PLACE_1);	break;
		case 2:	place_cell_put(top, fx_text, REGIST_PLACE_2);	break;
		case 3:	place_cell_put(top, fx_text, REGIST_PLACE_3);	break;
		case 4:	place_cell_put(top, fx_text, REGIST_PLACE_4);	break;
		case 5:	place_cell_put(top, fx_text, REGIST_PLACE_5);	break;
		case 6:	place_cell_put(top, fx_text, REGIST_PLACE_6);	break;
		case 7:	place_cell_put(top, fx_text, REGIST_PLACE_7);	break;
		case 8:	place_cell_put(top, fx_text, REGIST_PLACE_8);	break;
		case 9:	place_cell_put(top, fx_text, REGIST_PLACE_9);	break;
		}
		graph_putsa_fx(
			table_name_left(0),
			top,
			fx_text,
			(i == entered_place) ? name.byte : names_z[i].byte
		);
		graph_putfwnum_fx(
			table_points_left(0),
			top,
			FX(place_col, 3, 0),
			POINT_DIGITS,
			(entered_place == i) ? entered_points : scoredat_points[i],
			0,
			false
		);
		if(stage_expr(i, entered_place, < SCOREDAT_CLEARED)) {
			graph_putfwnum_fx(
				table_stage_left(0),
				top,
				fx_text,
				2,
				(i == entered_place) ? entered_stage : scoredat_stages[i],
				0,
				false
			);
		} else if(stage_expr(i, entered_place, == SCOREDAT_CLEARED_MAKAI)) {
			graph_putsa_fx(
				table_stage_left(0), top, fx_text, REGIST_STAGE_MAKAI
			);
		} else if(stage_expr(i, entered_place, == SCOREDAT_CLEARED_JIGOKU)) {
			graph_putsa_fx(
				table_stage_left(0), top, fx_text, REGIST_STAGE_JIGOKU
			);
		}
		graph_putsa_fx(
			table_stage_left(2), top, fx_text, REGIST_STAGE_ROUTE_DASH
		);
		regist_route_put(
			table_stage_left(3),
			top,
			fx_text,
			(i == entered_place)
				? entered_route[0] : scoredat_routes[i * SCOREDAT_ROUTE_LEN],
			(i == entered_place)
				? entered_route[1] : scoredat_route_byte(i, 1)
		);
		if(entered_place == i) {
			entered_name_left = table_name_left(0);
			entered_name_top = table_row_top(i);
		}
		#undef top
		#undef place_col
		#undef fx_text
		#undef stage_expr
	}
}

#define alphabet_left_to_column(left) \
	((left - left_for(0)) / KANJI_PADDED_W)

#define alphabet_left_to_kanji(left, kanji_at_0) \
	(alphabet_left_to_column(left) + kanji_swap(kanji_at_0))

#define alphabet_if(kanji, left, top, on_space, on_left, on_right, on_enter) \
	if(top == LOWER_TOP) { \
		kanji = alphabet_left_to_kanji(left, '‚'); \
	} else if(top == LOWER2_TOP) { \
		kanji = alphabet_left_to_kanji(left, '‚') + KANJI_PER_ROW; \
	} else if(top == UPPER_TOP) { \
		kanji = alphabet_left_to_kanji(left, '‚`'); \
	} else if(top == UPPER2_TOP) { \
		kanji = alphabet_left_to_kanji(left, '‚`') + KANJI_PER_ROW; \
	} else if(top == SYM_TOP) { \
		kanji = ALPHABET_SYMS[alphabet_left_to_column(left)]; \
	} else if(top == NUM_TOP && left < SPACE_LEFT) { \
		kanji = alphabet_left_to_kanji(left, '‚O'); \
	} else if((top == NUM_TOP) && (left == SPACE_LEFT)) { \
		on_space \
	} else if((top == NUM_TOP) && (left == LEFT_LEFT)) { \
		on_left \
	} else if((top == NUM_TOP) && (left == RIGHT_LEFT)) { \
		on_right \
	} else if((top == NUM_TOP) && (left == ENTER_LEFT)) { \
		on_enter \
	}

void alphabet_put_at(int left, int top, bool16 is_selected)
{
	// Placement matters with -O-!
	extern const char ALPHABET_SPACE_0[];
	extern const char ALPHABET_LEFT_0[];
	extern const char ALPHABET_RIGHT_0[];
	extern const char ALPHABET_ENTER_0[];

	int16_t kanji = '\0';

	egc_copy_rect_1_to_0(left, top, KANJI_PADDED_W, GLYPH_H);

	int fx = FX(
		!is_selected ? (COL_REGULAR) : (FX_REVERSE | COL_SELECTED), 2, 0
	);

	alphabet_if(kanji, left, top,
		{ graph_printf_fx(left, top, fx, ALPHABET_SPACE_0); },
		{ graph_printf_fx(left, top, fx, ALPHABET_LEFT_0); },
		{ graph_printf_fx(left, top, fx, ALPHABET_RIGHT_0); },
		{ graph_printf_fx(left, top, fx, ALPHABET_ENTER_0); }
	);
	if(kanji != '\0') {
		#if (BINARY == 'M')
			char kanji_str[3];
		#endif
		graph_putkanji_fx(left, top, fx, 4, kanji);
	}
}

#if (BINARY == 'M')
	extern bool regist_jump_to_enter;
#endif

#define set_kanji_at(name, pos, kanji) \
	name.byte[(pos * 2) + 0] = kanji_hi(kanji); \
	name.byte[(pos * 2) + 1] = kanji_lo(kanji);

int regist_on_shot(
	int left, int top,
	scoredat_name_z_t& entered_name, int& entered_name_cursor
)
{
	int16_t kanji = '\0';
	struct hack {
		unsigned char byte[SCOREDAT_NAME_BYTES + 1];
	};
	extern const hack REGIST_NAME_SPACES;
	hack cursor_str = REGIST_NAME_SPACES;

	alphabet_if(kanji, left, top,
		{ kanji = kanji_swap('@'); },
		{ CLAMP_DEC(entered_name_cursor, 0); },
		{ CLAMP_INC(entered_name_cursor, (SCOREDAT_NAME_KANJI - 1)); },
		{ return 1; }
	);

	if(kanji != '\0') {
		set_kanji_at(entered_name, entered_name_cursor, kanji);
		#if (BINARY == 'M')
			if(entered_name_cursor == (SCOREDAT_NAME_KANJI - 1)) {
				regist_jump_to_enter = true;
			}
		#endif
		if(entered_name_cursor < (SCOREDAT_NAME_KANJI - 1)) {
			entered_name_cursor++;
		}
	}

	egc_copy_rect_1_to_0(
		entered_name_left,
		entered_name_top,
		(SCOREDAT_NAME_KANJI * GLYPH_FULL_W),
		GLYPH_H
	);
	graph_printf_s_fx(
		entered_name_left,
		entered_name_top,
		FX(COL_SELECTED, 2, 0),
		0,
		entered_name.byte
	);

	set_kanji_at(cursor_str, entered_name_cursor, kanji_swap('Q'));
	graph_printf_s_fx(
		entered_name_left,
		entered_name_top,
		FX(COL_SELECTED, 0, 0),
		1,
		cursor_str.byte
	);
	return 0;
}

#pragma option -b
enum regist_input_ret_t {
	RI_REGULAR = 0,
	RI_ENTER = 1,
	RI_NONE = 2
};
#pragma option -b.

regist_input_ret_t regist_on_input(
	int& left, int& top,
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
	inline void scoredat_free(void)
#else
	void scoredat_free(void)
#endif
{
	delete[] scoredat_names;
	delete[] scoredat_stages;
	delete[] scoredat_routes;
	delete[] scoredat_points;
}

void scoredat_save(void)
{
	extern const char SCOREDAT_FN_EASY_2[];
	extern const char SCOREDAT_FN_NORMAL_2[];
	extern const char SCOREDAT_FN_HARD_2[];
	extern const char SCOREDAT_FN_LUNATIC_2[];
	extern const char SCOREDAT_FOPEN_WB[];

	struct hack {
		char x[sizeof(SCOREDAT_MAGIC)];
	};
	#undef SCOREDAT_MAGIC
	extern const hack SCOREDAT_MAGIC;

	FILE* fp;
	const hack magic = SCOREDAT_MAGIC;
	char fn[16];
	scoredat_fn(fn, 2);

	if( (fp = fopen(fn, SCOREDAT_FOPEN_WB)) == NULL) {
		return;
	}
	write(fileno(fp), magic.x, sizeof(SCOREDAT_MAGIC) - 1);
	for(int i = 0; i < SCOREDAT_NAMES_SIZE; i++) {
		scoredat_names[i] = scoredat_name_byte_encode(scoredat_names[i]);
	}
	write(fileno(fp), scoredat_names, SCOREDAT_NAMES_SIZE);
	write(fileno(fp), scoredat_points, sizeof(uint32_t) * SCOREDAT_PLACES);
	write(fileno(fp), scoredat_stages, sizeof(int16_t) * SCOREDAT_PLACES);
	write(fileno(fp), scoredat_routes, sizeof(twobyte_t) * SCOREDAT_PLACES);
	fclose(fp);
}

void regist_name_enter(int entered_place)
{
	scoredat_name_z_t entered_name;
	regist_input_timeout_declare();
	int left;
	int top;
	int entered_name_cursor;
	int i;

	entered_name_cursor = 0;
	regist_input_timeout_reset();
	left = left_for(0);
	top = LOWER_TOP;

	for(i = 0; i < SCOREDAT_NAME_BYTES; i++) {
		entered_name.byte[i] = ' ';
	}
	entered_name.byte[SCOREDAT_NAME_BYTES] = '\0';

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
		] = entered_name.byte[i];
	}
	scoredat_save();
}

static const int PLACE_NONE = (SCOREDAT_PLACES + 20);
static const int SCOREDAT_NOT_CLEARED = (SCOREDAT_CLEARED - 10);

void regist(
	int32_t points, int16_t stage, const char route[SCOREDAT_ROUTE_LEN + 1]
)
{
	struct hack {
		const char *r[4];
	};
	extern const hack REGIST_TITLE_RANKS;

	scoredat_name_z_t names[SCOREDAT_PLACES];
	const hack RANKS = REGIST_TITLE_RANKS;
	long place;

	regist_bg_put(stage);

	graph_accesspage_func(1);

	regist_title_put(
		TITLE_BACK_LEFT, stage, RANKS.r, (FX_CLEAR_BG | FX(COL_REGULAR, 2, 0))
	);
	// On page 1, the title should now at (TITLE_BACK_LEFT, TITLE_BACK_TOP) if
	// not cleared, or at (TITLE_BACK_LEFT, TITLE_TOP) if cleared.

	graph_accesspage_func(0);
	if(stage < SCOREDAT_NOT_CLEARED) {
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
		scoredat_name_get(place, names[place].byte);
	}
	for(place = 0; place < SCOREDAT_PLACES; place++) {
		if(points >= scoredat_points[place]) {
			break;
		}
	}

	input_reset_sense();

	if(place < SCOREDAT_PLACES) {
		for(long shift = (SCOREDAT_PLACES - 1); shift > place; shift--) {
			strcpy(names[shift].byte, names[shift - 1].byte);
			scoredat_points[shift] = scoredat_points[shift - 1];
			scoredat_stages[shift] = scoredat_stages[shift - 1];
			scoredat_route_byte(shift, 0) = scoredat_route_byte(shift, -2);
			scoredat_route_byte(shift, 1) = scoredat_route_byte(shift, -1);
		}
		long p = (SCOREDAT_NAMES_SIZE - 1);
		while(((place * SCOREDAT_NAME_BYTES) + SCOREDAT_NAME_BYTES) <= p) {
			scoredat_names[p] = scoredat_names[p - SCOREDAT_NAME_BYTES];
			p--;
		}
		regist_put_initial(place, points, stage, route, names);
		alphabet_put_initial();

		scoredat_points[place] = points;
		scoredat_stages[place] = stage;
		scoredat_route_byte(place, 0) = route[0];
		scoredat_route_byte(place, 1) = route[1];

		// Writes the new name to scoredat_names[] and calls scoredat_save()
		regist_name_enter(place);

		_ES = FP_SEG(graph_accesspage_func); // Yes, no point to this at all.
		scoredat_free();
		return;
	}
	regist_put_initial(PLACE_NONE, points, stage, route, names);
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

#include "th01/hardware/egc.h"

#define COL_SELECTED 3
#define COL_REGULAR 7

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
#define SPACE_LEFT left_for(NUM_COUNT)
#define LEFT_COLUMN (KANJI_PER_ROW - 3)
#define LEFT_LEFT  left_for(LEFT_COLUMN + 0)
#define RIGHT_LEFT left_for(LEFT_COLUMN + 1)
#define ENTER_LEFT left_for(LEFT_COLUMN + 2)

inline uint16_t kanji_swap(uint16_t kanji)
{
	return (kanji << 8) | (kanji >> 8);
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
				? entered_route[0] : scoredat_routes[i].byte.lo,
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

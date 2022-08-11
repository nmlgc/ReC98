#include <stddef.h>
#include <dos.h>
#include "platform.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/common.h"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/clamp.hpp"
#include "th01/formats/ptn.hpp"
extern "C" {
#include "th01/hardware/egc.h"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/grppsafx.h"
#include "th01/hardware/input.hpp"
#include "th01/hardware/palette.h"
#include "th01/snd/mdrv2.h"
}
#include "th01/formats/grp.h"
#include "th01/shiftjis/bonus.hpp"
#include "th01/sprites/bonusbox.hpp"
#include "th01/main/extend.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/vars.hpp"
#include "th01/main/hud/hud.hpp"
#include "th01/main/bonus.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/stage/palette.hpp"
#include "th01/main/stage/stages.hpp"

/// Coordinates
/// -----------

// Stage bonus
// -----------

static const screen_x_t STAGEBONUS_PADDED_LEFT = 32;
static const screen_y_t STAGEBONUS_PADDED_TOP = 40;
static const int STAGEBONUS_ROWS = 14;
static const pixel_t STAGEBONUS_PADDING_TOP = 40;
static const pixel_t STAGEBONUS_PADDED_W = ((2 * GLYPH_FULL_W) + STAGEBONUS_W);
static const pixel_t STAGEBONUS_PADDED_H = (
	STAGEBONUS_PADDING_TOP + (STAGEBONUS_ROWS * GLYPH_H) + GLYPH_H
);
// -----------

// TOTLE
// -----

static const vram_word_amount_t TOTLE_METRIC_VRAM_WORD_LEFT = (224 / 16);
static const pixel_t TOTLE_METRIC_DIGIT_W = PTN_QUARTER_W;
// -----
/// -----------

// State
// -----

extern unsigned long score_bonus; // Should be local to the respective function.

#define clamp_and_add_x10_to_score_bonus(val, max, unnecessary_i) \
	/* Sneaky! That's how we can pretend this is an actual function that */ \
	/* returns a value. */ \
	val; \
	if(val > max) { \
		val = max; \
	} \
	for(unnecessary_i = 0; unnecessary_i < 10; unnecessary_i++) { \
		score_bonus += val; \
	}
// -----

// ZUN quirk: No ([digit] % 10) for the quarter calculation? As a result, we
// get scrambled numerals if [digit % 20] is between 10 and 19 inclusive:
//
// | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 |   18   |   19   |
// |  2 |  3 |  0 |  1 |  6 |  7 |  4 |  5 | (none) | (none) |
#define totle_metric_digit_scramble_if_ge_10_and_put_8(left, top, digit) { \
	ptn_put_quarter_8( \
		left, top, (PTN_TOTLE_NUMERAL_16 + ((digit % 10) / 4)), (digit % 4) \
	); \
} \

// [digit] must be a value from 0 to 9, but [place] can be negative.
void pascal near totle_metric_digit_animate(
	int digit, int place, screen_y_t top
)
{
	enum {
		DIGIT_LOOPS = 2, // Number of full loops from 0 to 9
	};

	int loops_done = 0;
	screen_x_t left = (
		(TOTLE_METRIC_VRAM_WORD_LEFT * 16) + (place * TOTLE_METRIC_DIGIT_W)
	);

	// The only place in the game where this hack is appropriate… but even
	// here, that's only because the left coordinate is always word-aligned.
	ptn_sloppy_unput_before_alpha_put = true;

	for(int i = 0; i < (DIGIT_LOOPS * 10); i++) {
		totle_metric_digit_scramble_if_ge_10_and_put_8(left, top, i);
		if((i % 10) == (digit % 10)) {
			loops_done++;
		}
		if(loops_done >= DIGIT_LOOPS) {
			break;
		}
		delay(4);
		mdrv2_se_play(2);
	}

	// Only necessary because the last numeral rendered in the loop is
	// guaranteed to be a scrambled one.
	totle_metric_digit_scramble_if_ge_10_and_put_8(left, top, digit);

	ptn_sloppy_unput_before_alpha_put = false;
}

static const int ROWSHIFT_CHUNK_DOTS = (EGC_REGISTER_DOTS * 2);
static const int ROWSHIFT_CHUNK_SIZE = (EGC_REGISTER_SIZE * 2);

// Shifts [ROWSHIFT_CHUNK_DOTS] pixels of the given row on VRAM page 0 from
// either the right edge of VRAM to the left or vice versa depending on whether
// [y] is even or odd, then fills the freed-up chunk with a chunk of pixels
// from VRAM page 1 that start [transferred_offset] bytes away from the shifted
// edge.
// Assumes that VRAM page 0 is accessed, and that the EGC is active and
// initialized for a copy.
void pascal near egc_pagetrans_rowshift_alternating(
	vram_y_t y, vram_byte_amount_t transferred_offset
)
{
	enum {
		CHUNK_OFFSET_LEFT  = (0 * EGC_REGISTER_SIZE),
		CHUNK_OFFSET_RIGHT = (1 * EGC_REGISTER_SIZE),
	};

	uvram_offset_t vo_p0;
	egc_temp_t dots;
	vram_byte_amount_t negative_chunk_delta; // negative for extra confusion?
	union {
		vram_dword_amount_t num;
		vram_offset_t vo_p1;
	} u1;

	// Shift
	if(y & 1) {
		vo_p0 = vram_offset_muldiv((RES_X - ROWSHIFT_CHUNK_DOTS), y);
		negative_chunk_delta = -ROWSHIFT_CHUNK_SIZE;
	} else {
		vo_p0 = vram_offset_muldiv(0, y);
		negative_chunk_delta = ROWSHIFT_CHUNK_SIZE;
	}
	for(u1.num = 0; u1.num < ((ROW_SIZE / ROWSHIFT_CHUNK_SIZE) - 1); u1.num++) {
		vo_p0 += negative_chunk_delta;

		// Inconsistent parentheses? Blame code generation.
		dots = egc_chunk(vo_p0 + CHUNK_OFFSET_LEFT);
		egc_chunk((vo_p0 - negative_chunk_delta + CHUNK_OFFSET_LEFT)) = dots;
		dots = egc_chunk(vo_p0 + CHUNK_OFFSET_RIGHT);
		egc_chunk((vo_p0 - negative_chunk_delta + CHUNK_OFFSET_RIGHT)) = dots;
	}

	// Transfer new pixels
	u1.vo_p1 = ((negative_chunk_delta > 0)
		? ((y * ROW_SIZE) + transferred_offset)
		: ((y * ROW_SIZE) + ROW_SIZE - ROWSHIFT_CHUNK_SIZE - transferred_offset)
	);
	graph_accesspage_func(1);	dots = egc_chunk(u1.vo_p1 + CHUNK_OFFSET_LEFT);
	graph_accesspage_func(0);	egc_chunk(vo_p0 + CHUNK_OFFSET_LEFT) = dots;
	graph_accesspage_func(1);	dots = egc_chunk(u1.vo_p1 + CHUNK_OFFSET_RIGHT);
	graph_accesspage_func(0);	egc_chunk(vo_p0 + CHUNK_OFFSET_RIGHT) = dots;
}

void pascal near totle_pagetrans_animate(int)
{
	upixel_t y;
	unsigned int rows_active = 0;
	uvram_byte_amount_t* row_transfer_offset;
	bool16* row_active;
	unsigned int rows_done = 0;
	unsigned int col;
	unsigned int comp;
	unsigned int rows_done_prev = 1;
	int unused_and_uninitialized_frame_count; // ZUN bloat

	row_transfer_offset = new uvram_byte_amount_t[RES_Y];
	row_active = new bool16[RES_Y];
	for(y = 0; y < RES_Y; y++) {
		row_transfer_offset[y] = 0;
		row_active[y] = false;
	}

	egc_on();
	egc_setup_copy();

	while(1) {
		for(y = 0; y < RES_Y; y++) {
			if(!row_active[y]) {
				continue;
			}
			egc_pagetrans_rowshift_alternating_32(y, row_transfer_offset[y]);
			row_transfer_offset[y] += ROWSHIFT_CHUNK_SIZE;
			if(row_transfer_offset[y] >= ROW_SIZE) {
				row_active[y] = false;
				rows_done++;
			}
		}
		unused_and_uninitialized_frame_count++;
		frame_delay(2);

		if(rows_done >= RES_Y) {
			break;
		}
		if(rows_active < RES_Y) {
			row_active[rows_active + 0] = true;
			row_active[rows_active + 1] = true;
			row_active[rows_active + 2] = true;
			row_active[rows_active + 3] = true;
			row_active[rows_active + 4] = true;
			row_active[rows_active + 5] = true;
			row_active[rows_active + 6] = true;
			row_active[rows_active + 7] = true;
		}
		rows_active += 8;

		if((rows_done != rows_done_prev) && ((rows_active & 0xF) == 0)) {
			z_palette_step_to(col, comp, grp_palette);
		}
		rows_done_prev = rows_done;
	}

	delete[] row_transfer_offset;
	delete[] row_active;
	egc_off();
}

void near totle_load_and_pagetrans_animate(void)
{
	extern const char CLEAR3_grp[];
	extern const char numb_ptn[];

	graph_accesspage_func(1);
	grp_put(CLEAR3_grp);
	ptn_load(PTN_SLOT_NUMB, numb_ptn);
	graph_accesspage_func(0);
	totle_pagetrans_animate(0);
}

void near stagebonus_box_open_animate(void)
{
	vram_offset_t vo_upper_row = vram_offset_shift(
		STAGEBONUS_PADDED_LEFT,
		(STAGEBONUS_PADDED_TOP + (STAGEBONUS_PADDED_H / 2))
	);
	pixel_t x;
	vram_offset_t vo_upper_column;
	vram_offset_t vo_lower_row;
	vram_offset_t vo_lower_column;
	const dot_rect_t(8, 4) BOX = sSTAGEBONUS_BOX;

	grcg_setcolor_rmw(V_BLACK);

	vo_lower_row = vo_upper_row;
	for(pixel_t row = 0; row < (STAGEBONUS_PADDED_H / 2); row++) {
		x = 0;
		vo_upper_column = vo_upper_row;
		vo_lower_column = vo_lower_row;
		while(x < (STAGEBONUS_PADDED_W / BYTE_DOTS)) {
			grcg_put(vo_upper_column, BOX[row % BOX.h()], 8);
			grcg_put(vo_lower_column, BOX[row % BOX.h()], 8);
			x++;
			vo_upper_column++;
			vo_lower_column++;
		}
		vo_upper_row -= ROW_SIZE;
		vo_lower_row += ROW_SIZE;
		if((row % 6) == 0) {
			frame_delay(1);
		}
	}
	grcg_off();
}

static const int8_t FULLWIDTH_NUMERAL_SPACE = 10;

void fullwidth_numeral(ShiftJISKanji& kanji, int8_t digit)
{
	struct hack { const ShiftJISKanji* x[11]; }; // XXX
	extern const struct hack FULLWIDTH_NUMERALS_WITH_SPACE;

	const struct hack NUMERALS = FULLWIDTH_NUMERALS_WITH_SPACE;

	kanji.byte[0] = NUMERALS.x[digit]->byte[0];
	kanji.byte[1] = NUMERALS.x[digit]->byte[1];
}

void pascal near fullwidth_str_from_4_digit_value(ShiftJISKanji str[4], int val)
{
	fullwidth_numeral(str[0], (val / 1000));	val %= 1000;
	fullwidth_numeral(str[1], (val / 100)); 	val %= 100;
	fullwidth_numeral(str[2], (val / 10));  	val %= 10;
	fullwidth_numeral(str[3], val);
}

#define stagebonus_str_put(relative_left, row, col, str) { \
	graph_putsa_fx( \
		(STAGEBONUS_PADDED_LEFT + GLYPH_FULL_W + relative_left), \
		(STAGEBONUS_PADDED_TOP + 40 + (row * GLYPH_H)), \
		(col | FX_WEIGHT_BOLD), \
		str \
	); \
}

void stagebonus_animate(int stage_num)
{
	enum {
		DIGITS = ((sizeof(stagebonus_digit_buf) - 1) / 2),
		METRIC_W = shiftjis_w(stagebonus_digit_buf),

		// Right-aligned?
		TITLE_LEFT = (STAGEBONUS_W - STAGEBONUS_TITLE_W),

		LABEL_LEFT = 0,

		// Technically reaching into the right padding.
		METRIC_LEFT = (STAGEBONUS_W + GLYPH_FULL_W - METRIC_W),

		TOTAL_LEFT = (STAGEBONUS_W - METRIC_W),
		HIT_KEY_LEFT = (
			STAGEBONUS_W - (2 * GLYPH_FULL_W) - shiftjis_w(STAGEBONUS_HIT_KEY)
		),
	};

	#undef stagebonus_title
	#undef stagebonus_digit_buf
	#undef STAGEBONUS_SUBTITLE
	#undef STAGEBONUS_TIME
	#undef STAGEBONUS_CARDCOMBO_MAX
	#undef STAGEBONUS_RESOURCES
	#undef STAGEBONUS_STAGE_NUMBER
	#undef STAGEBONUS_TOTAL
	#undef STAGEBONUS_HIT_KEY
	extern stagebonus_title_t stagebonus_title;
	extern ShiftJISKanji stagebonus_digit_buf[];
	extern const char STAGEBONUS_SUBTITLE[];
	extern const char STAGEBONUS_TIME[];
	extern const char STAGEBONUS_CARDCOMBO_MAX[];
	extern const char STAGEBONUS_RESOURCES[];
	extern const char STAGEBONUS_STAGE_NUMBER[];
	extern const char STAGEBONUS_TOTAL[];
	extern const char STAGEBONUS_HIT_KEY[];

	#define clamp_add_x10_to_score_bonus_and_put( \
		digit_buf, row, val, max, unnecessary_i \
	) { \
		val = clamp_and_add_x10_to_score_bonus(val, max, unnecessary_i); \
		fullwidth_str_from_4_digit_value(digit_buf, val); \
		stagebonus_str_put(METRIC_LEFT, row, V_WHITE, digit_buf->byte); \
	}

	stagebonus_title_t* title = reinterpret_cast<stagebonus_title_t *>(
		&stagebonus_title
	);
	ShiftJISKanji* digit_buf = reinterpret_cast<ShiftJISKanji *>(
		stagebonus_digit_buf
	);
	int val = 0;
	unsigned int i;

	fullwidth_numeral(title->stage[0], (stage_num / 10));
	fullwidth_numeral(title->stage[1], (stage_num % 10));

	z_palette_set_all_show(stage_palette);
	stagebonus_box_open_animate();

	stagebonus_str_put(TITLE_LEFT, 0, V_RED, title->prefix->byte);
	stagebonus_str_put(LABEL_LEFT, 2, V_WHITE, STAGEBONUS_SUBTITLE);
	stagebonus_str_put(LABEL_LEFT, 3, V_WHITE, STAGEBONUS_TIME);
	stagebonus_str_put(LABEL_LEFT, 5, V_WHITE, STAGEBONUS_CARDCOMBO_MAX);
	stagebonus_str_put(LABEL_LEFT, 7, V_WHITE, STAGEBONUS_RESOURCES);
	stagebonus_str_put(LABEL_LEFT, 9, V_WHITE, STAGEBONUS_STAGE_NUMBER);
	stagebonus_str_put(LABEL_LEFT, 11, V_WHITE, STAGEBONUS_TOTAL);
	stagebonus_str_put(HIT_KEY_LEFT, 13, V_RED, STAGEBONUS_HIT_KEY);

	// Time
	val = (stage_timer * 3);
	val = clamp_and_add_x10_to_score_bonus(val, 6553, i);
	fullwidth_numeral(digit_buf[4], 0);
	fullwidth_numeral(digit_buf[5], FULLWIDTH_NUMERAL_SPACE);
	fullwidth_str_from_4_digit_value(digit_buf, val);
	stagebonus_str_put(METRIC_LEFT, 3, V_WHITE, digit_buf->byte);

	// Card combo ("Continuous")
	val = (cardcombo_max * 100);
	clamp_add_x10_to_score_bonus_and_put(digit_buf, 5, val, 6553, i);

	// Bomb & Player
	val = (lives * 200);
	val += (bombs * 100);
	clamp_add_x10_to_score_bonus_and_put(digit_buf, 7, val, 6553, i);

	// Stage number
	val = ((stage_num - 1) * 200);
	clamp_add_x10_to_score_bonus_and_put(digit_buf, 9, val, 6553, i);

	// Commit
	score += score_bonus;

	// Sum
	int bonus_div_10000 = (score_bonus / 10000);
	int bonus_remainder = (score_bonus - (bonus_div_10000 * 10000));

	resident->bonus_per_stage[(stage_num - 1) % STAGES_PER_SCENE] = score_bonus;

	fullwidth_numeral(digit_buf[0], (bonus_div_10000 / 10));
	fullwidth_numeral(digit_buf[1], (bonus_div_10000 % 10));
	fullwidth_numeral(digit_buf[2], (bonus_remainder / 1000));
	bonus_remainder %= 1000;
	fullwidth_numeral(digit_buf[3], (bonus_remainder / 100));
	bonus_remainder %= 100;
	fullwidth_numeral(digit_buf[4], (bonus_remainder / 10));
	fullwidth_numeral(digit_buf[5], 0);
	stagebonus_str_put(TOTAL_LEFT, 11, V_WHITE, digit_buf->byte);

	// Remember when we added to the [score] above?
	hud_score_and_cardcombo_render();

	// Don't you love explicitly spelling out everything that can happen?
	score_extend_update_and_render();

	input_reset_sense();
	input_shot = true;
	input_ok = true;
	while((input_shot == true) && (input_ok == true)) {
		input_sense(false);
	}

	score_bonus = 0;

	#undef clamp_add_x10_to_score_bonus_and_put
}

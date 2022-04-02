#pragma option -zPgroup_01

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/rank.h"
extern "C" {
#include "th01/hardware/grppsafx.h"
#include "th02/hardware/frmdelay.h"
#include "th03/common.h"
#include "th03/score.h"
#include "th03/playchar.hpp"
#include "th03/resident.hpp"
#include "th03/sprites/regi.h"
#include "th03/formats/cdg.h"
#include "th03/formats/pi.hpp"
#include "th03/hardware/input.h"
}
#include "th03/shiftjis/regist.hpp"
#include "th03/formats/scoredat.hpp"

#include "th03/formats/score_ld.cpp"
#include "th03/formats/score_es.cpp"

static const int PLACE_NONE = -1;

/// Coordinates
/// -----------

// REGI_W and REGI_H are already used for, well, regi_patnum_t members...
#define REGI_GLYPH_W 32
#define REGI_GLYPH_H 32
static const int REGI_DOUBLEWIDE_X = REGI_SP;

static const screen_x_t TABLE_LEFT = 24;
static const screen_y_t TABLE_TOP = 104;
static const pixel_t TABLE_ROW_SPACING = 20;

static const pixel_t NAME_SPACING = 24;
static const pixel_t SCORE_SPACING = 16;
static const pixel_t CELL_PADDING_X = 16;
static const pixel_t PLACE_NUMBER_PADDED_W = (REGI_GLYPH_W + CELL_PADDING_X);

inline screen_x_t place_left(const unsigned char& name_cursor_backwards) {
	return (TABLE_LEFT + PLACE_NUMBER_PADDED_W +
		(((SCOREDAT_NAME_LEN - 1) - name_cursor_backwards) * NAME_SPACING)
	);
}

inline screen_y_t place_top(int place) {
	return (TABLE_TOP + (place * TABLE_ROW_SPACING));
}

static const int ALPHABET_ROWS = 3;
static const int ALPHABET_GLYPHS = REGI_ALL;
static const int ALPHABET_GLYPHS_PER_ROW = (ALPHABET_GLYPHS / ALPHABET_ROWS);
static const pixel_t ALPHABET_ROW_W = (ALPHABET_GLYPHS_PER_ROW * REGI_GLYPH_W);
static const pixel_t ALPHABET_ROW_SPACING = 24;

static const screen_x_t ALPHABET_LEFT = 64;
static const screen_y_t ALPHABET_TOP = 320;
static const screen_x_t ALPHABET_RIGHT = (ALPHABET_LEFT + ALPHABET_ROW_W);

inline screen_y_t alphabet_top_for_row(int row) {
	return (ALPHABET_TOP + (row * ALPHABET_ROW_SPACING));
}
/// -----------

/// Function ordering fails
/// -----------------------

// [regi] should, obviously, be a regi_patnum_t.
void pascal near regi_put(
	screen_x_t left, screen_y_t top, int regi, bool16 highlight
);
/// -----------------------

/// State
/// -----

extern int entered_place;
/// -----

void near regist_load_and_put_initial(void)
{
	enum {
		RANK_IMAGE_W = 320,
		RANK_IMAGE_H = 88,
	};

	extern unsigned char near *rank_image_fn;
	extern const char regib_pi[];
	extern const char regi2_bft[];
	extern const char regi1_bft[];

	palette_black();
	graph_accesspage(0);
	graph_showpage(0);

	pi_load_put_8_free(0, regib_pi);

	// Kind of assumes that we only show this screen once for the lifetime of
	// the process.
	rank_image_fn[3] += resident->rank;

	cdg_load_single(0, rank_image_fn, 0);
	cdg_put_8((RES_X - RANK_IMAGE_W), (RES_Y - RANK_IMAGE_H), 0);
	cdg_free(0);

	super_entry_bfnt(regi2_bft);
	super_entry_bfnt(regi1_bft);

	graph_copy_page(1);
	graph_accesspage(0);
}

inline int score_digit_as_regi(int digit) {
	return (REGI_0 + resident->score_last[0].digits[digit]);
}

int near regist_score_enter_from_resident(void)
{
	int place;
	int shift;
	int c;

	for(place = 0; place < SCOREDAT_PLACES; place++) {
		for(c = (SCORE_DIGITS - 1); c >= 0; c--) {
			if(score_digit_as_regi(c) > hi.score.score[place][c + 1]) {
				goto found;
			} else if(score_digit_as_regi(c) < hi.score.score[place][c + 1]) {
				break;
			}
		}
	}
	if(place == SCOREDAT_PLACES) {
		return PLACE_NONE;
	}

found:
	if(place < (SCOREDAT_PLACES - 1)) {
		for(shift = (SCOREDAT_PLACES - 2); shift >= place; shift--) {
			for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
				hi.score.name[shift + 1][c] = hi.score.name[shift][c];
			}
			for(c = 0; c < sizeof(hi.score.score[0]); c++) {
				hi.score.score[shift + 1][c] = hi.score.score[shift][c];
			}
			hi.score.stage[shift + 1] = hi.score.stage[shift];
			hi.score.playchar[shift + 1] = hi.score.playchar[shift];
		}
	}

	for(c = 0; c < SCOREDAT_NAME_LEN; c++) {
		hi.score.name[place][c] = REGI_ASCII(' ');
	}

	for(c = 1; c < (SCORE_DIGITS + 1); c++) {
		hi.score.score[place][c] = REGI_DIGIT(
			resident->score_last[0].digits[c - 1]
		);
	}
	hi.score.score[place][0] = static_cast<regi_patnum_t>(
		REGI_3 - resident->rem_credits
	);

	if(resident->story_stage == STAGE_ALL) {
		hi.score.stage[place] = REGI_ALL;
	} else {
		hi.score.stage[place] = REGI_DIGIT(resident->story_stage);
	}

	hi.score.playchar[place].v = (resident->playchar_paletted[0].char_id() + 1);
	return place;
}

void near alphabet_put_initial(void)
{
	screen_x_t left;
	screen_y_t top;
	int regi = REGI_A; // regi_patnum_t

	top = alphabet_top_for_row(0);
	while(top <= alphabet_top_for_row(ALPHABET_ROWS - 1)) {
		left = ALPHABET_LEFT;
		while(left < ALPHABET_RIGHT) {
			super_put(left, top, regi);
			left += REGI_GLYPH_W;
			regi++;
		}
		top += ALPHABET_ROW_SPACING;
	}
}

// [regi] should, obviously, be a regi_patnum_t.
void pascal near alphabet_putca(int regi, bool16 highlight)
{
	screen_x_t left = (
		((regi % ALPHABET_GLYPHS_PER_ROW) * REGI_GLYPH_W) + ALPHABET_LEFT
	);
	screen_y_t top = (
		((regi / ALPHABET_GLYPHS_PER_ROW) * ALPHABET_ROW_SPACING) + ALPHABET_TOP
	);
	regi_put(left, top, regi, highlight);
}

// What's a EGC?
void pascal near regi_unput(screen_x_t left, screen_y_t top)
{
	vram_offset_t vo = vram_offset_shift(left, top);
	for(unsigned long y = 0; y < REGI_GLYPH_H; y++) {
		Planar<dots_t(REGI_GLYPH_W)> row;
		graph_accesspage(1);	VRAM_SNAP_PLANAR(row, vo, REGI_GLYPH_W);
		graph_accesspage(0);	VRAM_PUT_PLANAR(vo, row, REGI_GLYPH_W);
		vo += ROW_SIZE;
	}
}

void pascal near regi_put(
	screen_x_t left, screen_y_t top, int regi, bool16 highlight
)
{
	// ZUN bug: A bounds check either here or in super_put() would be nice, to
	// prevent uninitialized data from being accessed once a score reaches
	// 8,000,000,000 points.
	int patnum = regi;
	if(highlight) {
		patnum += REGI_COUNT;
	}
	super_put(left, top, patnum);
	if((regi % ALPHABET_GLYPHS_PER_ROW) == REGI_DOUBLEWIDE_X) {
		super_put((left + REGI_GLYPH_W), top, (patnum + 1));
	}
}

void pascal near regist_row_put_at(screen_x_t left, screen_y_t top, int place)
{
	int c;
	int score_digit_first_nonzero; // regi_patnum_t
	bool16 highlight = (entered_place == place);
	unsigned char col = (entered_place == place) ? 0xF : 0x4;

	if(entered_place == PLACE_NONE) {
		highlight = true;
		col = 0xF;
	}

	// Place number
	if(place != 9) { // If the 10 is hardcoded in the branch below anyway...
		regi_put(left, top, (REGI_1 + place), highlight);
	} else {
		regi_put((left - (REGI_GLYPH_W / 4)), top, REGI_1, highlight);
		regi_put((left + (REGI_GLYPH_W / 4)), top, REGI_0, highlight);
	}
	left += PLACE_NUMBER_PADDED_W;

	// Name
	c = (SCOREDAT_NAME_LEN - 1);
	while(c >= 0) {
		if(hi.score.name[place][c] != REGI_ASCII(' ')) {
			regi_put(left, top, hi.score.name[place][c], highlight);
		}
		c--;
		left += NAME_SPACING;
	}
	left += CELL_PADDING_X;

	// Score
	score_digit_first_nonzero = REGI_0;
	c = (sizeof(hi.score.score[0]) - 1);
	while(c >= 0) {
		if(score_digit_first_nonzero == REGI_0) {
			score_digit_first_nonzero = hi.score.score[place][c];
		}
		if(score_digit_first_nonzero != REGI_0) {
			regi_put(left, top, hi.score.score[place][c], highlight);
		}
		c--;
		left += SCORE_SPACING;
	}
	left += CELL_PADDING_X;

	// Player character
	graph_putsa_fx(
		left,
		(top + ((REGI_GLYPH_H - GLYPH_H) / 2)),
		(col | FX_WEIGHT_BOLD),
		REGIST_PLAYCHARS[hi.score.playchar[place].v]
	);
	left += (REGIST_PLAYCHAR_W + CELL_PADDING_X);

	// Stage
	regi_put(left, top, hi.score.stage[place], highlight);
}

void near regist_rows_put(void)
{
	graph_copy_page(0);

	int place = 0;
	screen_y_t top = TABLE_TOP;
	while(place < SCOREDAT_PLACES) {
		regist_row_put_at(TABLE_LEFT, top, place);
		place++;
		top += TABLE_ROW_SPACING;
	}
}

void pascal near regist_row_put(int place)
{
	regist_row_put_at(TABLE_LEFT, place_top(place), place);
}

void near regist_name_enter(void)
{
	#define cursor_blank(cursor_backwards, top) { \
		regi_unput(place_left(cursor_backwards), top); \
		hi.score.name[entered_place][cursor_backwards] = REGI_ASCII(' '); \
	}

	#define cursor_backspace(cursor_backwards, top) { \
		cursor_blank(cursor_backwards, top); \
		if(cursor_backwards < (SCOREDAT_NAME_LEN - 1)) { \
			cursor_backwards++; \
		} \
	}

	#define on_direction(condition, hold_frames, func) { \
		if(condition) { \
			if( \
				(hold_frames == 0) || \
				((hold_frames >= 30) && ((hold_frames % 4) == 0)) \
			) { \
				func \
			} \
			hold_frames++; \
		} else { \
			hold_frames = 0; \
		} \
	}

	#define on_action(condition, lock, func) { \
		if(condition) { \
			if(lock == false) { \
				func \
			} \
			lock = true; \
		} else { \
			lock = false; \
		} \
	}

	struct input_hold_frames_t {
		int up;
		int down;
		int left;
		int right;
	};
	extern const input_hold_frames_t REGIST_INPUT_HOLD_INIT;

	screen_y_t top;
	int regi = REGI_A; // regi_patnum_t
	input_hold_frames_t hold_frames = REGIST_INPUT_HOLD_INIT;
	bool done = false;
	bool rerender = true;
	bool enter_locked = false;
	unsigned char cursor_backwards = (SCOREDAT_NAME_LEN - 1);
	bool back_locked = false;
	top = place_top(entered_place);

	while(!done) {
		input_mode_interface();

		on_direction((input_sp & INPUT_UP), hold_frames.up, {
			if(regi != REGI_QUESTION) {
				alphabet_putca(regi, false);
				regi -= ALPHABET_GLYPHS_PER_ROW;
				if(regi < 0) {
					regi += ALPHABET_GLYPHS;
				}
				rerender = true;
			}
		});
		on_direction((input_sp & INPUT_DOWN), hold_frames.down, {
			if(regi != REGI_QUESTION) {
				alphabet_putca(regi, false);
				regi += ALPHABET_GLYPHS_PER_ROW;
				if(regi >= ALPHABET_GLYPHS) {
					regi -= ALPHABET_GLYPHS;
				}
				rerender = true;
			}
		});
		on_direction((input_sp & INPUT_LEFT), hold_frames.left, {
			alphabet_putca(regi, false);
			if((regi % ALPHABET_GLYPHS_PER_ROW) == 0) {
				regi += REGI_DOUBLEWIDE_X;
			} else if((regi == REGI_BS) || (regi == REGI_SP)) {
				regi -= 2;
			} else {
				regi--;
			}
			rerender = true;
		});
		on_direction((input_sp & INPUT_RIGHT), hold_frames.right, {
			alphabet_putca(regi, false);
			if((regi % ALPHABET_GLYPHS_PER_ROW) == REGI_DOUBLEWIDE_X) {
				regi -= REGI_DOUBLEWIDE_X;
			} else if((regi == REGI_M) || (regi == REGI_Z)) {
				regi += 2;
			} else {
				regi++;
			}
			rerender = true;
		});

		on_action(
			((input_sp & INPUT_OK) || (input_sp & INPUT_SHOT)), enter_locked, {
				if(regi == REGI_BS) {
					cursor_backspace(cursor_backwards, top);
				} else if(regi == REGI_END) {
					done = true;
				} else {
					hi.score.name[entered_place][cursor_backwards] =
						static_cast<regi_patnum_t>(regi);
					if(cursor_backwards == 0) {
						done = true;
					}
					cursor_backwards--;
				}
				rerender = true;
			}
		);

		on_action((input_sp & INPUT_BOMB), back_locked, { \
			cursor_backspace(cursor_backwards, top);
			rerender = true;
		});

		if(rerender == true) {
			alphabet_putca(regi, true);

			// Any potential glyph at this cursor position will be overwritten
			// anyway, both on screen (by the preview) and in the name buffer
			// (by actually selecting a character). The backspace feature also
			// requires any previously set glyph to be erased here, due to...
			cursor_blank(cursor_backwards, top);

			// ... this full row rendering call. ZUN apparently considered it
			// necessary because the name glyphs overlap each other due to
			// NAME_SPACING < REGI_GLYPH_W. But even then, rendering only the
			// previous glyph would have been enough.
			regist_row_put(entered_place);

			// Preview the selected glyph in the place row
			if((regi % ALPHABET_GLYPHS_PER_ROW) != REGI_DOUBLEWIDE_X) {
				regi_put(place_left(cursor_backwards), top, regi, false);
			}
			rerender = false;
		}

		frame_delay(1);
	}

	#undef on_action
	#undef on_direction
}

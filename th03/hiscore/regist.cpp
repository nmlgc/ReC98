#pragma option -zPgroup_01

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/rank.h"
#include "th03/common.h"
#include "th03/score.h"
#include "th03/playchar.hpp"
#include "th03/resident.hpp"
#include "th03/sprites/regi.h"
#include "th03/formats/cdg.h"
#include "th03/formats/pi.hpp"
}
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

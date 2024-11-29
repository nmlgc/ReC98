/// View-only High Score menu
/// -------------------------

#include "th04/formats/scoredat/recreate.cpp"
#include "th04/hiscore/scoredat.cpp"
#include "libs/master.lib/pc98_gfx.hpp"

enum hiscore_patnum_t {
	// scnum.bft
	// ---------
	PAT_SCNUM = 0,
	PAT_SCNUM_last = (PAT_SCNUM + 9),
	#if (GAME == 5)
		PAT_SCNUM_UNUSED,
		PAT_SCNUM_UNUSED_last = (PAT_SCNUM_UNUSED + 9),
	#endif
	// ---------
	// hi_m.bft
	// --------
	PAT_RANK_1,
	PAT_RANK_2,
	PAT_RANK_last = (PAT_RANK_1 + (RANK_COUNT * 2) - 1),
	// --------
};

/// Coordinates
/// -----------

static const pixel_t NAME_W = (SCOREDAT_NAME_LEN * GAIJI_W);
static const pixel_t DIGIT_W = 16;

// The optional 9th score digit is written into the name padding.
static const pixel_t NAME_PADDED_W = (NAME_W + ((GAME == 5) ? 6 : 4) + DIGIT_W);

static const pixel_t SCORE_PADDED_W = ((DIGIT_W * SCORE_DIGITS) + 8);
static const pixel_t STAGE_PADDED_W = (GAIJI_W + 8);
static const pixel_t COLUMN_W = (
	NAME_PADDED_W + SCORE_PADDED_W + STAGE_PADDED_W + ((GAME == 5) ? 10 : 0)
);

static const pixel_t RANK_W = 128;

// These obviously only apply to the leftmost column.
static const screen_x_t NAME_LEFT = 8;
static const screen_x_t SCORE_LEFT = (NAME_LEFT + NAME_PADDED_W);
static const screen_x_t STAGE_LEFT = (SCORE_LEFT + SCORE_PADDED_W);

#if (GAME == 5)
	static const screen_y_t TABLE_1_TOP = 88;
	static const screen_y_t TABLE_2_TOP = 224;
	static const pixel_t PLACE_1_PADDING_BOTTOM = 8;
#else
	static const screen_y_t TABLE_TOP = 96;
	static const pixel_t PLACE_1_PADDING_BOTTOM = GLYPH_H;
#endif

static const screen_x_t RANK_LEFT = (RES_X - GLYPH_FULL_W - RANK_W);
static const screen_y_t RANK_TOP = (RES_Y - (GLYPH_H / 2) - GLYPH_H);
/// -----------

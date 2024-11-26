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

// ZUN bloat: The main difference between the TH04 and TH05 implementations is
// that TH04 explicitly spells out its two characters while TH05 sanely loops
// over its four. The `debloated` branch would also migrate TH04 to loops.

#define digit_at(section, place, digit) ( \
	((section.score.g_score[place].digits[digit]) - gb_0_) \
)

#define digit_put(left, top, digit) { \
	super_put(left, top, (PAT_SCNUM + digit)); \
}

// ZUN bug: Since score addition in MAIN.EXE effectively turns the most
// significant digit of a `score_lebcd_t` value from BCD to binary for scores
// past 99,999,999, the type would support a maximum score of 2,559,999,999
// points, or `09 09 09 09 09 09 09 FF` in memory. TH04's OMAKE.TXT confirms
// that ZUN knew it was possible to reach more than 100 million points in that
// game, and so he equipped this menu with the ability to interpret the last
// byte as binary and display a 9th digit in what would normally be the padding
// between name and score.
// However, `scoredat_section_t` stores its digits as gaiji, with an offset of
// [gb_0_]. This makes no sense no matter *how* you look at it, since both the
// in-game HUD and this High Score screen would prefer raw digits from 0 to 9.
// At first, this *seems* like no big deal because subtracting [gb_0_] would
// always correctly remove that offset, even if a digit's value wrapped around
// 0. But the problems then arise when such a subtraction is done as an
// expression that gets promoted to `int` as per C's integer promotion rules…
// such as when dividing by an untyped 10 in both functions below. As a result,
// the subtraction actually yields a negative integer, the result of the
// division remains negative as well, and the subsequent super_put() call ends
// up corrupting VRAM as master.lib does not bounds-check the patnum parameter.
// Therefore, this screen only supports a maximum 8th and 9th digit value of
// (0xFF - 0xA0) = 95, or a total score of 959,999,999 – not the 999 million
// you would expect.
//
// (At least scores above 1 billion on both unmodified games seem to be way out
// of reach as of December 2024, so you can't really complain about the lack of
// support for a 10th digit.)

#if (GAME == 5)
void pascal near score_put(screen_x_t left, screen_y_t top, int place)
{
	static_assert(SCORE_DIGITS == 8);
	if(digit_at(hi, place, 7) >= 10) {
		digit_put((left + (-1 * DIGIT_W)), top, (digit_at(hi, place, 7) / 10));
	}
	digit_put(left, top, (digit_at(hi, place, 7) % 10));
	left += DIGIT_W;

	int digit = (SCORE_DIGITS - 2);
	while(digit >= 0) {
		digit_put(left, top, digit_at(hi, place, digit));
		digit--;
		left += DIGIT_W;
	}
}
#else
#define digit_put_for(playchar, rel_left, top, digit) { \
	digit_put((SCORE_LEFT + rel_left + (playchar * COLUMN_W)), top, digit); \
}

#define digit8_put(playchar, top, section, place) { \
	static_assert(SCORE_DIGITS == 8); \
	if(digit_at(section, place, 7) >= 10) { \
		digit_put_for( \
			playchar, (-1 * DIGIT_W), top, (digit_at(section, place, 7) / 10) \
		); \
	} \
}

void pascal near scores_put(screen_y_t top, int place)
{
	int digit;
	pixel_t rel_left = DIGIT_W;

	digit8_put(PLAYCHAR_REIMU,  top, hi,  place);
	digit8_put(PLAYCHAR_MARISA, top, hi2, place);

	// ZUN bloat: Could have been part of the lower loop.
	digit_put_for(PLAYCHAR_REIMU,  0, top, (digit_at(hi,  place, 7) % 10));
	digit_put_for(PLAYCHAR_MARISA, 0, top, (digit_at(hi2, place, 7) % 10));

	digit = (SCORE_DIGITS - 2);
	while(digit >= 0) {
		digit_put_for(
			PLAYCHAR_REIMU,  rel_left, top, digit_at(hi,  place, digit)
		);
		digit_put_for(
			PLAYCHAR_MARISA, rel_left, top, digit_at(hi2, place, digit)
		);
		digit--;
		rel_left += DIGIT_W;
	}
}
#endif

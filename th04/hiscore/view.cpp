/// View-only High Score menu
/// -------------------------

#pragma option -zPop_01
#include "th04/formats/scoredat/recreate.cpp"
#include "th04/hiscore/score_ld.cpp"
#include "game/bgimage.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/formats/bfnt.h"
#include "th04/snd/snd.h"
#include "th04/shiftjis/fnshared.hpp"
#if (GAME == 5)
#include "th05/resident.hpp"
#include "th05/hardware/input.h"
#include "th05/formats/pi.hpp"
#include "th05/op/op.hpp"
#else
#include "th04/resident.hpp"
#include "th04/hardware/input.h"
#include "th03/formats/pi.hpp"
#include "th04/op/op.hpp"
#endif

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

enum hiscore_colors_t {
	COL_NAME = 2,
	COL_NAME_FIRST = 7,
	COL_STAGE = 7,
	COL_SHADOW = 14,
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

/// State
/// -----

scoredat_section_t hi;
scoredat_section_t hi2;

unsigned char rank;
unsigned char cleared_with[PLAYCHAR_COUNT][RANK_COUNT];
bool extra_unlocked;
/// -----

#define digit_at(section, place, digit) ( \
	((section.score.g_score[place].digits[digit]) - gb_0) \
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

void pascal near score_put(
	int playchar, const scoredat_section_t& section, screen_y_t top, int place
)
{
	int digit;
	pixel_t rel_left = DIGIT_W;

	static_assert(SCORE_DIGITS == 8);
	if(digit_at(section, place, 7) >= 10) {
		digit_put_for(
			playchar, (-1 * DIGIT_W), top, (digit_at(section, place, 7) / 10)
		);
	}
	digit_put_for(playchar, 0, top, (digit_at(section, place, 7) % 10));

	digit = (SCORE_DIGITS - 2);
	while(digit >= 0) {
		digit_put_for(
			playchar, rel_left, top, digit_at(section, place, digit)
		);
		digit--;
		rel_left += DIGIT_W;
	}
}
#endif

void pascal near stage_put(
	screen_x_t left, screen_y_t top, int gaiji // ACTUAL TYPE: gaiji_th04_t
)
{
	if(gaiji == g_NONE) {
		gaiji = g_HISCORE_STAGE_EMPTY;
	}
	graph_gaiji_putc((left + 2), (top + 2), gaiji, COL_SHADOW);
	graph_gaiji_putc((left + 0), (top + 0), gaiji, COL_STAGE);
}

#define name_put_shadowed(left, top, str, col_fg) { \
	graph_gaiji_puts((left + 2), (top + 2), GAIJI_W, str, COL_SHADOW); \
	graph_gaiji_puts((left + 0), (top + 0), GAIJI_W, str, col_fg); \
}

#if (GAME == 5)
void pascal near place_put(playchar2 playchar, int place)
{
	screen_x_t left;
	screen_y_t top;
	vc2 name_col;

	// ZUN bloat: Could have been calculated arithmetically...
	if(place == 0) {
		switch(playchar) {
		case PLAYCHAR_REIMU:
			left = (NAME_LEFT + (0 * COLUMN_W));
			top = TABLE_1_TOP;
			break;
		case PLAYCHAR_MARISA:
			left = (NAME_LEFT + (1 * COLUMN_W));
			top = TABLE_1_TOP;
			break;
		case PLAYCHAR_MIMA:
			left = (NAME_LEFT + (0 * COLUMN_W));
			top = TABLE_2_TOP;
			break;
		case PLAYCHAR_YUUKA:
			left = (NAME_LEFT + (1 * COLUMN_W));
			top = TABLE_2_TOP;
			break;
		}
		name_col = COL_NAME_FIRST;
	} else {
		// ZUN bloat: …and without branching by place.
		switch(playchar) {
		case PLAYCHAR_REIMU:
			left = (NAME_LEFT + (0 * COLUMN_W));
			top = (TABLE_1_TOP + PLACE_1_PADDING_BOTTOM + (place * GLYPH_H));
			break;
		case PLAYCHAR_MARISA:
			left = (NAME_LEFT + (1 * COLUMN_W));
			top = (TABLE_1_TOP + PLACE_1_PADDING_BOTTOM + (place * GLYPH_H));
			break;
		case PLAYCHAR_MIMA:
			left = (NAME_LEFT + (0 * COLUMN_W));
			top = (TABLE_2_TOP + PLACE_1_PADDING_BOTTOM + (place * GLYPH_H));
			break;
		case PLAYCHAR_YUUKA:
			left = (NAME_LEFT + (1 * COLUMN_W));
			top = (TABLE_2_TOP + PLACE_1_PADDING_BOTTOM + (place * GLYPH_H));
			break;
		}
		name_col = COL_NAME;
	}
	name_put_shadowed(
		left,
		top,
		reinterpret_cast<const char far *>(hi.score.g_name[place]),
		name_col
	);
	score_put((left + (SCORE_LEFT - NAME_LEFT)), top, place);
	stage_put((left + (STAGE_LEFT - NAME_LEFT)), top, hi.score.g_stage[place]);
}
#else
void pascal near place_put(
	int playchar, int place, const scoredat_section_t& section
)
{
	vc_t col;
	screen_y_t top;
	if(place == 0) {
		col = COL_NAME_FIRST;
		top = TABLE_TOP;
	} else {
		col = COL_NAME;
		top = (TABLE_TOP + PLACE_1_PADDING_BOTTOM + (place * GLYPH_H));
	}

	// ZUN bug: Leaves the second column with 4 fewer pixels of padding between
	// name and score. (Which translates to 0 pixels in case of a 9th score
	// digit.)
	name_put_shadowed(
		(NAME_LEFT + (playchar * (COLUMN_W + 4))),
		top,
		reinterpret_cast<const char far *>(section.score.g_name[place]),
		col
	);
	score_put(playchar, section, top, place);
	stage_put(
		(STAGE_LEFT + (playchar * COLUMN_W)), top, section.score.g_stage[place]
	);
}
#endif

void near rank_render(void)
{
	bgimage.write(0, 0);

	for(int pc = 0; pc < PLAYCHAR_COUNT; pc++) {
#if (GAME == 5)
		hiscore_scoredat_load_for(pc);
		for(int place = 0; place < SCOREDAT_PLACES; place++) {
			place_put(pc, place);
		}
#else
		for(int place = 0; place < SCOREDAT_PLACES; place++) {
			place_put(pc, place, ((pc == PLAYCHAR_REIMU) ? hi : hi2));
		}
#endif
	}

	static_assert(RANK_W == (2 * BFNT_ASSUMED_MAX_W));
	#define RANK_HALF_W (RANK_W / 2)
	super_put(
		(RANK_LEFT + (0 * RANK_HALF_W)), RANK_TOP, (PAT_RANK_1 + (rank * 2))
	);
	super_put(
		(RANK_LEFT + (1 * RANK_HALF_W)), RANK_TOP, (PAT_RANK_2 + (rank * 2))
	);
	#undef RANK_HALF_W
}

void near regist_view_menu(void)
{
	snd_kaja_func(KAJA_SONG_STOP, 0);
	snd_load(BGM_HISCORE_FN, SND_LOAD_SONG);
	snd_kaja_func(KAJA_SONG_PLAY, 0);

	// ZUN bloat: This both
	// • doesn't work, because fade-ins require the volume to be set to a lower
	//   value than what [KAJA_SONG_PLAY] resets it to, and
	// • sounds terrible, because -128 is the fastest but still not quite
	//   instant fade speed. This leaves the initial note on each channel muted
	//   while the rest of the track fades in very abruptly, clashing with the
	//   bass and chord notes of the name registration themes in both games.
	snd_kaja_func(KAJA_SONG_FADE, -128);

	palette_black_out(1);
	rank = resident->rank;

#if (GAME == 4)
	hiscore_scoredat_load_both();
#endif
	GrpSurface_LoadPI(bgimage, &Palettes, HISCORE_BG_FN);
	rank_render();
	palette_black_in(1);

	while(1) {
		// ZUN bug: The TH04 version of this function doesn't address the PC-98
		// keyboard quirk documented in the `Research/HOLDKEY` example, which
		// causes input to occasionally be processed a frame or two later than
		// expected. Not that big of a deal given that every key press launches
		// a 16-frame palette fade animation, but a bug nonetheless.
		input_reset_sense_interface();
		frame_delay(1);

		if(key_det & (INPUT_OK | INPUT_SHOT | INPUT_CANCEL)) {
			break;
		}
		if((key_det & INPUT_LEFT) && (rank != RANK_EASY)) {
			rank--;
			palette_settone(0);
#if (GAME == 4)
			hiscore_scoredat_load_both();
#endif
			rank_render();
			palette_black_in(1);
		}
		if((key_det & INPUT_RIGHT) && (rank < RANK_EXTRA)) {
			rank++;
			palette_settone(0);
#if (GAME == 4)
			hiscore_scoredat_load_both();
#endif
			rank_render();
			palette_black_in(1);
		}
	}

	snd_kaja_func(KAJA_SONG_FADE, 1);
	palette_black_out(1);
	graph_accesspage(0);
	GrpSurface_LoadPI(bgimage, &Palettes, MENU_MAIN_BG_FN);
	bgimage.write(0, 0);
	palette_black_in(1);

	do {
		// ZUN bug: With that one PC-98 keyboard quirk still not addressed in
		// TH04, the loop will break relatively quickly even while the player
		// is still holding a key. This cuts short any attempt to listen to the
		// fade-out by holding a key. In TH05, this works as intended.
		// (At least it proves that this loop wasn't actually necessary to
		// ensure that this menu isn't re-entered, confirming this entire loop
		// to be an easter egg that allows the player to actually listen to the
		// BGM fade-out.)
		input_reset_sense_interface();
		frame_delay(1);
	} while(key_det != INPUT_NONE);

	snd_kaja_func(KAJA_SONG_STOP, 0);
	snd_load(BGM_MENU_MAIN_FN, SND_LOAD_SONG);
	snd_kaja_func(KAJA_SONG_PLAY, 0);
}

#if (GAME == 5)
void near cleardata_load(void)
{
	extra_unlocked = false;
	for(int playchar = PLAYCHAR_REIMU; playchar < PLAYCHAR_COUNT; playchar++) {
		extra_playable_with[playchar] = false;
		rank = RANK_EASY;
		while(rank < RANK_COUNT) {
			if(hiscore_scoredat_load_for(playchar)) {
				break;
			}
			cleared_with[playchar][rank] = hi.score.cleared;
			if(cleared_with[playchar][rank] != SCOREDAT_CLEARED) {
				cleared_with[playchar][rank] = false;
			}
			if(rank < RANK_EXTRA) {
				extra_unlocked |= cleared_with[playchar][rank];
				extra_playable_with[playchar] |= cleared_with[playchar][rank];
			}
			rank++;
		}
	}
	rank = resident->rank;
}
#else
void near cleardata_load(void)
{
	rank = RANK_EASY;
	while(rank < RANK_COUNT) {
		if(hiscore_scoredat_load_both()) {
			break;
		}

		scoredat_t near *sd = &hi.score;
		for(int playchar = 0; playchar < PLAYCHAR_COUNT; playchar++) {
			unsigned char near* cleared = &cleared_with[playchar][rank];
			*cleared = sd->cleared;
			if(*cleared > SCOREDAT_CLEARED_BOTH) {
				*cleared = false;
			}
			if(rank != RANK_EASY) {
				extra_unlocked |= *cleared;
			}

			static_assert(PLAYCHAR_COUNT == 2);
			sd = &hi2.score;
		}
		rank++;
	}
	rank = resident->rank;
}
#endif

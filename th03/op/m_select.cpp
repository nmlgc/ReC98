/// Character selection menu
/// ------------------------

#pragma option -zPgroup_01

#include "th03/op/m_select.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th02/formats/bfnt.h"
#include "th03/common.h"
#include "th03/resident.hpp"
#include "th03/formats/cdg.h"
extern "C" {
#include "th03/formats/hfliplut.h"
}
#include "th03/formats/scoredat.hpp"
#include "th03/shiftjis/fns.hpp"
#include "th03/snd/snd.h"
#include "th03/sprites/op_cdg.hpp"

/// Constants
/// ---------

static const int STAT_COUNT = 3;
extern const uint8_t PLAYCHAR_STATS[PLAYCHAR_COUNT][STAT_COUNT];
/// ---------

/// Coordinates
/// -----------

static const pixel_t PIC_W = 192;
static const pixel_t PIC_H = 192;
static const pixel_t PIC_MARGIN_X = 32;

static const pixel_t NAME_W = 128;
static const pixel_t NAME_H = 16;
static const pixel_t NAME_PADDING_Y = 4;
static const pixel_t NAME_PADDED_H = (NAME_H + NAME_PADDING_Y);

static const pixel_t STATS_W = 128;

static const pixel_t STAT_STAR_W = 9;
static const pixel_t STAT_STAR_PADDED_W = (STAT_STAR_W + 2);
static const pixel_t STAT_STAR_H = 16;

static const screen_x_t P1_LEFT = PIC_MARGIN_X;
static const screen_x_t P2_LEFT = (RES_X - PIC_MARGIN_X - PIC_W);
static const screen_y_t PIC_TOP = 96;

static const screen_x_t NAMES_LEFT = ((RES_X / 2) - (NAME_W / 2));
static const screen_y_t NAMES_TOP = 136;

static const screen_y_t STATS_TOP = (PIC_TOP + PIC_H + 16);
/// -----------

/// State
/// -----

extern bool input_locked[PLAYER_COUNT];
extern playchar_t sel[PLAYER_COUNT];
extern bool sel_confirmed[PLAYER_COUNT];
extern page_t page_shown;
extern unsigned int fadeout_frames;
extern int16_t curve_unused; // ZUN bloat
extern int curve_trail_count;
extern unsigned char playchars_available;
/// -----

#include "th03/formats/score_ld.cpp"

unsigned char near playchars_available_load(void)
{
	unsigned char ret = PLAYCHAR_COUNT_LOCKED;
	for(int i = RANK_EASY; i < (RANK_LUNATIC + 1); i++) {
		if(scoredat_load_and_decode(static_cast<rank_t>(i))) {
			return PLAYCHAR_COUNT_LOCKED;
		}
		if(hi.score.cleared == SCOREDAT_CLEARED) {
			ret = PLAYCHAR_COUNT;
		}
	}
	return ret;
}

// Coincidentally, these were the only characters available in the trial
// version.
void near select_cdg_load_part1_of_4(void)
{
	extern const char SELECT_EXTRA_FOR_PLAYCHAR_FN[];

	hflip_lut_generate();

	static_assert(PLAYCHAR_COUNT >= 3);
	for(int i = 0; i < 3; i++) {
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0);
	}
	cdg_load_all_noalpha(CDG_EXTRA_FOR_PLAYCHAR, SELECT_EXTRA_FOR_PLAYCHAR_FN);
}

void near select_cdg_load_part2_of_4(void)
{
	extern const char PLAYCHAR_PIC_UNKNOWN_FN[];
	extern const char SELECT_STATS_FN[];
	extern const char SELECT_EXTRA_BG_FN[];

	// ZUN bloat: Shouldn't this be exclusively loaded for Story Mode?
	cdg_load_single((CDG_PIC_SELECTED + 1), PLAYCHAR_PIC_UNKNOWN_FN, 0);

	cdg_load_single_noalpha(CDG_STATS, SELECT_STATS_FN, 0);
	cdg_load_single_noalpha(CDG_EXTRA_BG, SELECT_EXTRA_BG_FN, 0);
}

void near select_cdg_load_part3_of_4(void)
{
	extern const char SELECT_EXTRA_FOR_PLAYCHAR_FN[];

	// ZUN bloat: Redundant, PID 0 always has to select a character before the
	// game shows the image in this slot.
	cdg_load_single((CDG_PIC_SELECTED + 0), PLAYCHAR_PIC_FN[PLAYCHAR_REIMU], 0);

	static_assert(PLAYCHAR_COUNT >= 6);
	for(int i = 3; i < 6; i++) {
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0);
	}
}

#define select_cdg_load_part4_of_4() { \
	static_assert(PLAYCHAR_COUNT <= 9); \
	for(int i = 6; i < 9; i++) { \
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0); \
	} \
} \

void near select_init_and_load(void)
{
	extern const char BGM_SELECT_FN[];
	extern const char PLAYCHAR_NAME_FN[];
	extern const char SELECT_PALETTE_FN[];

	vsync_Count1 = 0;

	snd_kaja_func(KAJA_SONG_STOP, 0);
	snd_load(BGM_SELECT_FN, SND_LOAD_SONG);
	snd_kaja_func(KAJA_SONG_PLAY, 0);

	curve_unused = 200;
	random_seed = resident->rand;

	text_clear();
	super_free();
	super_entry_bfnt(PLAYCHAR_NAME_FN);

	// ZUN landmine: Does nothing to avoid this happening mid-frame and causing
	// tearing.
	graph_accesspage(0);	graph_clear();
	graph_accesspage(1);	graph_clear();
	graph_showpage(0);
	page_shown = 0;

	palette_entry_rgb_show(SELECT_PALETTE_FN);
	select_cdg_load_part4_of_4();

	// ZUN bug: Is this supposed to be long enough for the player to release
	// the Shot key that might have entered this menu? If that was the intent,
	// the menu functions should properly lock input until the player released
	// that key. Keep holding the Shot key for more than 30 frames and the
	// menus will still confirm the initial selection on their first frame.
	// The menu needs [input_locked] anyway; why isn't it set here?!
	while(vsync_Count1 < 30) {
	}

	curve_trail_count = 8;
	playchars_available = playchars_available_load();
}

void near select_free(void)
{
	for(int i = CDG_SELECT_FIRST; i < CDG_SELECT_COUNT; i++) {
		cdg_free(i);
	}
	super_free();
}

inline void sel_p1_pic_put(void) {
	cdg_put_8(
		P1_LEFT,
		PIC_TOP,
		(!sel_confirmed[0] ? (CDG_PIC + sel[0]) : (CDG_PIC_SELECTED + 0))
	);
}

void near vs_sel_pics_put(void)
{
	sel_p1_pic_put();
	cdg_put_hflip_8(
		P2_LEFT,
		PIC_TOP,
		(!sel_confirmed[1] ? (CDG_PIC + sel[1]) : (CDG_PIC_SELECTED + 1))
	);
}

void near story_sel_pics_put(void)
{
	sel_p1_pic_put();
	cdg_put_8(P2_LEFT, PIC_TOP, (CDG_PIC_SELECTED + 1));
}

#define stat_star_row_put(pid, row_top, star_i, star_left) { \
	star_i = 5; \
	star_left = (((pid == 0) ? P1_LEFT : P2_LEFT) + STATS_W - 20); \
	while(PLAYCHAR_STATS[sel[pid]][stat_i] < star_i) { \
		grcg_boxfill( \
			star_left, \
			row_top, \
			(star_left + STAT_STAR_W - 1), \
			(row_top + STAT_STAR_H -1) \
		); \
		star_i--; \
		star_left -= STAT_STAR_PADDED_W; \
	} \
}

void near stats_put(void)
{
	int stat_i;
	int star_i;
	screen_x_t star_left;

	cdg_put_noalpha_8(P1_LEFT, STATS_TOP, CDG_STATS);
	if(resident->game_mode != GM_STORY) {
		cdg_put_noalpha_8(P2_LEFT, STATS_TOP, CDG_STATS);
	}

	grcg_setcolor(GC_RMW, 14);
	stat_i = 0;
	screen_y_t row_top = (STATS_TOP + 11);
	while(stat_i < STAT_COUNT) {
		stat_star_row_put(0, row_top, star_i, star_left);
		if(resident->game_mode != GM_STORY) {
			stat_star_row_put(1, row_top, star_i, star_left);
		}
		stat_i++;
		row_top += STAT_STAR_H;
	}

	grcg_off();
}

void near names_put(void)
{
	screen_y_t top = NAMES_TOP;
	int playchar = 0;
	while(playchar < playchars_available) {
		static_assert(NAME_W == (2 * BFNT_ASSUMED_MAX_W));
		super_put((NAMES_LEFT + (0 * (NAME_W / 2))), top, ((playchar * 2) + 0));
		super_put((NAMES_LEFT + (1 * (NAME_W / 2))), top, ((playchar * 2) + 1));
		playchar++;
		top += NAME_PADDED_H;
	}
}

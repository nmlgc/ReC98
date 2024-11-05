/// Character selection menu
/// ------------------------

#pragma option -zPgroup_01

#include "th03/op/m_select.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
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

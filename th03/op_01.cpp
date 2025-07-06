/* ReC98
 * -----
 * Code segment #1 of TH03's OP.EXE
 */

#pragma option -zPgroup_01

#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/rank.h"
#include "th01/math/clamp.hpp"
#include "th01/core/initexit.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/gaiji/str.hpp"
#include "th02/op/menu.hpp"
#include "th02/op/m_music.hpp"
#include "th03/common.h"
#include "th03/resident.hpp"
#include "th03/hardware/input.h"
#include "th03/formats/cdg.h"
#include "th03/formats/cfg_impl.hpp"
#include "th03/core/initexit.h"
#include "th03/gaiji/gaiji.h"
#include "th03/snd/snd.h"
#include "th03/shiftjis/fns.hpp"
#include "th03/shiftjis/main.hpp"
#include "th03/op/m_main.hpp"
#include "th03/op/m_select.hpp"
#include <conio.h>
#include <mem.h>
#include <stddef.h>

enum main_choice_t {
	MC_STORY,
	MC_VS,
	MC_MUSICROOM,
	MC_REGIST_VIEW,
	MC_OPTION,
	MC_QUIT,
	MC_COUNT,
};

enum option_choice_t {
	OC_RANK,
	OC_BGM,
	OC_KEY_MODE,
	OC_QUIT,
	OC_COUNT,
};

enum vs_choice_t {
	VC_COUNT = VS_MODE_COUNT,
};

// Proportional gaiji strings
// --------------------------

enum gaiji_th03_mikoft_t {
	gp_Start = 0x30,
	gp_Start_last = ((gp_Start + 3) - 1),
	gp_VS_Start,
	gp_VS_Start_last = ((gp_VS_Start + 6) - 1),
	gp_Option = 0x3D,
	gp_Option_last = ((gp_Option + 4) - 1),
	gp_Music_room,
	gp_Music_room_last = ((gp_Music_room + 7) - 1),
	gp_Quit,
	gp_Quit_last = ((gp_Quit + 3) - 1),
	gp_Music,
	gp_Music_last = ((gp_Music + 4) - 1),
	gp_FM_86_,
	gp_FM_86__last = ((gp_FM_86_ + 4) - 1),
	gp_MIDI__SC_88_,
	gp_MIDI__SC_88__last = ((gp_MIDI__SC_88_ + 7) - 1),
	gp_off,
	gp_off_last = ((gp_off + 2) - 1),
	gp_KeyConfig,
	gp_KeyConfig_last = ((gp_KeyConfig + 6) - 1),
	gp_Type,
	gp_Type_last = ((gp_Type + 3) - 1),
	gp_1,
	gp_2,
	gp_3,
	gp_Key,
	gp_Key_last = ((gp_Key + 2) - 1),
	gp_Joy,
	gp_Joy_last = ((gp_Joy + 2) - 1),
	gp_vs,
	gp_vs_last = ((gp_vs + 2) - 1),
	gp_Rank,
	gp_Rank_last = ((gp_Rank + 3) - 1),
	gp_Easy,
	gp_Easy_last = ((gp_Easy + 3) - 1),
	gp_Normal,
	gp_Normal_last = ((gp_Normal + 4) - 1),
	gp_Hard,
	gp_Hard_last = ((gp_Hard + 3) - 1),
	gp_Lunatic,
	gp_Lunatic_last = ((gp_Lunatic + 4) - 1),

	gp_HiScore = 0x82,
	gp_HiScore_last = ((gp_HiScore + 5) - 1),
	gp_1P_vs = 0x88,
	gp_1P_vs_last = ((gp_1P_vs + 4) - 1),
	gp__CPU,
	gp__CPU_last = ((gp__CPU + 4) - 1),
	gp_CPU_vs = 0x92,
	gp_CPU_vs_last = ((gp_CPU_vs + 4) - 1),
	gp__2P,
	gp__2P_last = ((gp__2P + 4) - 1),
};

// Constructs a VS choice string out of its two halves.
#define g_str_vs(first, second) { g_str_4(first), g_str_4(second), '\0' }
// --------------------------

bool snd_sel_disabled = false; // Yes, it's just (!snd_fm_possible).

/// YUME.CFG loading and saving
/// ---------------------------

void near cfg_load(void)
{
	cfg_t cfg;

	cfg_load_and_set_resident(cfg, CFG_FN_CAPS);

	resident->bgm_mode = cfg.opts.bgm_mode;
	snd_determine_mode();
	snd_sel_disabled = false;
	if(!snd_active) {
		resident->bgm_mode = SND_BGM_OFF;
		snd_sel_disabled = true;
	} else if(cfg.opts.bgm_mode == SND_BGM_OFF) {
		snd_active = false;
	}

	resident->key_mode = cfg.opts.key_mode;
	resident->rank = cfg.opts.rank;
}

inline void cfg_save_bytes(cfg_t &cfg, size_t bytes) {
	file_append(CFG_FN_CAPS);
	file_seek(0, SEEK_SET);

	cfg.opts.bgm_mode = resident->bgm_mode;
	cfg.opts.key_mode = resident->key_mode;
	cfg.opts.rank = resident->rank;

	file_write(&cfg.opts, bytes);
	file_close();
}

void near cfg_save(void)
{
	cfg_t cfg;
	cfg_save_bytes(cfg, 4); // MODDERS: Should be `sizeof(cfg.opts)`
}

void near cfg_save_exit(void)
{
	cfg_t cfg = { 0 };
	cfg_save_bytes(cfg, sizeof(cfg));
}
/// ---------------------------

bool near switch_to_mainl(void)
{
	memset(resident->score_last, 0, sizeof(resident->score_last));
	cfg_save();

	// ZUN landmine: The system's previous gaiji should be restored *after*
	// TRAM gets cleared in game_exit(), not before while we're still showing
	// menu text.
	gaiji_restore();

	snd_kaja_func(KAJA_SONG_STOP, 0);

	// ZUN landmine: The screen clearing done in this function will almost
	// certainly not run within VBLANK.
	game_exit();

	entrypoint_exec(EP_CUTSCENE);
	return false;
}

bool near story_menu(void)
{
	enum {
		RANDOM_OPPONENT_MIN = PLAYCHAR_REIMU,
		RANDOM_OPPONENT_MAX = PLAYCHAR_RIKAKO,
		RANDOM_OPPONENT_COUNT = (
			(RANDOM_OPPONENT_MAX - RANDOM_OPPONENT_MIN) + 1
		),
	};

	static bool opponent_seen[RANDOM_OPPONENT_COUNT] = { false };

	// ACTUAL TYPE: playchar_t
	static const uint8_t STAGE7_OPPONENT_FOR[PLAYCHAR_COUNT] = {
		PLAYCHAR_MIMA, // for Reimu
		PLAYCHAR_REIMU, // for Mima
		PLAYCHAR_REIMU, // for Marisa
		PLAYCHAR_MARISA, // for Ellen
		PLAYCHAR_REIMU, // for Kotohime
		PLAYCHAR_ELLEN, // for Kana
		PLAYCHAR_KANA, // for Rikako
		PLAYCHAR_KOTOHIME, // for Chiyuri
		PLAYCHAR_RIKAKO, // for Yumemi
	};

	int stage;
	int candidate;

	resident->demo_num = 0;
	resident->pid_winner = 0;
	resident->story_stage = 0;
	resident->is_cpu[0] = false;
	resident->is_cpu[1] = true;
	resident->game_mode = GM_STORY;
	resident->story_lives = CREDIT_LIVES;
	resident->show_score_menu = false;
	resident->playchar_paletted[1].v = -1;

	if(select_menu(SM_STORY)) {
		return true;
	}

	const PlaycharPalettedOptional p1_playchar_paletted = (
		resident->playchar_paletted[0]
	);

	// ACTUAL TYPE: playchar_t
	int stage7_opponent = STAGE7_OPPONENT_FOR[p1_playchar_paletted.char_id()];
	irand_init(resident->rand);

	for(stage = 0; stage < 6; stage++) {
		// Confirmed to terminate for all 2³² possible seeds and all original
		// combinations of player character and Stage 7 opponent.
		do {
			candidate = (
				RANDOM_OPPONENT_MIN + (irand() % RANDOM_OPPONENT_COUNT)
			);
		} while(opponent_seen[candidate] || (stage7_opponent == candidate));
		opponent_seen[candidate] = true;
		resident->story_opponents[stage].v = TO_OPTIONAL_PALETTED(candidate);
	}
	resident->story_opponents[6].v = TO_OPTIONAL_PALETTED(stage7_opponent);
	resident->story_opponents[7].set(PLAYCHAR_CHIYURI);
	resident->story_opponents[8].set(PLAYCHAR_YUMEMI);

	// Select alternate palette on collision
	for(stage = 0; stage < STAGE_COUNT; stage++) {
		if(resident->story_opponents[stage].v == p1_playchar_paletted.v) {
			resident->story_opponents[stage].v++;
		}
	}

	resident->playchar_paletted[1] = resident->story_opponents[0];
	resident->rem_credits = 3;
	resident->op_animation_fast = false;
	resident->skill = (70 + (resident->rank * 25));
	return switch_to_mainl();
}

bool near select_vs_menu(vs_mode_t mode)
{
	resident->is_cpu[0] = ((mode == VS_CPU_CPU) ? true : false);
	resident->is_cpu[1] = ((mode != VS_1P_2P) ? true : false);
	resident->demo_num = 0;
	resident->pid_winner = 0;
	resident->story_stage = 0;
	resident->game_mode = (GM_VS + mode);
	resident->show_score_menu = false;

	if(select_menu((mode == VS_1P_2P) ? SM_VS_2P : SM_VS_CPU)) {
		resident->game_mode = GM_NONE;
		return true;
	}

	return switch_to_mainl();
}

void near start_demo(void)
{
	static const int8_t PAIRINGS[DEMO_COUNT][PLAYER_COUNT] = {
		TO_OPTIONAL_PALETTED(PLAYCHAR_MIMA),
		TO_OPTIONAL_PALETTED(PLAYCHAR_REIMU),

		TO_OPTIONAL_PALETTED(PLAYCHAR_MARISA),
		TO_OPTIONAL_PALETTED(PLAYCHAR_RIKAKO),

		TO_OPTIONAL_PALETTED(PLAYCHAR_ELLEN),
		TO_OPTIONAL_PALETTED(PLAYCHAR_KANA),

		TO_OPTIONAL_PALETTED(PLAYCHAR_KOTOHIME),
		TO_OPTIONAL_PALETTED(PLAYCHAR_MARISA),
	};
	static const int32_t RAND[DEMO_COUNT] = { 600, 1000, 3200, 500 };

	resident->is_cpu[0] = true;
	resident->is_cpu[1] = true;
	ring_inc_range(resident->demo_num, 1, DEMO_COUNT);
	resident->pid_winner = 0;

	// Critically important to guarantee deterministic demos!
	resident->story_stage = 0;

	unsigned int pairing_id = (resident->demo_num - 1);
	resident->game_mode = GM_DEMO;
	resident->show_score_menu = false;
	resident->playchar_paletted[0].v = PAIRINGS[pairing_id][0];
	resident->playchar_paletted[1].v = PAIRINGS[pairing_id][1];
	resident->rand = RAND[pairing_id];
	palette_black_out(1);
	switch_to_mainl();
}

struct Menu {
	pixel_t w;
};

extern const Menu MENU_MAIN;
extern const Menu MENU_OPTION;

const Menu near *menu_prev;
const Menu near *menu_cur;

void near wait_for_input_or_start_demo_then_box_to_main_animate(void)
{
	{
		input_sp = INPUT_NONE;
		int frame = 0;
		while(input_sp == INPUT_NONE) {
			input_mode_interface();
			resident->rand++;
			frame++;
			if(frame > 520) {
				start_demo();
			}
			frame_delay(1);
		}
	}
	menu_cur = &MENU_MAIN;
	menu_prev = menu_cur;
	super_put(BOX_LEFT, BOX_TOP, OPWIN_LEFT);
	box_animate((OPWIN_W + OPWIN_STEP_W), menu_cur->w);
}

bool near score_menu(void)
{
	resident->story_stage = STAGE_NONE;
	resident->show_score_menu = true;
	resident->game_mode = GM_NONE;
	return switch_to_mainl();
}

/// The menu
/// --------

// Must be non-`const` for data ordering reasons. Declared at global scope
// because
// 1) the same [COMMAND_QUIT] string is used in both the main and Option menu,
//    and
// 2) some of those are unused, which points toward ZUN having declared them at
//    global scope as well.
char COMMAND_STORY[] = { g_str_3(gp_Start), '\0' };
char COMMAND_VS[] = { g_str_6(gp_VS_Start), '\0' };
char COMMAND_MUSICROOM[] = { g_str_7(gp_Music_room), '\0' };
char COMMAND_REGIST_VIEW[] = { g_str_5(gp_HiScore), '\0' };
char COMMAND_OPTION[] = { g_str_4(gp_Option), '\0' };
char COMMAND_QUIT[] = { g_str_3(gp_Quit), '\0' };

char LABEL_RANK[] = { g_str_3(gp_Rank), '\0' };
char LABEL_MUSIC[] = { g_str_4(gp_Music), '\0' };
char LABEL_KEYCONFIG[] = { g_str_6(gp_KeyConfig), '\0' };

char VALUE_SPACES[] = { g_SP, g_SP, g_SP, g_SP, '\0' };
char VALUE_EASY[] = { g_str_3(gp_Easy), '\0' };
char VALUE_NORMAL[] = { g_str_4(gp_Normal), '\0' };
char VALUE_HARD[] = { g_str_3(gp_Hard), '\0' };
char VALUE_LUNATIC[] = { g_str_4(gp_Lunatic), '\0' };

char VALUE_OFF[8] = { g_SP, g_SP, g_str_2(gp_off), g_SP, g_SP, g_SP };
char VALUE_FM[8] = { g_SP, g_str_4(gp_FM_86_), g_SP, g_SP };
char VALUE_MIDI[8] = { g_str_7(gp_MIDI__SC_88_) };

// The initial names for the three input modes? Unused in the final game.
char VALUE_TYPE_1[] = { g_str_3(gp_Type), gp_1, '\0' };
char VALUE_TYPE_2[] = { g_str_3(gp_Type), gp_2, '\0' };
char VALUE_TYPE_3[] = { g_str_3(gp_Type), gp_3, '\0' };

char VALUE_KEY_KEY[] = {
	g_str_2(gp_Key), g_str_2(gp_vs), g_str_2(gp_Key), '\0',
};
char VALUE_JOY_KEY[] = {
	g_str_2(gp_Joy), g_str_2(gp_vs), g_str_2(gp_Key), '\0',
};
char VALUE_KEY_JOY[] = {
	g_str_2(gp_Key), g_str_2(gp_vs), g_str_2(gp_Joy), '\0',
};

// Globals
// -------

int8_t menu_sel = 0;
bool quit = false;
bool input_allowed;

int8_t in_option; // ACTUAL TYPE: bool
menu_put_func_t menu_put;
// -------

bool pascal near input_is_quit(int sel_quit)
{
	return (
		((input_sp & (INPUT_OK | INPUT_SHOT)) && (menu_sel == sel_quit)) ||
		(input_sp & INPUT_CANCEL)
	);
}

// These menus want to display centered strings. However, the underlying gaiji
// of all of these (except "Start", which exactly fits into the 48 pixels
// covered by its 3 gaiji) are left-aligned and leave anywhere from 6 to 14
// pixels of trailing blank space in their last gaiji. Hence, ZUN shifts the
// mathematically correct center a bit to get as close as possible to visual
// centering, but still fails to perfectly center three of these labels; only
// "Music room" and "Option" are. Would be a ZUN bug, but a fix would also have
// to change assets. We'll probably only do that once we translate the game.
#define gaiji_w_shifted(str, shift_x) ( \
	((sizeof(str) - 1) + shift_x) * GAIJI_W \
)

inline tram_y_t choice_tram_y(unsigned int line) {
	return ((BOX_TOP / GLYPH_H) + 1 + line);
}

#define choice_put_centered(center_x, line, shift_x, str, atrb) { \
	gaiji_putsa( \
		((center_x - (gaiji_w_shifted(str, shift_x) / 2)) / GLYPH_HALF_W), \
		choice_tram_y(line), \
		str, \
		atrb \
	); \
}

void pascal near vs_choice_put(int sel, tram_atrb2 atrb)
{
	enum {
		W = (8 * GAIJI_W),
		TRAM_LEFT = ((BOX_SUBMENU_CENTER_X - (W / 2)) / GLYPH_HALF_W),
	};
	if(sel == VS_1P_CPU) {
		static const char STR[] = g_str_vs(gp_1P_vs, gp__CPU);
		gaiji_putsa(TRAM_LEFT, choice_tram_y(1), STR, atrb);
	} else if(sel == VS_1P_2P) {
		static const char STR[] = g_str_vs(gp_1P_vs, gp__2P);
		gaiji_putsa(TRAM_LEFT, choice_tram_y(2), STR, atrb);
	} else /* if (sel == VS_CPU_CPU) */ {
		static const char STR[] = g_str_vs(gp_CPU_vs, gp__CPU);
		gaiji_putsa(TRAM_LEFT, choice_tram_y(3), STR, atrb);
	}
}

bool near vs_menu(void)
{
	// ZUN quirk: This assignment causes any initially held inputs to be
	// processed immediately, just like in the Main menu at startup, but unlike
	// after a later switch between the Main and Option menu.
	input_t input_prev = INPUT_NONE;

	text_clear();
	box_animate(MAIN_W, SUBMENU_W);

	menu_sel = VS_1P_CPU;
	for(int i = 0; i < VC_COUNT; i++) {
		vs_choice_put(i, ((i == menu_sel) ? TX_WHITE : TX_BLACK));
	}

	while(1) {
		input_mode_interface();
		if(input_prev == INPUT_NONE) {
			if(input_sp & (INPUT_UP | INPUT_DOWN)) {
				int8_t delta = ((input_sp & INPUT_UP) ? -1 : +1);
				vs_choice_put(menu_sel, TX_BLACK);
				ring_step(menu_sel, delta, VS_1P_CPU, VS_CPU_CPU);
				vs_choice_put(menu_sel, TX_WHITE);
			}
			if((input_sp & (INPUT_SHOT | INPUT_OK))) {
				return select_vs_menu(static_cast<vs_mode_t>(menu_sel));
			}
			// ZUN bug: Should have added a INPUT_CANCEL branch to allow
			// players to quit back to the main menu once they entered this
			// one.
		}
		input_prev = input_sp;
		frame_delay(1);
	}
}

void pascal near main_choice_put(int sel, tram_atrb2 atrb)
{
	if(sel == MC_STORY) {
		choice_put_centered(BOX_MAIN_CENTER_X, 0, 0, COMMAND_STORY, atrb);
	} else if(sel == MC_VS) {
		choice_put_centered(BOX_MAIN_CENTER_X, 1, -1, COMMAND_VS, atrb);
	} else if(sel == MC_MUSICROOM) {
		choice_put_centered(BOX_MAIN_CENTER_X, 2, -1, COMMAND_MUSICROOM, atrb);
	} else if(sel == MC_REGIST_VIEW) {
		choice_put_centered(
			BOX_MAIN_CENTER_X, 3, -1, COMMAND_REGIST_VIEW, atrb
		);
	} else if(sel == MC_OPTION) {
		choice_put_centered(BOX_MAIN_CENTER_X, 4, -1, COMMAND_OPTION, atrb);
	} else if(sel == MC_QUIT) {
		choice_put_centered(BOX_MAIN_CENTER_X, 5, -1, COMMAND_QUIT, atrb);
	}
}

void pascal near option_choice_put(int sel, tram_atrb2 atrb)
{
	enum {
		// ZUN quirk: Not the center of the left column.
		LABEL_CENTER_X = BOX_MAIN_CENTER_X,

		VALUE_LEFT = BOX_SUBMENU_CENTER_X,
		VALUE_W = (BOX_SUBMENU_RIGHT - VALUE_LEFT),
		VALUE_TRAM_LEFT = (VALUE_LEFT / GLYPH_HALF_W),
		VALUE_CENTER_X = (VALUE_LEFT + (VALUE_W / 2)),
	};

	if(sel == OC_RANK) {
		static_assert(sizeof(VALUE_SPACES) >= sizeof(VALUE_EASY));
		static_assert(sizeof(VALUE_SPACES) >= sizeof(VALUE_NORMAL));
		static_assert(sizeof(VALUE_SPACES) >= sizeof(VALUE_HARD));
		static_assert(sizeof(VALUE_SPACES) >= sizeof(VALUE_LUNATIC));

		choice_put_centered(LABEL_CENTER_X, 0, 0, LABEL_RANK, atrb);
		choice_put_centered(VALUE_CENTER_X, 0, 1, VALUE_SPACES, TX_WHITE);
		switch(resident->rank) {
		case RANK_EASY:
			choice_put_centered(VALUE_CENTER_X, 0, 1, VALUE_EASY, atrb);
			break;
		case RANK_NORMAL:
			choice_put_centered(VALUE_CENTER_X, 0, 1, VALUE_NORMAL, atrb);
			break;
		case RANK_HARD:
			choice_put_centered(VALUE_CENTER_X, 0, 1, VALUE_HARD, atrb);
			break;
		case RANK_LUNATIC:
			choice_put_centered(VALUE_CENTER_X, 0, 1, VALUE_LUNATIC, atrb);
			break;
		}
	} else if(sel == OC_BGM) {
		choice_put_centered(LABEL_CENTER_X, 2, -1, LABEL_MUSIC, atrb);
		switch(resident->bgm_mode) {
		case SND_BGM_OFF:
			gaiji_putsa(VALUE_TRAM_LEFT, choice_tram_y(2), VALUE_OFF, atrb);
			break;
		case SND_BGM_FM:
			gaiji_putsa(VALUE_TRAM_LEFT, choice_tram_y(2), VALUE_FM, atrb);
			break;
		case SND_BGM_MIDI:
			gaiji_putsa(VALUE_TRAM_LEFT, choice_tram_y(2), VALUE_MIDI, atrb);
			break;
		}
	} else if(sel == OC_KEY_MODE) {
		choice_put_centered(LABEL_CENTER_X, 4, -1, LABEL_KEYCONFIG, atrb);
		switch(resident->key_mode) {
		case KM_KEY_KEY:
			choice_put_centered(VALUE_CENTER_X, 4, -1, VALUE_KEY_KEY, atrb);
			break;
		case KM_JOY_KEY:
			choice_put_centered(VALUE_CENTER_X, 4, -1, VALUE_JOY_KEY, atrb);
			break;
		case KM_KEY_JOY:
			choice_put_centered(VALUE_CENTER_X, 4, -1, VALUE_KEY_JOY, atrb);
			break;
		}
	} else if(sel == OC_QUIT) {
		choice_put_centered(BOX_SUBMENU_CENTER_X, 5, 0, COMMAND_QUIT, atrb);
	}
}

void pascal near menu_sel_update_and_render(int8_t max, int8_t direction)
{
	menu_put(menu_sel, TX_BLACK);
	menu_sel += direction;
	if(menu_sel < ring_min()) {
		menu_sel = max;
	}
	if(menu_sel > max) {
		menu_sel = 0;
	}
	menu_put(menu_sel, TX_WHITE);
}

#define menu_init(in_this_menu, choice_count, put) { \
	for(int i = 0; i < choice_count; i++) { \
		put(i, ((menu_sel == i) ? TX_WHITE : TX_BLACK)); \
	} \
	menu_put = put; \
	in_this_menu = true; \
	input_allowed = false; \
}

inline void return_from_other_screen_to_main(bool& in_this_menu) {
	op_fadein_animate();
	wait_for_input_or_start_demo_then_box_to_main_animate();
	select_cdg_load_part2_of_4();
	in_this_menu = false;
	input_allowed = false;
	menu_cur = &MENU_MAIN;
}

// Sure, *maybe* these names should point out the possibility of a blocking
// box transition animation, but main_update_and_render() also directly enters
// the even more blocking character selection and Music Room screens.
void near main_update_and_render(void)
{
	static bool in_this_menu = false;

	if(!in_this_menu) {
		menu_init(in_this_menu, MC_COUNT, main_choice_put);
	}

	if(!input_allowed) {
		return;
	}
	menu_update_vertical(input_sp, MC_COUNT);
	if((input_sp & INPUT_OK) || (input_sp & INPUT_SHOT)) {
		switch(menu_sel) {
		case MC_STORY:
			story_menu();
			return_from_other_screen_to_main(in_this_menu);
			return;
		case MC_VS:
			resident->playchar_paletted[0].set(PLAYCHAR_REIMU);
			resident->playchar_paletted[1].set(PLAYCHAR_REIMU);
			vs_menu();
			return_from_other_screen_to_main(in_this_menu);
			return;
		case MC_MUSICROOM:
			{for(int i = 0; i < CDG_SLOT_COUNT; i++) {
				cdg_free(i);
			}}
			super_free();
			musicroom_menu();
			return_from_other_screen_to_main(in_this_menu);
			return;
		case MC_REGIST_VIEW:
			score_menu();
			break; // launches into MAINL.EXE
		case MC_OPTION:
			in_this_menu = false;
			in_option = true;
			menu_cur = &MENU_OPTION;
			menu_sel = OC_RANK;
			break;
		case MC_QUIT:
			in_this_menu = false; // We're quitting anyway...
			quit = true;
			break;
		}
	}
	if(input_sp & INPUT_CANCEL) {
		quit = true;
	}
}

void near option_update_and_render(void)
{
	static bool in_this_menu = false;

	if(!in_this_menu) {
		menu_init(in_this_menu, OC_COUNT, option_choice_put);
	}

	if(!input_allowed) {
		return;
	}
	menu_update_vertical(input_sp, OC_COUNT);

	if(input_sp & (INPUT_LEFT | INPUT_RIGHT)) {
		int8_t delta = ((input_sp & INPUT_LEFT) ? -1 : +1);
		switch(menu_sel) {
		case OC_RANK:
			ring_step(resident->rank, delta, RANK_EASY, RANK_LUNATIC);
			break;
		case OC_BGM:
			if(!snd_sel_disabled) {
				if(resident->bgm_mode == SND_BGM_OFF) {
					resident->bgm_mode = SND_BGM_FM;
					snd_kaja_func(KAJA_SONG_STOP, 0);
					snd_determine_mode();
					snd_kaja_func(KAJA_SONG_PLAY, 0);
				} else {
					resident->bgm_mode = SND_BGM_OFF;
					snd_kaja_func(KAJA_SONG_STOP, 0);
					snd_active = false;
				}
			}
			break;
		case OC_KEY_MODE:
			ring_step(resident->key_mode, delta, KM_KEY_KEY, KM_KEY_JOY);
			break;
		}
		option_choice_put(menu_sel, TX_WHITE);
	}
	if(input_is_quit(OC_QUIT)) {
		in_this_menu = false;
		menu_sel = MC_OPTION;
		in_option = false;
		menu_cur = &MENU_MAIN;
	}
}

const Menu MENU_MAIN = {
	MAIN_W,
};
const Menu MENU_OPTION = {
	SUBMENU_W,
};

int main_op(int, const char *[])
{
	graph_400line();
	text_clear();
	respal_create();

	if(game_init_op(OP_AND_END_PF_FN)) {
		dos_puts2(ERROR_OUT_OF_MEMORY);
		getch();
		return 1;
	}

	gaiji_backup();
	gaiji_entry_bfnt(GAIJI_FN);
	cfg_load();
	if((resident->game_mode >= GM_VS) && (resident->demo_num == 0)) {
		select_cdg_load_part1_of_4();
		select_cdg_load_part3_of_4();
		select_cdg_load_part2_of_4();
		select_vs_menu(static_cast<vs_mode_t>(resident->game_mode - GM_VS));
	}

	if(!resident->op_animation_fast) {
		op_animate();
		resident->op_animation_fast = true;
	} else {
		resident->op_animation_fast = false;
		op_fadein_animate();
	}
	wait_for_input_or_start_demo_then_box_to_main_animate();

	// Showing the menu options before loading part 2 is actually a pretty nice
	// idea to better hide potentially long loading times.
	//
	// ZUN quirk: Resetting [input_sp] regardless of the actually held keys
	// causes ZUN's original version of main_update_and_render() to always
	// return with its instance of [input_allowed] set to `true`. Thus, any
	// initially held key is supposed to be processed instantly on the first
	// call to the function in the loop below – contrary to what you would
	// expect from the whole input locking system, and contrary to how the game
	// behaves after switching the active menu later on, where inputs *are*
	// locked until the player releases all keys.
	in_option = false;
	input_sp = INPUT_NONE;
	main_update_and_render();
	input_allowed = true;

	select_cdg_load_part2_of_4();

	while(!quit) {
		input_mode_interface();
		if(menu_prev != menu_cur) {
			text_clear();
			box_animate(menu_prev->w, menu_cur->w);
			menu_prev = menu_cur;
		}
		if(input_sp == INPUT_NONE) {
			input_allowed = true;
		}
		switch(in_option) {
		case false:	main_update_and_render();  	break;
		case true: 	option_update_and_render();	break;
		}
		if(input_sp != INPUT_NONE) {
			input_allowed = false;
		}
		resident->rand++;
		frame_delay(1);
	}
	cfg_save_exit();

	// ZUN landmine: The system's previous gaiji should be restored *after*
	// clearing TRAM, not before while we're still showing menu text. Sending
	// ((8,192 × 2) + 512) bytes of data over I/O ports one byte at a time
	// takes a short while, so this can definitely be visible for a fraction of
	// a frame on real, not infinitely fast hardware. Especially since the CRT
	// beam is most certainly in the middle of a frame after the file I/O
	// immediately above.
	// Funnily enough, TH02 got the order correct right in the one place where
	// it mattered in that game.
	//
	// ZUN bloat: Also, game_exit_to_dos() already clears TRAM.
	gaiji_restore();
	text_clear();

	game_exit_to_dos();
	respal_free();

	return 0;
}
/// --------

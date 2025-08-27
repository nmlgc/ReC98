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
#include "th03/formats/cfg_impl.hpp"
#include "th03/core/initexit.h"
#include "th03/gaiji/gaiji.h"
#include "th03/snd/snd.h"
#include "th03/shiftjis/fns.hpp"
#include "th03/shiftjis/main.hpp"
#include "th03/op/m_main.hpp"
#include "th03/op/m_select.hpp"
#include <conio.h>
#include <stddef.h>
#include <process.h>

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

#define resident_reset_scores(i) { \
	/* ZUN bloat: Very unsafe. */ \
	for(i = 0; i < (PLAYER_COUNT * SCORE_DIGITS); i++) { \
		resident->score_last[0].digits[i] = 0; \
	} \
}

inline bool switch_to_mainl(bool opwin_free) {
	cfg_save();

	// ZUN landmine: The system's previous gaiji should be restored *after*
	// TRAM gets cleared in game_exit(), not before while we're still showing
	// menu text.
	gaiji_restore();

	snd_kaja_func(KAJA_SONG_STOP, 0);
	if(opwin_free) {
		super_free(); // ZUN bloat: Process termination will do this anyway.
	}

	// ZUN landmine: The screen clearing done in this function will almost
	// certainly not run within VBLANK.
	game_exit();

	execl(BINARY_MAINL, BINARY_MAINL, nullptr);
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

	if(select_story_menu()) {
		return true;
	}

retry_opponent_selection:
	// ACTUAL TYPE: playchar_t
	int stage7_opponent = STAGE7_OPPONENT_FOR[
		resident->playchar_paletted[0].char_id_16()
	];
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

		// ZUN bloat: Should not change types.
		#define candidate_paletted candidate
		candidate_paletted = TO_OPTIONAL_PALETTED(candidate);
		resident->story_opponents[stage].v = candidate_paletted;

		// ZUN bloat: All of these palette swaps could have been done in a
		// single loop at the end.
		if(candidate_paletted == resident->playchar_paletted[0].v) {
			resident->story_opponents[stage].v = (candidate_paletted + 1);
		}
		#undef candidate_paletted
	}

	resident->playchar_paletted[1] = resident->story_opponents[0];
	resident->story_opponents[6].v = TO_OPTIONAL_PALETTED(stage7_opponent);

	// ZUN bloat: Palette swaps...
	resident->story_opponents[7].set(PLAYCHAR_CHIYURI);
	if(
		resident->playchar_paletted[0].v ==
		TO_OPTIONAL_PALETTED(PLAYCHAR_CHIYURI)
	) {
		resident->story_opponents[7].v++;
	}
	resident->story_opponents[8].set(PLAYCHAR_YUMEMI);
	if(
		resident->playchar_paletted[0].v ==
		TO_OPTIONAL_PALETTED(PLAYCHAR_YUMEMI)
	) {
		resident->story_opponents[8].v++;
	}

	// ZUN bloat: This can never happen.
	for(stage = 0; stage < STAGE_COUNT; stage++) {
		if(resident->story_opponents[stage].char_id_16() >= PLAYCHAR_COUNT) {
			goto retry_opponent_selection;
		}
	}

	resident_reset_scores(stage);
	resident->rem_credits = 3;
	resident->op_animation_fast = false;
	resident->skill = (70 + (resident->rank * 25));
	return switch_to_mainl(false);
}

inline tram_y_t choice_tram_y(unsigned int line) {
	return ((BOX_TOP / GLYPH_H) + 1 + line);
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
	int sel;

	// ZUN quirk: This assignment causes any initially held inputs to be
	// processed immediately, just like in the Main menu at startup, but unlike
	// after a later switch between the Main and Option menu.
	input_t input_prev = INPUT_NONE;

	// After a match, we come back here, skip the menu, and launch into
	// character selection.
	if(resident->game_mode < GM_VS) {
		text_clear();
		box_main_to_submenu_animate();

		sel = VS_1P_CPU;
		vs_choice_put(VS_1P_CPU, TX_WHITE);
		vs_choice_put(VS_1P_2P, TX_BLACK);
		vs_choice_put(VS_CPU_CPU, TX_BLACK);

		while(1) {
			input_mode_interface();
			if(input_prev == INPUT_NONE) {
				if(input_sp & INPUT_UP) {
					vs_choice_put(sel, TX_BLACK);
					ring_dec(sel, VS_CPU_CPU);
					vs_choice_put(sel, TX_WHITE);
				}
				if(input_sp & INPUT_DOWN) {
					vs_choice_put(sel, TX_BLACK);
					ring_inc(sel, VS_CPU_CPU);
					vs_choice_put(sel, TX_WHITE);
				}
				if((input_sp & INPUT_SHOT) || (input_sp & INPUT_OK)) {
					break;
				}
				// ZUN bug: Should have added a INPUT_CANCEL branch to allow
				// players to quit back to the main menu once they entered this
				// one.
			}
			input_prev = input_sp;
			frame_delay(1);
		}
	} else {
		sel = (resident->game_mode - GM_VS);
	}

	resident->is_cpu[0] = ((sel == VS_CPU_CPU) ? true : false);
	resident->is_cpu[1] = ((sel != VS_1P_2P) ? true : false);
	resident->demo_num = 0;
	resident->pid_winner = 0;
	resident->story_stage = 0;
	resident->game_mode = (GM_VS + sel);
	resident->show_score_menu = false;

	// ZUN bloat: Could be compressed into a single branch.
	if(sel == VS_1P_2P) {
		if(select_1p_vs_2p_menu()) {
			resident->game_mode = GM_NONE;
			return true;
		}
	} else {
		if(select_vs_cpu_menu()) {
			resident->game_mode = GM_NONE;
			return true;
		}
	}

	resident_reset_scores(sel);
	return switch_to_mainl(false);
}

void near start_demo(void)
{
	static const int8_t PAIRINGS[DEMO_COUNT * PLAYER_COUNT] = {
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

	resident->game_mode = GM_DEMO;
	resident->show_score_menu = false;

	// ZUN bloat: A two-dimensional array would have been more readable and
	// would have generated better code.
	resident->playchar_paletted[0].v = (
		PAIRINGS[((resident->demo_num - 1) * PLAYER_COUNT) + 0]
	);
	resident->playchar_paletted[1].v = (
		PAIRINGS[((resident->demo_num - 1) * PLAYER_COUNT) + 1]
	);

	resident->rand = RAND[resident->demo_num - 1];
	int i;
	resident_reset_scores(i);
	palette_black_out(1);

	switch_to_mainl(false);
}

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

	super_put(BOX_LEFT, BOX_TOP, OPWIN_LEFT);

	// ZUN bloat: Should maybe be merged with the two others in `m_main.cpp`.
	{for(
		screen_x_t right_left = (BOX_LEFT + OPWIN_W);
		right_left < (BOX_MAIN_RIGHT - OPWIN_STEP_W);
		right_left += OPWIN_STEP_W
	) {
		box_column16_unput(right_left);
		super_put(right_left, BOX_TOP, OPWIN_RIGHT);
		frame_delay(1);
	}}
}

bool near score_menu(void)
{
	resident->story_stage = STAGE_NONE;
	resident->show_score_menu = true;
	resident->game_mode = GM_NONE;
	int i;
	resident_reset_scores(i);
	return switch_to_mainl(true);
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

// ZUN bloat: Unused, but looks like a gaiji version of the space string below.
// Since that is the only call to text_putsa() in this binary, using this one
// would have also removed the need to link in that function.
char UNUSED_SPACES[5] = { g_SP, g_SP, g_SP, g_SP, '\0' };

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
bool in_main = true;

// ZUN bloat: Should be function-level statics.
bool main_input_allowed;
bool option_input_allowed;

int8_t in_option; // ACTUAL TYPE: bool
static int8_t padding; // ZUN bloat
menu_put_func_t menu_put;
// -------

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

#define choice_put_centered(center_x, line, shift_x, str, atrb) { \
	gaiji_putsa( \
		((center_x - (gaiji_w_shifted(str, shift_x) / 2)) / GLYPH_HALF_W), \
		choice_tram_y(line), \
		str, \
		atrb \
	); \
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

#pragma option -a2

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
		choice_put_centered(LABEL_CENTER_X, 0, 0, LABEL_RANK, atrb);
		text_putsa(
			(VALUE_TRAM_LEFT + 2), // This is bloat anyway, who cares
			choice_tram_y(0),
			"        ",
			TX_WHITE
		);
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

#define menu_init(in_this_menu, input_allowed, choice_count, put) { \
	input_allowed = false; /* ZUN bloat: Redundant */ \
	for(int i = 0; i < choice_count; i++) { \
		put(i, ((menu_sel == i) ? TX_WHITE : TX_BLACK)); \
	} \
	menu_put = put; \
	in_this_menu = true; \
	input_allowed = false; \
}

inline void return_from_other_screen_to_main(
	bool& in_this_menu, bool& main_input_allowed
) {
	op_fadein_animate();
	wait_for_input_or_start_demo_then_box_to_main_animate();
	select_cdg_load_part2_of_4();
	in_this_menu = false;
	main_input_allowed = false;
	in_main = true;
}

// Sure, *maybe* these names should point out the possibility of a blocking
// box transition animation, but main_update_and_render() also directly enters
// the even more blocking character selection and Music Room screens.
void near main_update_and_render(void)
{
	#define input_allowed	main_input_allowed
	static bool in_this_menu = false;

	if(!in_this_menu) {
		text_clear();
		if(!in_main) {
			box_submenu_to_main_animate();
		}
		in_main = false; // ZUN bloat: Why is this set here, and now?
		menu_init(in_this_menu, input_allowed, MC_COUNT, main_choice_put);
	}

	if(input_sp == INPUT_NONE) {
		input_allowed = true;
	}
	if(!input_allowed) {
		return;
	}
	menu_update_vertical(input_sp, MC_COUNT);
	if((input_sp & INPUT_OK) || (input_sp & INPUT_SHOT)) {
		switch(menu_sel) {
		case MC_STORY:
			story_menu();
			return_from_other_screen_to_main(in_this_menu, input_allowed);
			return;
		case MC_VS:
			resident->playchar_paletted[0].set(PLAYCHAR_REIMU);
			resident->playchar_paletted[1].set(PLAYCHAR_REIMU);
			vs_menu();
			return_from_other_screen_to_main(in_this_menu, input_allowed);
			return;
		case MC_MUSICROOM:
			/* TODO: Replace with the decompiled call
			* 	musicroom_menu();
			* once the segmentation allows us to, if ever */
			_asm { nop; push cs; call near ptr musicroom_menu; }

			return_from_other_screen_to_main(in_this_menu, input_allowed);
			return;
		case MC_REGIST_VIEW:
			score_menu();
			break; // launches into MAINL.EXE
		case MC_OPTION:
			in_this_menu = false;
			in_option = true;
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
	if(input_sp != INPUT_NONE) { // Covers all previous input cases too! Good!
		input_allowed = false;
	}

	#undef input_allowed
}

#define snd_flip() { \
	if(!snd_sel_disabled) { \
		if(resident->bgm_mode == SND_BGM_OFF) { \
			resident->bgm_mode = SND_BGM_FM; \
			snd_kaja_func(KAJA_SONG_STOP, 0); \
			snd_determine_mode(); \
			snd_kaja_func(KAJA_SONG_PLAY, 0); \
		} else { \
			resident->bgm_mode = SND_BGM_OFF; \
			snd_kaja_func(KAJA_SONG_STOP, 0); \
			snd_active = false; \
		} \
		/* ZUN bloat: Already done at the call site. */ \
		option_choice_put(menu_sel, TX_WHITE); \
	} \
}

inline void return_from_option_to_main(bool& option_initialized) {
	option_initialized = false;
	menu_sel = MC_OPTION;
	in_option = false;
}

void near option_update_and_render(void)
{
	#define input_allowed	option_input_allowed
	static bool in_this_menu = false;

	if(!in_this_menu) {
		text_clear();
		box_main_to_submenu_animate();
		menu_init(in_this_menu, input_allowed, OC_COUNT, option_choice_put);
	}

	if(input_sp == INPUT_NONE) {
		input_allowed = true;
	}
	if(!input_allowed) {
		return;
	}
	menu_update_vertical(input_sp, OC_COUNT);

	// ZUN bloat: Could have been deduplicated.
	if(input_sp & INPUT_RIGHT) {
		switch(menu_sel) {
		case OC_RANK:
			ring_inc_range(resident->rank, RANK_EASY, RANK_LUNATIC);
			break;
		case OC_BGM:
			snd_flip();
			break;
		case OC_KEY_MODE:
			ring_inc_range(resident->key_mode, KM_KEY_KEY, KM_KEY_JOY);
			break;
		}
		option_choice_put(menu_sel, TX_WHITE);
	}
	if(input_sp & INPUT_LEFT) {
		switch(menu_sel) {
		case OC_RANK:
			ring_dec_range(resident->rank, RANK_EASY, RANK_LUNATIC);
			break;
		case OC_BGM:
			snd_flip();
			break;
		case OC_KEY_MODE:
			ring_dec_range(resident->key_mode, KM_KEY_KEY, KM_KEY_JOY);
			break;
		}
		option_choice_put(menu_sel, TX_WHITE);
	}

	if((input_sp & INPUT_OK) || (input_sp & INPUT_SHOT)) {
		if(menu_sel == OC_QUIT) {
			return_from_option_to_main(in_this_menu);
		}
	}
	if(input_sp & INPUT_CANCEL) {
		return_from_option_to_main(in_this_menu);
	}
	if(input_sp != INPUT_NONE) { // Covers all previous input cases too! Good!
		input_allowed = false;
	}

	#undef input_allowed
}

void main(void)
{
	graph_400line();
	text_clear();
	respal_create();

	if(game_init_op(OP_AND_END_PF_FN)) {
		dos_puts2(ERROR_OUT_OF_MEMORY);
		getch();
		return;
	}

	gaiji_backup();
	gaiji_entry_bfnt(GAIJI_FN);
	cfg_load();
	if((resident->game_mode >= GM_VS) && (resident->demo_num == 0)) {
		select_cdg_load_part1_of_4();
		select_cdg_load_part3_of_4();
		select_cdg_load_part2_of_4();
		vs_menu();
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
	// means that main_update_and_render() always returns with its instance of
	// [input_allowed] set to `true`. Thus, any initially held key is processed
	// instantly on the first call to the function in the loop below – contrary
	// to what you would expect from the whole input locking system, and
	// contrary to how the game behaves after switching the active menu later
	// on, where inputs *are* locked until the player releases all keys.
	in_option = false;
	input_sp = INPUT_NONE;
	main_update_and_render();

	select_cdg_load_part2_of_4();

	while(!quit) {
		input_mode_interface();
		switch(in_option) {
		case false:	main_update_and_render();  	break;
		case true: 	option_update_and_render();	break;
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
}
/// --------

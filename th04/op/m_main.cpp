#if (GAME == 5)
	#include "th05/mem.h"
	#include "th05/op/start.cpp"
	#include "th05/shiftjis/fns.hpp"
#else
	#include "th03/shiftjis/fnshared.hpp"
	#include "th04/mem.h"
	#include "th04/op/start.cpp"
	#include "th04/shiftjis/fns.hpp"
#endif

#include <conio.h>
#include <string.h>
#include "shiftjis.hpp"
#include "th01/math/clamp.hpp"
#include "th01/hardware/grcg.hpp"
#include "th01/hardware/egc.h"
#include "th02/v_colors.hpp"
#include "th02/op/menu.hpp"
#include "th02/op/m_music.hpp"
#include "th03/core/initexit.h"
#include "th04/hardware/grppsafx.h"
#include "th04/formats/cdg.h"
#include "th04/shiftjis/fnshared.hpp"
#include "th04/shiftjis/m_main.hpp"
#include "th04/sprites/op_cdg.hpp"

#pragma option -a2

enum main_choice_t {
	MC_GAME,
	MC_EXTRA,
	MC_REGIST_VIEW,
	MC_MUSICROOM,
	MC_OPTION,
	MC_QUIT,
	MC_COUNT,
};

enum option_choice_t {
	OC_RANK,
	OC_LIVES,
	OC_BOMBS,
	OC_BGM,
	OC_SE,
	OC_TURBO_OR_SLOW,
	OC_RESET,
	OC_QUIT,
	OC_COUNT,
};

// Coordinates
// -----------
// Terminology:
// • Choice:  The set of selections in a menu.
// • Command: An option-less choice, displayed horizontally centered.
// • Cursor:  The sprites from CAR.CD2.
// • Label:   Any single sprite from SFT2.CD2.
// • Value:   A label that represents the current value of a changeable choice.
// • Option:  A label and a value, displayed next to each other and
//            horizontally centered.

static const pixel_t LABEL_W = 96;
static const pixel_t LABEL_H = 16;

static const pixel_t CURSOR_W = 32;

static const screen_y_t MENU_TOP = ((GAME == 5) ? 250 : 224);

static const screen_x_t COMMAND_LEFT = ((RES_X / 2) - (LABEL_W / 2));

static const pixel_t COMMAND_H = (LABEL_H + 4);
static const screen_x_t COMMAND_CURSOR_LEFT_LEFT = (
	COMMAND_LEFT - (CURSOR_W / 2)
);
static const screen_x_t COMMAND_CURSOR_RIGHT_LEFT = (
	(COMMAND_LEFT + LABEL_W) - (CURSOR_W / 2)
);
static const screen_x_t COMMAND_CURSOR_LEFT_RIGHT_DISTANCE = (
	COMMAND_CURSOR_RIGHT_LEFT - COMMAND_CURSOR_LEFT_LEFT
);

static const screen_x_t MENU_MAIN_LEFT = COMMAND_CURSOR_LEFT_LEFT;
static const pixel_t MENU_MAIN_W = (
	COMMAND_CURSOR_RIGHT_LEFT + CURSOR_W - MENU_MAIN_LEFT
);

inline screen_y_t main_choice_top(int sel /* ACTUAL TYPE: main_choice_t */) {
	return (MENU_TOP + (sel * COMMAND_H));
}

static const screen_x_t OPTION_LABEL_LEFT = ((RES_X / 2) - LABEL_W);
static const screen_x_t OPTION_VALUE_LEFT = (OPTION_LABEL_LEFT + LABEL_W);
static const screen_x_t OPTION_CURSOR_LEFT_LEFT = OPTION_LABEL_LEFT;
static const screen_x_t OPTION_CURSOR_RIGHT_LEFT = (
	OPTION_VALUE_LEFT + LABEL_W - CURSOR_W
);

static const screen_x_t MENU_OPTION_LEFT = OPTION_CURSOR_LEFT_LEFT;
static const pixel_t MENU_OPTION_W = (
	OPTION_CURSOR_RIGHT_LEFT + CURSOR_W - MENU_OPTION_LEFT
);

inline screen_y_t option_choice_top(option_choice_t sel) {
	return ((sel >= OC_QUIT)
		? (MENU_TOP + (OC_RESET * LABEL_H) + ((sel - OC_RESET) * COMMAND_H))
		: (MENU_TOP + (sel * LABEL_H))
	);
}

static const screen_y_t DESC_TOP = (RES_Y - GLYPH_H);
// -----------

// Colors
// ------

const vc2 COL_INACTIVE = ((GAME == 5) ?  8 :  1);
const vc2 COL_ACTIVE   = ((GAME == 5) ? 14 :  8);
const vc2 COL_LOCKED   = ((GAME == 5) ?  2 : 12);
const vc2 COL_DESC     = ((GAME == 5) ?  9 : V_WHITE);
// ------

// Globals
// -------

#if (GAME == 5)
	static int8_t unused = 0; // ZUN bloat
#endif
int8_t menu_sel = 0;
bool quit = false;
int8_t main_menu_unused_1 = 1;
const shiftjis_t* MENU_DESC[] = MENU_DESCRIPTIONS;
resident_t* resident;
int8_t in_option; // ACTUAL TYPE: bool
menu_unput_and_put_func_t menu_unput_and_put;
// -------

#define command_put(top, slot) { \
	cdg_put_nocolors_8(COMMAND_LEFT, top, slot); \
}

inline void option_label_put(option_choice_t sel, op_cdg_slot_t slot) {
	cdg_put_nocolors_8(OPTION_LABEL_LEFT, option_choice_top(sel), slot);
}

#define option_value_put(sel, cdg_value) { \
	cdg_put_nocolors_8(OPTION_VALUE_LEFT, option_choice_top(sel), cdg_value); \
}

#define desc_unput_and_put(desc_id) { \
	egc_copy_rect_1_to_0_16(0, DESC_TOP, RES_X, GLYPH_H); \
	graph_putsa_fx_func = FX_WEIGHT_BOLD; \
	graph_putsa_fx( \
		(RES_X - GLYPH_FULL_W - (strlen(MENU_DESC[desc_id]) * GLYPH_HALF_W)), \
		DESC_TOP, \
		COL_DESC, \
		MENU_DESC[desc_id] \
	); \
}

void pascal near main_unput_and_put(int sel, vc2 col)
{
	screen_y_t top = main_choice_top(sel);
	egc_copy_rect_1_to_0_16(MENU_MAIN_LEFT, top, MENU_MAIN_W, LABEL_H);
	grcg_setcolor(GC_RMW, col);
	int desc_id = sel;

	// ZUN bloat: Could have been deduplicated.
	switch(sel) {
	case MC_GAME:
		command_put(main_choice_top(MC_GAME), CDG_MAIN_GAME);
		desc_id = (22 + resident->rank);
		break;
	case MC_EXTRA:
		if(!extra_unlocked) {
			grcg_setcolor(GC_RMW, COL_LOCKED);
		}
		command_put(main_choice_top(MC_EXTRA), CDG_MAIN_EXTRA);
		break;
	case MC_REGIST_VIEW:
		command_put(main_choice_top(MC_REGIST_VIEW), CDG_MAIN_REGIST_VIEW);
		break;
	case MC_MUSICROOM:
		command_put(main_choice_top(MC_MUSICROOM), CDG_MAIN_MUSICROOM);
		break;
	case MC_OPTION:
		command_put(main_choice_top(MC_OPTION), CDG_MAIN_OPTION);
		break;
	case MC_QUIT:
		command_put(main_choice_top(MC_QUIT), CDG_QUIT);
		break;
	}
	grcg_off();

	if(col == COL_ACTIVE) {
		cdg_put_8(COMMAND_CURSOR_LEFT_LEFT,  top, CDG_CURSOR_LEFT);
		cdg_put_8(COMMAND_CURSOR_RIGHT_LEFT, top, CDG_CURSOR_RIGHT);
		desc_unput_and_put(desc_id);
	}
}

void pascal near option_unput_and_put(int sel, vc2 col)
{
	int desc_id;
	screen_x_t cursor_left_left = OPTION_CURSOR_LEFT_LEFT;
	int cdg_value; // ACTUAL TYPE: op_cdg_slot_t

	// ZUN bloat: option_choice_top() handles both cases.
	screen_y_t top = (MENU_TOP + (sel * LABEL_H));
	if(sel == OC_QUIT) {
		top = option_choice_top(OC_QUIT);
	}

	egc_copy_rect_1_to_0_16(MENU_OPTION_LEFT, top, MENU_OPTION_W, LABEL_H);
	grcg_setcolor(GC_RMW, col);

	switch(sel) {
	case OC_RANK:
		option_label_put(OC_RANK, CDG_OPTION_LABEL_RANK);
		option_value_put(OC_RANK, (CDG_OPTION_VALUE_RANK + resident->rank));
		desc_id = (6 + resident->rank);
		break;
	case OC_LIVES:
		option_label_put(OC_LIVES, CDG_OPTION_LABEL_LIVES);
		option_value_put(OC_LIVES, (CDG_NUMERAL + resident->cfg_lives));
		desc_id = 10;
		break;
	case OC_BOMBS:
		option_label_put(OC_BOMBS, CDG_OPTION_LABEL_BOMBS);
		option_value_put(OC_BOMBS, (CDG_NUMERAL + resident->cfg_bombs));
		desc_id = 11;
		break;
	case OC_BGM:
		option_label_put(OC_BGM, CDG_OPTION_LABEL_BGM);
		cdg_value = ((resident->bgm_mode == SND_BGM_OFF)
			? CDG_OPTION_VALUE_OFF
			: (CDG_OPTION_VALUE_BGM - SND_BGM_FM26 + resident->bgm_mode)
		);
		option_value_put(OC_BGM, cdg_value);
		desc_id = (12 + resident->bgm_mode);
		break;
	case OC_SE:
		option_label_put(OC_SE, CDG_OPTION_LABEL_SE);
		cdg_value = ((resident->se_mode == SND_SE_OFF)
			? CDG_OPTION_VALUE_OFF
			: (CDG_OPTION_VALUE_SE_FM + SND_SE_FM - resident->se_mode)
		);
		option_value_put(OC_SE, cdg_value);
		desc_id = (15 + resident->se_mode);
		break;
	case OC_TURBO_OR_SLOW:
		command_put(
			option_choice_top(OC_TURBO_OR_SLOW),
			(CDG_OPTION_SLOW - resident->turbo_mode)
		);
		cursor_left_left = COMMAND_CURSOR_LEFT_LEFT;
		desc_id = (18 + resident->turbo_mode);
		break;
	case OC_RESET:
		command_put(option_choice_top(OC_RESET), CDG_OPTION_RESET);
		cursor_left_left = COMMAND_CURSOR_LEFT_LEFT;
		desc_id = 20;
		break;
	case OC_QUIT:
		command_put(option_choice_top(OC_QUIT), CDG_QUIT);
		cursor_left_left = COMMAND_CURSOR_LEFT_LEFT;
		desc_id = 21;
		break;
	}
	grcg_off();

	if(col == COL_ACTIVE) {
		cdg_put_8(cursor_left_left, top, CDG_CURSOR_LEFT);
		if(cursor_left_left == COMMAND_CURSOR_LEFT_LEFT) {
			cdg_put_8(
				(cursor_left_left + (COMMAND_CURSOR_LEFT_RIGHT_DISTANCE)),
				top,
				CDG_CURSOR_RIGHT
			);
		} else {
			cdg_put_8(OPTION_CURSOR_RIGHT_LEFT, top, CDG_CURSOR_RIGHT);
		}
		desc_unput_and_put(desc_id);
	}
}

void pascal near menu_sel_update_and_render(int8_t max, int8_t direction)
{
	menu_unput_and_put(menu_sel, COL_INACTIVE);

	menu_sel += direction;
	if(menu_sel < 0) {
		menu_sel = max;
	}
	if(menu_sel > max) {
		menu_sel = 0;
	}
	if(!extra_unlocked && (menu_sel == MC_EXTRA) && !in_option) {
		menu_sel += direction;
	}

	menu_unput_and_put(menu_sel, COL_ACTIVE);
	snd_se_play_force(1);
}

#define menu_init( \
	initialized, \
	input_allowed, \
	choice_count, \
	unput_and_put, \
	other_left, \
	other_w, \
	other_bottom \
) { \
	input_allowed = false; \
	\
	/* ZUN bloat: Excessively wide and tall. */ \
	egc_copy_rect_1_to_0_16( \
		other_left, MENU_TOP, (other_w + 32), (other_bottom + 24 - MENU_TOP) \
	); \
	\
	for(int i = 0; i < choice_count; i++) { \
		unput_and_put(i, ((menu_sel == i) ? COL_ACTIVE : COL_INACTIVE)); \
	} \
	menu_unput_and_put = unput_and_put; \
	initialized = true; \
	input_allowed = false; /* ZUN bloat: Already done above. */ \
}

inline void return_from_other_screen_to_main(bool& main_initialized, int sel) {
	graph_accesspage(1);
	pi_fullres_load_palette_apply_put_free(0, MENU_MAIN_BG_FN);
	graph_copy_page(0); // switches the accessed page back 0
	palette_100();
	main_initialized = false;
	in_option = false;
	menu_sel = sel;
}

void near main_update_and_render(void)
{
	static bool initialized = false;
	static bool input_allowed;

	if(!initialized) {
		main_menu_unused_1 = 0;

		// ZUN bloat: Way too wide.
		menu_init(
			initialized,
			input_allowed,
			MC_COUNT,
			main_unput_and_put,
			(MENU_OPTION_LEFT - 32),
			(MENU_OPTION_W + 64),
			option_choice_top(OC_COUNT)
		);
	}

	if(!key_det) {
		input_allowed = true;
	}
	if(!input_allowed) {
		return;
	}
	menu_update_vertical(MC_COUNT);

	if((key_det & INPUT_OK) || (key_det & INPUT_SHOT)) {
		snd_se_play_force(11);
		switch(menu_sel) {
		case MC_GAME:
			start_game();
			return_from_other_screen_to_main(initialized, MC_GAME);
			return;
		case MC_EXTRA:
			start_extra();
			return_from_other_screen_to_main(initialized, MC_EXTRA);
			return;
		case MC_REGIST_VIEW:
			regist_view_menu();
			initialized = false;
			break;
		case MC_MUSICROOM:
			musicroom_menu();
			main_cdg_load();

			// ZUN quirk: Moving to MC_GAME in TH04?
			return_from_other_screen_to_main(
				initialized, ((GAME == 5) ? MC_MUSICROOM : MC_GAME)
			);
			return;
		case MC_OPTION:
			initialized = false;
			in_option = true;
			menu_sel = OC_RANK;
			break;
		case MC_QUIT:
			initialized = false; // We're quitting anyway...
			quit = true;
			break;
		}
	}
	if(key_det & INPUT_CANCEL) {
		quit = true;
	}
	if(key_det) {
		input_allowed = false;
	}
}

#define snd_redetermine_modes_and_reload_se() { \
	snd_determine_modes(resident->bgm_mode, resident->se_mode); \
	snd_load(SE_FN, SND_LOAD_SE); \
}

inline void snd_redetermine_modes_and_restart_bgm(bool also_reload_se) {
	snd_kaja_func(KAJA_SONG_STOP, 0);
	#if (GAME == 5)
		if(also_reload_se) {
			snd_redetermine_modes_and_reload_se();
		} else {
			snd_determine_modes(resident->bgm_mode, resident->se_mode);
		}
	#else
		snd_determine_modes(resident->bgm_mode, resident->se_mode);
	#endif
	snd_load(BGM_MENU_MAIN_FN, SND_LOAD_SONG);
	snd_kaja_func(KAJA_SONG_PLAY, 0);
}

inline void return_from_option_to_main(bool& option_initialized) {
	option_initialized = false;
	menu_sel = MC_OPTION;
	in_option = false;
}

void near option_update_and_render(void)
{
	static bool initialized = false;
	static bool input_allowed;

	if(!initialized) {
		// ZUN landmine: [COMMAND_LEFT] doesn't include the cursor. But then
		// again, it doesn't matter as the horizontal area unblitted by
		// option_unput_and_put() is larger in this menu anyway.
		menu_init(
			initialized,
			input_allowed,
			8,
			option_unput_and_put,
			COMMAND_LEFT,
			MENU_MAIN_W,
			main_choice_top(MC_COUNT)
		);
	}

	if(!key_det) {
		input_allowed = true;
	}
	if(!input_allowed) {
		return;
	}
	menu_update_vertical(OC_COUNT);

	if((key_det & INPUT_OK) || (key_det & INPUT_SHOT)) {
		switch(menu_sel) {
		case OC_RESET:
			resident->rank = RANK_NORMAL;
			resident->cfg_lives = CFG_LIVES_DEFAULT;
			resident->cfg_bombs = CFG_BOMBS_DEFAULT;
			resident->bgm_mode = SND_BGM_FM86;
			resident->se_mode = SND_SE_FM;
			resident->turbo_mode = true;
			snd_redetermine_modes_and_restart_bgm(true);
			initialized = false;
			break;
		case OC_QUIT:
			snd_se_play_force(11);
			return_from_option_to_main(initialized);
			break;
		default:
			goto right;
		}
	}

	// ZUN bloat: Could have been deduplicated.
	if(key_det & INPUT_RIGHT) {
	right:
		switch(menu_sel) {
		case OC_RANK:
			ring_inc_range(resident->rank, RANK_EASY, RANK_LUNATIC);
			break;
		case OC_LIVES:
			ring_inc_range(resident->cfg_lives, 1, CFG_LIVES_MAX);
			break;
		case OC_BOMBS:
			ring_inc_range(resident->cfg_bombs, 0, CFG_BOMBS_MAX);
			break;
		case OC_BGM:
			ring_inc_ge_range(resident->bgm_mode, SND_BGM_OFF, SND_BGM_FM86);
			snd_redetermine_modes_and_restart_bgm(false);
			break;
		case OC_SE:
			// ZUN bloat: Come on...
			if(resident->se_mode == SND_SE_OFF) {
				resident->se_mode = SND_SE_BEEP;
			} else {
				resident->se_mode--;
			}

			// ZUN bug: TH04 does not immediately apply SE mode changes.
			// (Same below for INPUT_LEFT.)
			#if (GAME == 5)
				snd_redetermine_modes_and_reload_se();
			#endif
			break;
		case OC_TURBO_OR_SLOW:
			resident->turbo_mode = (1 - resident->turbo_mode);
			break;
		}
		option_unput_and_put(menu_sel, COL_ACTIVE);
	}
	if(key_det & INPUT_LEFT) {
		switch(menu_sel) {
		case OC_RANK:
			ring_dec_range(resident->rank, RANK_EASY, RANK_LUNATIC);
			break;
		case OC_LIVES:
			ring_dec_range(resident->cfg_lives, 1, CFG_LIVES_MAX);
			break;
		case OC_BOMBS:
			ring_dec_range(resident->cfg_bombs, 0, CFG_BOMBS_MAX);
			break;
		case OC_BGM:
			// ZUN bloat: Come on...
			if(resident->bgm_mode == SND_BGM_OFF) {
				resident->bgm_mode = SND_BGM_FM86;
			} else {
				resident->bgm_mode--;
			}
			snd_redetermine_modes_and_restart_bgm(false);
			break;
		case OC_SE:
			ring_inc_ge_range(resident->se_mode, SND_SE_OFF, SND_SE_BEEP);
			#if (GAME == 5)
				snd_redetermine_modes_and_reload_se();
			#endif
			break;
		case OC_TURBO_OR_SLOW:
			resident->turbo_mode = (1 - resident->turbo_mode);
			break;
		}
		option_unput_and_put(menu_sel, COL_ACTIVE);
	}

	if(key_det & INPUT_CANCEL) {
		return_from_option_to_main(initialized);
	}
	if(key_det) {
		input_allowed = false;
	}
}

void main(void)
{
	int idle_frames = 0;

	text_clear();
	respal_create(); // ZUN bloat: These games don't use resident palettes.
	mem_assign_paras = MEM_ASSIGN_PARAS_OP;
	if(game_init_op(OP_AND_END_PF_FN)) {
		dos_puts2(MEMORY_INSUFFICIENT);
		getch();
	}

	#if (GAME == 4)
		gaiji_backup();
		gaiji_entry_bfnt(GAIJI_FN);
	#endif

	cfg_load();
	if(resident->rank == RANK_SHOW_SETUP_MENU) {
		setup_menu();
		resident->rank = RANK_NORMAL;
	}
	snd_redetermine_modes_and_reload_se();

	if(!resident->zunsoft_shown) {
		zunsoft_animate();
		resident->zunsoft_shown = true;
	}

	if((GAME == 5) && resident->demo_num == 5) {
		resident->demo_num = 0;
	}
	if(resident->demo_num == 0) {
		snd_kaja_func(KAJA_SONG_STOP, 0);
	}
	op_animate();

	#if (GAME == 5)
		main_cdg_load();
		cleardata_and_regist_view_sprites_load();
	#else
		cleardata_and_regist_view_sprites_load();
		main_cdg_load();
	#endif
	in_option = false;
	quit = false;
	menu_sel = 0;
	while(!quit) {
		input_reset_sense_interface();
		switch(in_option) {
		case false:
			main_update_and_render();
			if(idle_frames >= 640) {
				start_demo();
				#if (GAME == 5)
					// ZUN bloat: Execution never gets here.
					idle_frames = 0;
				#endif
			}
			break;

		case true:
			option_update_and_render();
			break;
		}

		if(
			!key_det ||

			// Holding Left+Right triggers the hidden Extra Stage replay in
			// start_demo(). Don't reset [idle_frames] for that specific input,
			// as that function would otherwise never be called.
			((GAME == 5) && (key_det == (INPUT_LEFT | INPUT_RIGHT)))
		) {
			idle_frames++;
		} else {
			idle_frames = 0;
		}

		resident->rand++;
		frame_delay(1);
	}
	main_cdg_free();
	cfg_save_exit();
	#if (GAME == 4)
		gaiji_restore();
	#endif
	text_clear();
	game_exit_to_dos();
	respal_free(); // ZUN bloat: These games don't use resident palettes.
}

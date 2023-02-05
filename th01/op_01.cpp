/* ReC98
 * -----
 * Code segment #1 of TH01's OP.EXE
 */

#include <mem.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "pc98kbd.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "game/input.hpp"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/math/clamp.hpp"
#include "th01/core/initexit.hpp"
#include "th01/core/resstuff.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/grp_text.hpp"
#include "th01/hardware/input.hpp"
#include "th01/hardware/palette.h"
#include "th01/formats/cfg.hpp"
#include "th01/formats/grp.h"
#include "th01/snd/mdrv2.h"
#include "th01/shiftjis/debug.hpp"
#include "th01/shiftjis/fns.hpp"
#include "th01/shiftjis/op.hpp"

// Redundant copies of resident structure fields to static data
// ------------------------------------------------------------

unsigned long frame_rand;
// ------------------------------------------------------------

// Unused. The only thing on the main menu with this color is the "1996 ZUN"
// text at the bottom... probably part of an effect that we never got to see.
void snap_col_4(void)
{
	static dots8_t* columns[ROW_SIZE];
	register vram_x_t x;
	register screen_y_t y;
	vram_offset_t vram_offset;

	for(x = 0; x < ROW_SIZE; x++) {
		columns[x] = new dots8_t[RES_Y];
	}
	grcg_setcolor_tcr(4);
	graph_accesspage_func(1);

	for(x = 0; x < ROW_SIZE; x++) {
		y = 0;
		vram_offset = x;
		while(y < RES_Y) {
			columns[x][y] = VRAM_CHUNK(B, vram_offset, 8);
			y++;
			vram_offset += ROW_SIZE;
		}
	}

	grcg_off();
	graph_accesspage_func(0);
}

/// REIIDEN.CFG loading and saving
/// ------------------------------

cfg_options_t opts = {
	CFG_RANK_DEFAULT,
	CFG_BGM_MODE_DEFAULT,
	CFG_CREDIT_BOMBS_DEFAULT,
	CFG_CREDIT_LIVES_EXTRA_DEFAULT
};
int8_t debug_mode = 0;

void cfg_load(void)
{
	cfg_t cfg_in;
	bool read_failure = false;
	FILE* fp;

	if(( fp = fopen(CFG_FN, "rb") ) == nullptr) {
use_defaults:
		read_failure = true;
	}
	if(!read_failure) {
		fread(&cfg_in, 1, sizeof(cfg_in), fp);
		if(memcmp(cfg_in.id, CFG_ID, sizeof(cfg_in.id))) {
			fclose(fp);
			goto use_defaults;
		}
		opts.rank = cfg_in.opts.rank;
		opts.bgm_mode = cfg_in.opts.bgm_mode;
		opts.credit_bombs = cfg_in.opts.credit_bombs;
		opts.credit_lives_extra = cfg_in.opts.credit_lives_extra;
		fclose(fp);
	} else {
		opts.rank = CFG_RANK_DEFAULT;
		opts.bgm_mode = CFG_BGM_MODE_DEFAULT;
		opts.credit_bombs = CFG_CREDIT_BOMBS_DEFAULT;
		opts.credit_lives_extra = CFG_CREDIT_LIVES_EXTRA_DEFAULT;
	}
}

void cfg_save(void)
{
	bool write_failure = false;
	FILE* fp;

	if(( fp = fopen(CFG_FN, "wb") ) == nullptr) {
		write_failure = true;
	}
	if(!write_failure) {
		fputs(CFG_ID, fp);
		fputc(opts.rank, fp);
		fputc(opts.bgm_mode, fp);
		fputc(opts.credit_bombs, fp);
		fputc(opts.credit_lives_extra, fp);
		fclose(fp);
	}
}
/// ------------------------------

/// Input
/// -----

enum menu_id_t {
	MID_MAIN,
	MID_OPTION,
	MID_MUSIC,
	MID_UPDATE_BGM_MODE__DELAY__SWITCH_TO_MAIN,
	MID_DELAY__SWITCH_TO_OPTION,
};

static const int MAIN_CHOICE_COUNT = 4;
static const int OPTION_CHOICE_COUNT = 5;
static const int MUSIC_CHOICE_COUNT = 2;

#undef RING_INC
#undef RING_DEC

#define RING_INC(val, ring_end) \
	(val) += 1; \
	if((val) > (ring_end)) { \
		(val) = 0; \
	}

#define RING_DEC(val, ring_end) \
	(val) -= 1; \
	if((val) < 0) { \
		(val) = ring_end; \
	}

#define input_update_bool(var, cur_sensed) \
	if(cur_sensed) input_func_bool(var)

#define input_onchange_ring(prev_slot, cur_sensed, ring_func) \
	if(cur_sensed) { \
		if(!input_prev[prev_slot]) { \
			ring_func; \
			input_prev[prev_slot] = true; \
		} \
	} else { \
		input_prev[prev_slot] = false; \
	}

int8_t menu_sel = 0;
int8_t input_left = false; // ACTUAL TYPE: bool
bool input_ok = false;
bool input_shot = false;
bool input_cancel = false;

int8_t menu_id = MID_MAIN; // ACTUAL TYPE: menu_id_t

int8_t input_right = false; // ACTUAL TYPE: bool
bool quit = false;
int8_t unused_con_arg_0 = 0;
int8_t unused_con_arg_2 = 0;

// ZUN bloat: Just call resident_free() in the one case it's actually needed.
int8_t free_resident_structure_on_title_exit = false; // ACTUAL TYPE: bool

int32_t unused_con_arg_1 = 0;

inline void keygroup_sense(REGS& out, REGS& in, char group_id) {
	in.h.ah = 0x04;
	in.h.al = group_id;
	int86(0x18, &in, &out);
}

inline void ok_shot_cancel_sense(REGS& out, REGS& in) {
	keygroup_sense(out, in, 3);
	input_update_bool(input_ok, (out.h.ah & K3_RETURN));

	keygroup_sense(out, in, 5);
	input_update_bool(input_shot, (out.h.ah & K5_Z));

	keygroup_sense(out, in, 0);
	input_update_bool(input_cancel, (out.h.ah & K0_ESC));
}

void main_input_sense(void)
{
	REGS in;
	REGS out1, out2;
	static bool16 input_prev[2] = { false };

	keygroup_sense(out1, in, 7);
	keygroup_sense(out2, in, 8);

	input_onchange_ring(0,
		(out1.h.ah & K7_ARROW_UP) || (out2.h.ah & K8_NUM_8),
		RING_DEC(menu_sel, (MAIN_CHOICE_COUNT - 1))
	);

	keygroup_sense(out2, in, 9);

	input_onchange_ring(1,
		(out1.h.ah & K7_ARROW_DOWN) || (out2.h.ah & K9_NUM_2),
		RING_INC(menu_sel, (MAIN_CHOICE_COUNT - 1))
	);

	ok_shot_cancel_sense(out1, in);
}

uint8_t option_choice_max = 3;

void option_input_sense(void)
{
	REGS in;
	REGS out1, out2;
	static bool16 input_prev[2] = { false };

	keygroup_sense(out1, in, 7);
	keygroup_sense(out2, in, 8);

	input_onchange_ring(0,
		(out1.h.ah & K7_ARROW_UP) || (out2.h.ah & K8_NUM_8),
		RING_DEC(menu_sel, option_choice_max)
	);
	input_update_bool(
		input_left, (out1.h.ah & K7_ARROW_LEFT) || (out2.h.ah & K8_NUM_4)
	);

	keygroup_sense(out2, in, 9);

	input_onchange_ring(1,
		(out1.h.ah & K7_ARROW_DOWN) || (out2.h.ah & K9_NUM_2),
		RING_INC(menu_sel, option_choice_max)
	);
	input_update_bool(
		input_right, (out1.h.ah & K7_ARROW_RIGHT) || (out2.h.ah & K9_NUM_6)
	);

	ok_shot_cancel_sense(out1, in);
}
/// -----

void whiteline_put(screen_y_t y)
{
	vram_offset_t vram_offset = vram_offset_shift(0, y);
	vram_dword_amount_t x;

	grcg_setcolor_rmw(15);
	x = 0;
	while(x < (ROW_SIZE / sizeof(dots32_t))) {
		grcg_put(vram_offset, 0xFFFFFFFF, 32);
		x++;
		vram_offset += static_cast<vram_offset_t>(sizeof(dots32_t));
	}
	grcg_off();
}

void whitelines_animate(void)
{
	unsigned int i = 0;
	screen_y_t y1 = 0;
	screen_y_t y2 = 0;
	bool drawn_at[RES_Y] = { false };

	while(i++ < (RES_Y / 4)) {
		egc_copy_rect_1_to_0_16(0, y1, RES_X, 1);
		egc_copy_rect_1_to_0_16(0, y2, RES_X, 1);

		do {
			y1 = (rand() % RES_Y);
		} while(drawn_at[y1]);
		drawn_at[y1] = true;

		do {
			y2 = (rand() % RES_Y);
		} while(drawn_at[y2]);
		drawn_at[y2] = true;

		whiteline_put(y1);
		whiteline_put(y2);
		frame_delay(1);
	}
	graph_accesspage_func(1);
	graph_copy_accessed_page_to_other();
	graph_accesspage_func(0);
}

void title_init(void)
{
	mdrv2_bgm_load("reimu.mdt");
	mdrv2_bgm_play();
	graph_accesspage_func(1);
	grp_put_palette_show("REIIDEN2.grp");
	z_palette_black();
	graph_copy_accessed_page_to_other();
	grp_put("REIIDEN3.grp");
	graph_accesspage_func(0);
	z_palette_black_in();
	frame_delay(100);

	whitelines_animate();
}

void title_window_put(void)
{
	graph_accesspage_func(1);
	graph_copy_accessed_page_to_other();
	graph_accesspage_func(0);
	grp_put_colorkey("op_win.grp");
	graph_copy_accessed_page_to_other();
}

void title_exit(void)
{
	if(free_resident_structure_on_title_exit == true) {
		resident_free();
	}
	key_end();
}

// Starting the game
// -----------------

static const pellet_speed_t PELLET_SPEED_DEFAULT = to_pellet_speed(-0.1);

void start_game(void)
{
	cfg_save();
	resident_create_and_stuff_set(
		opts.rank,
		opts.bgm_mode,
		opts.credit_bombs,
		opts.credit_lives_extra,
		frame_rand
	);
	title_exit();
	mdrv2_bgm_fade_out_nonblock();
	game_switch_binary();

	if(debug_mode == 2) {
		resident->debug_mode = DM_TEST;
	} else if(debug_mode == 3) {
		resident->debug_mode = DM_FULL;
	} else if(debug_mode == 0) {
		resident->debug_mode = DM_OFF;
	}

	resident->route = ROUTE_MAKAI;
	resident->stage_id = 0;
	resident->rem_lives = (opts.credit_lives_extra + 2);
	resident->point_value = 0;

	for(int i = 0; i < SCENE_COUNT; i++) {
		resident->continues_per_scene[i] = 0;
		resident->bonus_per_stage[i] = 0;
	}

	resident->score_highest = 0;
	resident->continues_total = 0;
	resident->end_flag = ES_NONE;
	resident->unused_1 = 0;
	resident->snd_need_init = true;
	resident->pellet_speed = PELLET_SPEED_DEFAULT;

	execl(BINARY_MAIN, BINARY_MAIN, nullptr);
}

void start_continue(void)
{
	cfg_save();
	resident_create_and_stuff_set(
		opts.rank,
		opts.bgm_mode,
		opts.credit_bombs,
		opts.credit_lives_extra,
		frame_rand
	);

	if(resident->stage_id == 0) {
		_ES = FP_SEG(cfg_load); // ZUN bloat: Yes, no point to this at all
	}

	title_exit();
	mdrv2_bgm_fade_out_nonblock();
	game_switch_binary();

	resident->debug_mode = DM_OFF;
	resident->snd_need_init = true;
	resident->rem_lives = (opts.credit_lives_extra + 2);
	resident->unused_1 = 0;
	resident->pellet_speed = PELLET_SPEED_DEFAULT;
	resident->point_value = 0;

	execl(CFG_ID, CFG_ID, nullptr);
}
// -----------------

/// Main menu
/// ---------
/// Terminology: "Choice" = Top-level menu selection (not amount of values)

static const uint4_t COL_ACTIVE = 15;
static const uint4_t COL_INACTIVE = 5;
static const int16_t FX = FX_WEIGHT_BLACK;

// Coordinates
// -----------

static const screen_x_t MENU_LEFT = 220;
static const screen_x_t MENU_CENTER_X = 316;
static const screen_y_t MENU_CENTER_Y = 316;
static const pixel_t MENU_W = 176;

static const pixel_t CHOICE_PADDED_H = 20;
static const int CHOICE_COUNT_MAX = 5;

static const int TRACK_COUNT = 15;

// ZUN bloat: Needed to circumvent 16-bit promotion in a single comparison.
inline int8_t track_count(void) {
	return TRACK_COUNT;
}

#define choice_top_0(choice_count) ( \
	(MENU_CENTER_Y - (((choice_count) * CHOICE_PADDED_H) / 2)) \
)

#define choice_top(choice, choice_count) ( \
	(choice_top_0(choice_count) + (choice * CHOICE_PADDED_H)) \
)

#define music_choice_top(choice, choice_count) ( \
	(choice_top_0(choice_count + 1) + (choice * (CHOICE_PADDED_H * 2))) \
)
// -----------

inline void menu_unput(int choice_count) {
	egc_copy_rect_1_to_0_16(
		MENU_LEFT,
		choice_top_0(choice_count),
		MENU_W,
		(choice_count * CHOICE_PADDED_H)
	);
}

#define choice_put(left, top, col, str) { \
	graph_printf_fx(left, top, (col | FX), "%s", str); \
}

#define choice_put_value(left, top, col, str, val) { \
	graph_printf_fx(left, top, (col | FX), "%s%s", str, val); \
}

#define choice_render_if_changed(prev, cur, unput_and_put_func) { \
	if(cur != prev) { \
		unput_and_put_func(prev, COL_INACTIVE); \
		unput_and_put_func(cur, COL_ACTIVE); \
		prev = cur; \
	} \
}

void title_hit_key_put(int frame)
{
	enum {
		LEFT = (((RES_X / 2) - GLYPH_FULL_W) - (shiftjis_w(HIT_KEY) / 2)),
		TOP = choice_top(0, 1),
	};
	if((frame % 70) < 50) {
		graph_putsa_fx(LEFT, TOP, (FX_WEIGHT_BOLD | COL_ACTIVE), HIT_KEY);
	} else {
		egc_copy_rect_1_to_0_16_word_w(LEFT, TOP, shiftjis_w(HIT_KEY), GLYPH_H);
	}
}

void main_choice_unput_and_put(int choice, int col)
{
	const shiftjis_t* CHOICES[MAIN_CHOICE_COUNT] = MAIN_CHOICES;

	screen_x_t left = (MENU_CENTER_X - (MAIN_CHOICE_W / 2));
	screen_y_t top = choice_top(choice, MAIN_CHOICE_COUNT);

	// No unblitting necessary here, as only the colors change.
	graph_putsa_fx(left, top, (col | FX), CHOICES[choice]);
}

void option_choice_unput_and_put(int choice, int col)
{
	const shiftjis_t* CHOICES[OPTION_CHOICE_COUNT] = OPTION_CHOICES;
	const shiftjis_t* RANKS[RANK_COUNT] = RANKS_CAPS_CENTERED;
	const shiftjis_t* MUSIC_MODES[BGM_MODE_COUNT] = BGM_MODES_CENTERED;
	const shiftjis_t* START_LIVES[CFG_CREDIT_LIVES_EXTRA_MAX] = {
		"   3  ",
		"   4  ",
		"   5  ",
		"   6  ",
		"   7  ",
	};

	screen_x_t left = (MENU_CENTER_X - (MENU_W / 2));
	screen_y_t top = choice_top(choice, OPTION_CHOICE_COUNT);

	egc_copy_rect_1_to_0_16(left, top, MENU_W, GLYPH_H);

	if(choice == 0) {
		choice_put_value(left, top, col, CHOICES[choice], RANKS[opts.rank]);
	} else if(choice == 1) {
		choice_put_value(
			left, top, col, CHOICES[choice], MUSIC_MODES[opts.bgm_mode]
		);
	} else if(choice == 2) {
		choice_put_value(
			left,
			top,
			col,
			CHOICES[choice],
			START_LIVES[opts.credit_lives_extra]
		);
	} else if(choice == 3) {
		choice_put(left, top, col, CHOICES[choice]);
	} else if(choice == 4) {
		choice_put(left, top, col, CHOICES[choice]);
	}
}

int8_t music_sel = 0;

void music_choice_unput_and_put(int choice, int col)
{
	const shiftjis_t* CHOICES[MUSIC_CHOICE_COUNT]  = MUSIC_CHOICES;
	const shiftjis_t* TITLES[TRACK_COUNT]  = MUSIC_TITLES;

	screen_x_t left = (MENU_CENTER_X - (MENU_W / 2));
	screen_y_t top = music_choice_top(choice, MUSIC_CHOICE_COUNT);

	egc_copy_rect_1_to_0_16(left, top, MENU_W, GLYPH_H);

	if(choice == 0) {
		// ZUN bug: That's larger than the menu?
		egc_copy_rect_1_to_0_16(
			left, (top + CHOICE_PADDED_H), (MENU_W + GLYPH_FULL_W), GLYPH_H
		);
		graph_printf_fx(
			left, top, (col | FX), "%s%.2d", CHOICES[choice], music_sel
		);
		choice_put(left, (top + CHOICE_PADDED_H), col, TITLES[music_sel]);
	} else if(choice == 1) {
		choice_put(left, top, col, CHOICES[choice]);
	}
}

void main_update_and_render(void)
{
	static int sel_prev = 99;
	static bool16 in_this_menu = false;

	if(!in_this_menu) {
		menu_unput(CHOICE_COUNT_MAX);
		main_choice_unput_and_put(0, COL_INACTIVE);
		main_choice_unput_and_put(1, COL_INACTIVE);
		main_choice_unput_and_put(2, COL_INACTIVE);
		main_choice_unput_and_put(3, COL_INACTIVE);

		main_choice_unput_and_put(menu_sel, COL_ACTIVE);
		in_this_menu = true;
		sel_prev = menu_sel;
	}
	choice_render_if_changed(sel_prev, menu_sel, main_choice_unput_and_put);

	if(input_ok || input_shot) {
		switch(menu_sel) {
		case 0:
			start_game();
			break;
		case 1:
			start_continue();
			break;
		case 2:
			menu_id = MID_OPTION;
			in_this_menu = false;
			break;
		case 3:
			quit = true;
			break;
		}
	}
	if(input_cancel) {
		quit = true;
	}
}

void option_update_and_render(void)
{
	static bool16 in_this_menu = false;
	static int sel_prev = 0;
	static bool16 left_locked = false;
	static bool16 right_locked = false;

	if(!in_this_menu) {
		menu_sel = 0;
		sel_prev = 0;
		in_this_menu = true;
		option_choice_max = (OPTION_CHOICE_COUNT - 1);

		menu_unput(max_macro(MAIN_CHOICE_COUNT, MUSIC_CHOICE_COUNT));
		option_choice_unput_and_put(0, COL_ACTIVE);

		option_choice_unput_and_put(1, COL_INACTIVE);
		option_choice_unput_and_put(2, COL_INACTIVE);
		option_choice_unput_and_put(3, COL_INACTIVE);
		option_choice_unput_and_put(4, COL_INACTIVE);
	}
	choice_render_if_changed(sel_prev, menu_sel, option_choice_unput_and_put);

	on_condition_if_not_locked_2((input_left == true), left_locked, {
		switch(menu_sel) {
		case 0:
			ring_dec_16(opts.rank, RANK_LUNATIC);
			break;
		case 1:
			ring_dec_16(
				static_cast<int8_t>(opts.bgm_mode), (BGM_MODE_COUNT - 1)
			);
			break;
		case 2:
			ring_dec_16(
				opts.credit_lives_extra, (CFG_CREDIT_LIVES_EXTRA_MAX - 1)
			);
			break;
		}
		option_choice_unput_and_put(menu_sel, COL_ACTIVE);
	});

	on_condition_if_not_locked_2((input_right == true), right_locked, {
		switch(menu_sel) {
		case 0:
			ring_inc(opts.rank, RANK_LUNATIC);
			break;
		case 1:
			ring_inc(static_cast<int8_t>(opts.bgm_mode), (BGM_MODE_COUNT - 1));
			break;
		case 2:
			ring_inc(opts.credit_lives_extra, (CFG_CREDIT_LIVES_EXTRA_MAX - 1));
			break;
		}
		option_choice_unput_and_put(menu_sel, COL_ACTIVE);
	});

	if(((input_ok || input_shot) && (menu_sel == 4)) || input_cancel) {
		menu_id = MID_UPDATE_BGM_MODE__DELAY__SWITCH_TO_MAIN;
		in_this_menu = false;
		menu_sel = 2; // Option in the main menu
	}
	if((input_ok || input_shot) && (menu_sel == 3)) {
		menu_id = MID_MUSIC;
		in_this_menu = false;
		menu_sel = 0; // Track selection in the Music Test
	}
}

void music_play_selected(void)
{
	const char* FILES[TRACK_COUNT] = MUSIC_FILES;
	mdrv2_bgm_stop();
	mdrv2_bgm_load(FILES[music_sel]);
	mdrv2_bgm_play();
}

void music_update_and_render(void)
{
	static bool16 in_this_menu = false;
	static int sel_prev = 0;
	static bool16 left_locked = false;
	static bool16 right_locked = false;

	if(!in_this_menu) {
		menu_sel = 0;
		sel_prev = 0;
		in_this_menu = true;

		// This is not a functional way of locking these keys...
		input_ok = false;
		input_shot = false;

		option_choice_max = (MUSIC_CHOICE_COUNT - 1);

		menu_unput(CHOICE_COUNT_MAX);
		music_choice_unput_and_put(0, COL_ACTIVE);
		music_choice_unput_and_put(1, COL_INACTIVE);
	}
	choice_render_if_changed(sel_prev, menu_sel, music_choice_unput_and_put);

	on_condition_if_not_locked_2((input_left == true), left_locked, {
		if(menu_sel == 0) {
			ring_dec(music_sel, (TRACK_COUNT - 1));
		}
		music_choice_unput_and_put(menu_sel, COL_ACTIVE);
	});

	on_condition_if_not_locked_2((input_right == true), right_locked, {
		if(menu_sel == 0) {
			ring_inc_ge(music_sel, track_count());
		}
		music_choice_unput_and_put(menu_sel, COL_ACTIVE);
	});

	if(((input_ok || input_shot) && (menu_sel == 1)) || input_cancel) {
		menu_id = MID_DELAY__SWITCH_TO_OPTION;
		in_this_menu = false;
		menu_sel = 3; // Music Test in the option menu
	}
	if((input_ok || input_shot) && (menu_sel == 0)) {
		music_play_selected();
	}
}

void main(int argc, const char *argv[])
{
	int bgm_mode_cur = 0;
	int hit_key_frames = 0;
	const char* arg2; // ZUN bloat
	const char* arg4; // ZUN bloat
	uint8_t bios_flag;
	seg_t kb_buf_head;
	REGS in;
	REGS out;

	if(!mdrv2_resident()) {
		printf(ERROR_RESIDENT_INVALID);
		return;
	}

	unused_con_arg_0 = 0;
	unused_con_arg_1 = 0;
	unused_con_arg_2 = 0;

	if(argc > 1) {
		if(argv[1][0] == 's') {
			// Probably supposed to just show the stage selection screen
			// without any other debugging features, but start_game() ignores
			// this value.
			debug_mode = 1;
		}
		if(argv[1][0] == 't') {
			debug_mode = 2;
		}
		if(argv[1][0] == 'd') {
			debug_mode = 3;
		}

		// ZUN bug: The string could theoretically be less than 3 characters
		// long.
		if(memcmp(argv[1], "CON", 3) == 0) {
			arg2 = argv[2];
			unused_con_arg_0 = atol(arg2);
			unused_con_arg_1 = atol(argv[3]);
			arg4 = argv[4];
			unused_con_arg_2 = atol(arg4);
		}
	}

	// ZUN bug: Should be done conditionally based on resident_t::bgm_mode.
	// This is why you still get music during this binary despite disabling BGM
	// in the options.
	mdrv2_enable_if_board_installed();
	game_init();
	cfg_load();

	bgm_mode_cur = opts.bgm_mode;

	// Initialize the PC-98 keyboard interface and clear the key buffer.
	in.h.ah = 0x03;
	int86(0x18, &in, &out);

	key_start();

	title_init();

	// Set the BIOS_FLAG to not beep when the keyboard buffer overflows, as
	// we're clearing and setting its length to 0 below… I guess?
	pokeb(0, 0x0500 /* BIOS_FLAG */, (peekb(0, 0x0500 /* BIOS_FLAG */) | 0x20));

	while(!key_sense_bios()) {
		frame_delay(1);
		title_hit_key_put(hit_key_frames);
		hit_key_frames++;
	}

	title_window_put();

	// Since [frame_rand] is always 0 here, the white line animation always
	// looks identical.
	srand(frame_rand);

	while(!quit) {
		if(menu_id == MID_MAIN) {
			main_input_sense();
			main_update_and_render();
		} else if(menu_id == MID_OPTION) {
			option_input_sense();
			option_update_and_render();
		} else if(menu_id == MID_MUSIC) {
			option_input_sense();
			music_update_and_render();
		} else if(menu_id == MID_UPDATE_BGM_MODE__DELAY__SWITCH_TO_MAIN) {
			if(opts.bgm_mode != bgm_mode_cur) {
				if(opts.bgm_mode == BGM_MODE_OFF) {
					mdrv2_bgm_stop();
				} else if(static_cast<int>(opts.bgm_mode) == BGM_MODE_MDRV2) {
					mdrv2_bgm_stop();
					mdrv2_bgm_load("reimu.mdt");
					mdrv2_bgm_play();
				}
				bgm_mode_cur = opts.bgm_mode;
			}

			// ZUN quirk: These delays are only here to prevent this menu from
			// being immediately entered again if the OK or Shot key isn't
			// immediately released on the next frame. This would need a
			// cross-menu locking approach to be solved properly.
			frame_delay(15);
			menu_id = MID_MAIN;
		} else if(menu_id == MID_DELAY__SWITCH_TO_OPTION) {
			// ZUN quirk: Same here.
			frame_delay(15);
			menu_id = MID_OPTION;
		}

		// Clear the PC-98 BIOS keyboard buffer… yeah, this is not a proper
		// way to handle cross-menu locking either.
		poke(0, 0x0526 /* KB_BUF_TAIL */, peek(0, 0x0524) /* KB_BUF_HEAD */);
		pokeb(0, 0x0528 /* KB_COUNT */, 0);

		frame_rand++;
		frame_delay(1);
	}
	cfg_save();
	free_resident_structure_on_title_exit = true;
	mdrv2_bgm_stop();
	title_exit();

	graph_accesspage_func(1);	z_graph_clear();
	graph_accesspage_func(0);	z_graph_clear();

	game_exit();
	mdrv2_bgm_stop();
	printf(GOODBYE);
}
/// ---------

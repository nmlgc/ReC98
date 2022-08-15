/* ReC98
 * -----
 * Code segment #1 of TH01's OP.EXE
 */

#include <mem.h>
#include <process.h>
#include <stdio.h>
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
#include "th01/hardware/grppsafx.h"
#include "th01/hardware/input.hpp"
#include "th01/hardware/palette.h"
#include "th01/formats/cfg.hpp"
#include "th01/formats/grp.h"
#include "th01/snd/mdrv2.h"
#include "th01/shiftjis/op.hpp"

extern long rand;

extern const char aReimu_mdt[];

// Unused. The only thing on the main menu with this color is the "1996 ZUN"
// text at the bottom... probably part of an effect that we never got to see.
void snap_col_4(void)
{
	extern dots8_t* columns[ROW_SIZE];
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
			columns[x][y] = VRAM_PLANE_B[vram_offset];
			y++;
			vram_offset += ROW_SIZE;
		}
	}

	grcg_off();
	graph_accesspage_func(0);
}

/// REIIDEN.CFG loading and saving
/// ------------------------------

extern cfg_options_t opts;
extern int8_t debug_mode;
// These will be removed once the strings can be defined here
#undef CFG_FN
#undef CFG_ID
extern char CFG_FN[], CFG_ID[], FOPEN_RB[], FOPEN_WB[];

void cfg_load(void)
{
	cfg_t cfg_in;
	bool read_failure = false;
	FILE* fp;

	if(( fp = fopen(CFG_FN, FOPEN_RB) ) == nullptr) {
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
		opts.bombs = cfg_in.opts.bombs;
		opts.lives_extra = cfg_in.opts.lives_extra;
		fclose(fp);
	} else {
		opts.rank = CFG_RANK_DEFAULT;
		opts.bgm_mode = CFG_BGM_MODE_DEFAULT;
		opts.bombs = CFG_BOMBS_DEFAULT;
		opts.lives_extra = CFG_LIVES_EXTRA_DEFAULT;
	}
}

void cfg_save(void)
{
	bool write_failure = false;
	FILE* fp;

	if(( fp = fopen(CFG_FN, FOPEN_WB) ) == nullptr) {
		write_failure = true;
	}
	if(!write_failure) {
		fputs(CFG_ID, fp);
		fputc(opts.rank, fp);
		fputc(opts.bgm_mode, fp);
		fputc(opts.bombs, fp);
		fputc(opts.lives_extra, fp);
		fclose(fp);
	}
}
/// ------------------------------

/// Input
/// -----

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

extern int8_t menu_sel;
extern int8_t input_left; // ACTUAL TYPE: bool
extern bool input_cancel;

extern enum {
	MID_MAIN,
	MID_OPTION,
	MID_MUSIC,
	MID_UPDATE_BGM_MODE__DELAY__SWITCH_TO_MAIN,
} menu_id;

extern int8_t input_right; // ACTUAL TYPE: bool
extern bool quit;

// ZUN bloat: Just call resident_free() in the one case it's actually needed.
extern int8_t free_resident_structure_on_title_exit; // ACTUAL TYPE: bool

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
	// TODO: Should just be `static` once the variable can be declared here
	#define input_prev main_input_prev
	extern bool16 input_prev[2];

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

extern uint8_t option_choice_max;

void option_input_sense(void)
{
	REGS in;
	REGS out1, out2;
	// TODO: Should just be `static` once the variable can be declared here
	#undef  input_prev
	#define input_prev option_input_prev
	extern bool16 input_prev[2];

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
	struct hack {
		bool y[RES_Y];
	};
	extern const hack WHITELINES_DRAWN_AT;

	unsigned int i = 0;
	screen_y_t y1 = 0;
	screen_y_t y2 = 0;
	hack drawn_at = WHITELINES_DRAWN_AT;
	while(i++ < (RES_Y / 4)) {
		egc_copy_rect_1_to_0_16(0, y1, RES_X, 1);
		egc_copy_rect_1_to_0_16(0, y2, RES_X, 1);

		do {
			y1 = (rand() % RES_Y);
		} while(drawn_at.y[y1]);
		drawn_at.y[y1] = true;

		do {
			y2 = (rand() % RES_Y);
		} while(drawn_at.y[y2]);
		drawn_at.y[y2] = true;

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
	extern const char aReiiden2_grp[];
	extern const char aReiiden3_grp[];

	mdrv2_bgm_load(aReimu_mdt);
	mdrv2_bgm_play();
	graph_accesspage_func(1);
	grp_put_palette_show(aReiiden2_grp);
	z_palette_black();
	graph_copy_accessed_page_to_other();
	grp_put(aReiiden3_grp);
	graph_accesspage_func(0);
	z_palette_black_in();
	frame_delay(100);

	whitelines_animate();
}

void title_window_put(void)
{
	extern const char aOp_win_grp[];

	graph_accesspage_func(1);
	graph_copy_accessed_page_to_other();
	graph_accesspage_func(0);
	grp_put_colorkey(aOp_win_grp);
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
	extern char aReiiden_0[];

	cfg_save();
	resident_create_and_stuff_set(
		opts.rank, opts.bgm_mode, opts.bombs, opts.lives_extra, rand
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
	resident->rem_lives = (opts.lives_extra + 2);
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

	execl(aReiiden_0, aReiiden_0, nullptr);
}

void start_continue(void)
{
	cfg_save();
	resident_create_and_stuff_set(
		opts.rank, opts.bgm_mode, opts.bombs, opts.lives_extra, rand
	);

	if(resident->stage_id == 0) {
		_ES = FP_SEG(cfg_load); // ZUN bloat: Yes, no point to this at all
	}

	title_exit();
	mdrv2_bgm_fade_out_nonblock();
	game_switch_binary();

	resident->debug_mode = DM_OFF;
	resident->snd_need_init = true;
	resident->rem_lives = (opts.lives_extra + 2);
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

extern const shiftjis_t aSS[];

#define choice_put(left, top, col, str) { \
	graph_printf_fx(left, top, (col | FX), (aSS + 2), str); \
}

#define choice_put_value(left, top, col, str, val) { \
	graph_printf_fx(left, top, (col | FX), aSS, str, val); \
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
	extern const shiftjis_t GP_HIT_KEY[];

	if((frame % 70) < 50) {
		graph_putsa_fx(LEFT, TOP, (FX_WEIGHT_BOLD | COL_ACTIVE), GP_HIT_KEY);
	} else {
		egc_copy_rect_1_to_0_16_word_w(LEFT, TOP, shiftjis_w(HIT_KEY), GLYPH_H);
	}
}

template <int Count> struct TextArray {
	const shiftjis_t* t[Count];
};

void main_choice_unput_and_put(int choice, int col)
{
	extern TextArray<MAIN_CHOICE_COUNT> MAIN_CHOICES;
	const TextArray<MAIN_CHOICE_COUNT> CHOICES = MAIN_CHOICES;

	screen_x_t left = (MENU_CENTER_X - (MAIN_CHOICE_W / 2));
	screen_y_t top = choice_top(choice, MAIN_CHOICE_COUNT);

	// No unblitting necessary here, as only the colors change.
	graph_putsa_fx(left, top, (col | FX), CHOICES.t[choice]);
}

void option_choice_unput_and_put(int choice, int col)
{
	extern TextArray<OPTION_CHOICE_COUNT> OPTION_CHOICES;
	extern TextArray<RANK_COUNT> RANK_VALUES;
	extern TextArray<BGM_MODE_COUNT> BGM_MODE_VALUES;
	extern TextArray<CFG_LIVES_EXTRA_MAX> START_LIFE_VALUES;

	const TextArray<OPTION_CHOICE_COUNT> CHOICES = OPTION_CHOICES;
	const TextArray<RANK_COUNT> RANKS = RANK_VALUES;
	const TextArray<BGM_MODE_COUNT> MUSIC_MODES = BGM_MODE_VALUES;
	const TextArray<CFG_LIVES_EXTRA_MAX> START_LIVES = START_LIFE_VALUES;

	screen_x_t left = (MENU_CENTER_X - (MENU_W / 2));
	screen_y_t top = choice_top(choice, OPTION_CHOICE_COUNT);

	egc_copy_rect_1_to_0_16(left, top, MENU_W, GLYPH_H);

	if(choice == 0) {
		choice_put_value(left, top, col, CHOICES.t[choice], RANKS.t[opts.rank]);
	} else if(choice == 1) {
		choice_put_value(
			left, top, col, CHOICES.t[choice], MUSIC_MODES.t[opts.bgm_mode]
		);
	} else if(choice == 2) {
		choice_put_value(
			left, top, col, CHOICES.t[choice], START_LIVES.t[opts.lives_extra]
		);
	} else if(choice == 3) {
		choice_put(left, top, col, CHOICES.t[choice]);
	} else if(choice == 4) {
		choice_put(left, top, col, CHOICES.t[choice]);
	}
}

extern int8_t music_sel;

void music_choice_unput_and_put(int choice, int col)
{
	extern const char aS_2d[];
	extern TextArray<MUSIC_CHOICE_COUNT> MUSIC_CHOICES;
	extern TextArray<TRACK_COUNT> MUSIC_TITLES;

	const TextArray<MUSIC_CHOICE_COUNT> CHOICES = MUSIC_CHOICES;
	const TextArray<TRACK_COUNT> TITLES = MUSIC_TITLES;

	screen_x_t left = (MENU_CENTER_X - (MENU_W / 2));
	screen_y_t top = music_choice_top(choice, MUSIC_CHOICE_COUNT);

	egc_copy_rect_1_to_0_16(left, top, MENU_W, GLYPH_H);

	if(choice == 0) {
		// ZUN bug: That's larger than the menu?
		egc_copy_rect_1_to_0_16(
			left, (top + CHOICE_PADDED_H), (MENU_W + GLYPH_FULL_W), GLYPH_H
		);
		graph_printf_fx(
			left, top, (col | FX), aS_2d, CHOICES.t[choice], music_sel
		);
		choice_put(left, (top + CHOICE_PADDED_H), col, TITLES.t[music_sel]);
	} else if(choice == 1) {
		choice_put(left, top, col, CHOICES.t[choice]);
	}
}

void main_update_and_render(void)
{
	#define sel_prev    	main_sel_prev
	#define in_this_menu	main_in_this_menu

	extern int sel_prev;
	extern bool16 in_this_menu;

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

	#undef in_this_menu
	#undef sel_prev
}

void option_update_and_render(void)
{
	#define in_this_menu	option_in_this_menu
	#define sel_prev    	option_sel_prev
	#define left_locked 	option_left_locked
	#define right_locked	option_right_locked

	extern bool16 in_this_menu;
	extern int sel_prev;
	extern bool16 left_locked;
	extern bool16 right_locked;

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
			ring_dec_16(opts.lives_extra, (CFG_LIVES_EXTRA_MAX - 1));
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
			ring_inc(opts.lives_extra, (CFG_LIVES_EXTRA_MAX - 1));
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

	#undef right_locked
	#undef left_locked
	#undef sel_prev
	#undef in_this_menu
}
/// ---------

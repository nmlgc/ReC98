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
#include "th01/rank.h"
#include "th01/resident.hpp"
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
// These will be removed once the strings can be defined here
#undef CFG_FN
#undef CFG_ID
extern const char CFG_FN[], CFG_ID[], FOPEN_RB[], FOPEN_WB[];

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

extern char menu_sel;
extern bool input_left;
extern bool input_cancel;
extern bool input_right;
extern unsigned char option_rows;

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
		RING_DEC(menu_sel, 3)
	);

	keygroup_sense(out2, in, 9);

	input_onchange_ring(1,
		(out1.h.ah & K7_ARROW_DOWN) || (out2.h.ah & K9_NUM_2),
		RING_INC(menu_sel, 3)
	);

	ok_shot_cancel_sense(out1, in);
}

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
		RING_DEC(menu_sel, option_rows)
	);
	input_update_bool(
		input_left, (out1.h.ah & K7_ARROW_LEFT) || (out2.h.ah & K8_NUM_4)
	);

	keygroup_sense(out2, in, 9);

	input_onchange_ring(1,
		(out1.h.ah & K7_ARROW_DOWN) || (out2.h.ah & K9_NUM_2),
		RING_INC(menu_sel, option_rows)
	);
	input_update_bool(
		input_right, (out1.h.ah & K7_ARROW_RIGHT) || (out2.h.ah & K9_NUM_6)
	);

	ok_shot_cancel_sense(out1, in);
}
/// -----

/// White line animation
/// --------------------
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

void titlescreen_init(void) {
	extern const char aReimu_mdt[];
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

void titlescreen_create_op_win(void) {
	extern const char aOp_win_grp[];

	graph_accesspage_func(1);
	graph_copy_accessed_page_to_other();
	graph_accesspage_func(0);
	grp_put_colorkey(aOp_win_grp);
	graph_copy_accessed_page_to_other();
}

void key_end_resident_free(void) {
	extern char quit_flag;

	if(quit_flag == 1)
		resident_free();

	key_end();
}

extern long rand;
extern char mode;

void start(void) {
	extern char aReiiden_0[];

	cfg_save();
	resident_stuff_set(opts.rank, opts.bgm_mode, opts.bombs, opts.lives_extra, rand);
	key_end_resident_free();
	mdrv2_bgm_fade_out_nonblock();
	game_switch_binary();

	if(mode == 2) {
		resident->debug_mode = DM_TEST;
	} else if(mode == 3) {
		resident->debug_mode = DM_FULL;
	} else if(mode == 0) {
		resident->debug_mode = DM_OFF;
	}

	resident->route = 0;
	resident->stage_id = 0;
	resident->rem_lives = opts.lives_extra + 2;
	resident->point_value = 0;

	for(int i = 0; i < 4; i++) {
		resident->continues_per_scene[i] = 0;
		resident->bonus_per_stage[i] = 0;
	}

	resident->score_highest = 0;
	resident->continues_total = 0;
	resident->end_flag = ES_NONE;
	resident->unused_1 = 0;
	resident->snd_need_init = 1;
	resident->pellet_speed = -4;

	execl(aReiiden_0, aReiiden_0, NULL);
}

void Continue(void) { // Reserved keyword
	cfg_save();
	resident_stuff_set(opts.rank, opts.bgm_mode, opts.bombs, opts.lives_extra, rand);

	if(resident->stage_id == 0) {
		_ES = FP_SEG(cfg_load); // Yes, no point to this at all
	}

	key_end_resident_free();
	mdrv2_bgm_fade_out_nonblock();
	game_switch_binary();

	resident->debug_mode = DM_OFF;
	resident->snd_need_init = 1;
	resident->rem_lives = opts.lives_extra + 2;
	resident->unused_1 = 0;
	resident->pellet_speed = -4;
	resident->point_value = 0;

	execl((char*)MK_FP(_DS, CFG_ID), (char*)MK_FP(_DS, CFG_ID), NULL);
}

#define HIT_KEY_CYCLE_DUR 70
#define HIT_KEY_SHOW_FRAMES 50

#define HIT_KEY_LEFT 244
#define MAIN_MENU_LEFT 228
#define MAIN_MENU_TOP 306
#define MAIN_MENU_TEXT_WIDTH 128
#define MAIN_MENU_TEXT_HEIGHT 16
#define MAIN_MENU_OPTION_DISTANCE 20
#define MAIN_MENU_OPTION_TOP 276

void titlescreen_flash_hit_key_prompt(int frame) {
	extern const char GP_HIT_KEY[];

	if(frame % HIT_KEY_CYCLE_DUR < HIT_KEY_SHOW_FRAMES) {
		graph_putsa_fx(HIT_KEY_LEFT, MAIN_MENU_TOP, FX_WEIGHT_BOLD | 0xF, GP_HIT_KEY);
	} else {
		egc_copy_rect_1_to_0_16(HIT_KEY_LEFT, MAIN_MENU_TOP, MAIN_MENU_TEXT_WIDTH, MAIN_MENU_TEXT_HEIGHT);
	}
}

#define MAIN_MENU_ENTRY_COUNT 4
#define OPTIONS_COUNT 5
#define RANK_COUNT 4
#define FM_OPTION_COUNT 2
#define LIFES_AMOUNT_TEXT_COUNT 5

#define MUSIC_TEST_MENU_OPTION_COUNT 2
#define MUSIC_TEST_SONG_COUNT 15

template <int c> struct text_array_t {
	const char* t[c];
};

void main_menu_draw_option(int str_idx, int col) {
	extern text_array_t<MAIN_MENU_ENTRY_COUNT> MAIN_MENU_TEXT;

	int _str_idx = str_idx;
	int x;
	int y;

	text_array_t<MAIN_MENU_ENTRY_COUNT> _main_menu_text = MAIN_MENU_TEXT;

	x = HIT_KEY_LEFT;
	y = _str_idx * MAIN_MENU_OPTION_DISTANCE + MAIN_MENU_OPTION_TOP;

	graph_putsa_fx(x, y, col | FX_WEIGHT_BLACK, _main_menu_text.t[_str_idx]);
}

extern const char aSS[];

void option_menu_draw_option(int option, int col) {
	extern text_array_t<OPTIONS_COUNT> OPTIONS_TEXT;
	extern text_array_t<RANK_COUNT> RANK_TEXT;
	extern text_array_t<FM_OPTION_COUNT> FM_OPTION;
	extern text_array_t<LIFES_AMOUNT_TEXT_COUNT> LIFES_AMOUNT_TEXT;

	int _option = option;

	text_array_t<OPTIONS_COUNT> _options_text = OPTIONS_TEXT;
	text_array_t<RANK_COUNT> _rank_text = RANK_TEXT;
	text_array_t<FM_OPTION_COUNT> _fm_option = FM_OPTION;
	text_array_t<LIFES_AMOUNT_TEXT_COUNT> _lifes_amount_text = LIFES_AMOUNT_TEXT;

	int left = MAIN_MENU_LEFT;
	int top = _option * 20 + 266;

	egc_copy_rect_1_to_0_16(left, top, 0xB0, 0x10);

	if(_option == 0) {
		graph_printf_fx(left, top, col | FX_WEIGHT_BLACK, aSS, _options_text.t[_option], _rank_text.t[opts.rank]);
	} else if(_option == 1) {
		graph_printf_fx(left, top, col | FX_WEIGHT_BLACK, aSS, _options_text.t[_option], _fm_option.t[opts.bgm_mode]);
	} else if(_option == 2) {
		graph_printf_fx(left, top, col | FX_WEIGHT_BLACK, aSS, _options_text.t[_option], _lifes_amount_text.t[opts.lives_extra]);
	} else if(_option == 3) {
		graph_printf_fx(left, top, col | FX_WEIGHT_BLACK, aSS + 2, _options_text.t[_option]);
	} else if(_option == 4) {
		graph_printf_fx(left, top, col | FX_WEIGHT_BLACK, aSS + 2, _options_text.t[_option]);
	}
}

extern char bgm_playing;
extern const char aS_2d[];

void music_test_draw(int line, int col) {
	int _line = line;

	extern text_array_t<MUSIC_TEST_MENU_OPTION_COUNT> MUSIC_TEST_MENU_TEXT;
	extern text_array_t<MUSIC_TEST_SONG_COUNT> MUSIC_TEST_SONGS;

	text_array_t<MUSIC_TEST_MENU_OPTION_COUNT> _music_test_menu_text = MUSIC_TEST_MENU_TEXT;
	text_array_t<MUSIC_TEST_SONG_COUNT> _music_test_songs = MUSIC_TEST_SONGS;

	int left = MAIN_MENU_LEFT;
	int top = _line * 40 + 286;

	egc_copy_rect_1_to_0_16(left, top, 176, 16);

	if(_line == 0) {
		egc_copy_rect_1_to_0_16(left, top + 20, 192, 16);
		graph_printf_fx(left, top, col | FX_WEIGHT_BLACK, aS_2d, _music_test_menu_text.t[_line], bgm_playing);
		graph_printf_fx(left, top + 20, col | FX_WEIGHT_BLACK, aSS + 2, _music_test_songs.t[bgm_playing]);
	} else if(_line == 1){
		graph_printf_fx(left, top, col | FX_WEIGHT_BLACK, aSS + 2, _music_test_menu_text.t[_line]);
	}
}

/// --------------------

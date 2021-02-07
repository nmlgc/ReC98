/* ReC98
 * -----
 * Code segment #1 of TH01's OP.EXE
 */

extern "C" {
#include <mem.h>
#include <stdio.h>
#include "ReC98.h"
#include "x86real.h"
#include "pc98kbd.h"
#include "master.hpp"
#include "th01/ranks.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/input.hpp"
#include "th01/hardware/vsync.h"
#include "th01/formats/cfg.hpp"

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
	grcg_setcolor_tdw(4);
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

	if(( fp = fopen(CFG_FN, FOPEN_RB) ) == NULL) {
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

	if(( fp = fopen(CFG_FN, FOPEN_WB) ) == NULL) {
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

inline void keygroup_sense(REGS& out, REGS& in, char group_id)
{
	in.h.ah = 0x04;
	in.h.al = group_id;
	int86(0x18, &in, &out);
}

inline void ok_shot_cancel_sense(REGS& out, REGS& in)
{
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
		egc_put(vram_offset, 0xFFFFFFFF, 32);
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
	graph_copy_page_back_to_front();
	graph_accesspage_func(0);
}
/// --------------------

}

/* ReC98
 * -----
 * Code segment #1 of TH01's REIIDEN.EXE
 */

#include <process.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "x86real.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "pc98kbd.h"
#include "shiftjis.hpp"
#include "th01/common.h"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/core/initexit.hpp"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/grppsafx.h"
#include "th01/hardware/input.hpp"
#include "th01/hardware/palette.h"
#include "th01/hardware/text.h"
#include "th01/hardware/tram_x16.hpp"
#include "th01/hardware/ztext.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/formats/grp.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/formats/scoredat.hpp"
#include "th01/main/debug.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/vars.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/main/player/anim.hpp"
#include "th01/main/player/bomb.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/bullet/laser_s.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/stage/card.hpp"
#include "th01/main/stage/item.hpp"
#include "th01/main/stage/palette.hpp"
#include "th01/main/stage/stages.hpp"
#include "th01/main/stage/stageobj.hpp"
#include "th01/main/hud/hud.hpp"
#include "th01/shiftjis/debug.hpp"
#include "th01/shiftjis/entrance.hpp"
#include "th01/shiftjis/fns.hpp"

int8_t temporary_padding = 0;

inline void bomb_doubletap_update(uint8_t& pressed, uint8_t& other) {
	if(bomb_doubletap_frames < BOMB_DOUBLETAP_WINDOW) {
		pressed++;
	} else {
		bomb_doubletap_frames = 0;
		pressed = 1;
		other = 0;
	}
}

void input_sense(bool16 reset_repeat)
{
	extern uint8_t input_prev[16];
	int group_1, group_2, group_3, group_4;

	if(reset_repeat == true) {
		input_prev[0] = 0;
		input_prev[1] = 0;
		input_prev[2] = 0;
		input_prev[3] = 0;
		input_prev[8] = 0;
		input_prev[9] = 0;
		input_prev[10] = 0;
		input_prev[11] = 0;
		input_prev[4] = 0;
		input_prev[5] = 0;
		input_prev[6] = 0;
		input_prev[7] = 0;
		input_prev[12] = 0;
		input_prev[13] = 0;
		// Yup, no reset for 14 or 15.
		input_bomb = 0;
		return;
	}
	#define bomb_doubletap_shot input_prev[12]
	#define bomb_doubletap_strike input_prev[13]

	group_1 = key_sense(7);
	group_2 = key_sense(5);
	group_3 = key_sense(8);
	group_4 = key_sense(9);
	group_1 |= key_sense(7);
	group_2 |= key_sense(5);
	group_3 |= key_sense(8);
	group_4 |= key_sense(9);

	input_onchange_bool_2(0, 8,
		input_up, (group_1 & K7_ARROW_UP), (group_3 & K8_NUM_8)
	);
	input_onchange_bool_2(1, 9,
		input_down, (group_1 & K7_ARROW_DOWN), (group_4 & K9_NUM_2)
	);
	input_onchange_flag_2(2, 10,
		input_lr, INPUT_LEFT, (group_1 & K7_ARROW_LEFT), (group_3 & K8_NUM_4)
	);
	input_onchange_flag_2(3, 11,
		input_lr, INPUT_RIGHT, (group_1 & K7_ARROW_RIGHT), (group_4 & K9_NUM_6)
	);
	input_onchange(4, (group_2 & K5_Z), {
		input_shot = true;
		bomb_doubletap_update(bomb_doubletap_shot, bomb_doubletap_strike);
	} else {
		input_shot = false;
	});
	input_onchange(5, (group_2 & K5_X), {
		input_strike = true;
		bomb_doubletap_update(bomb_doubletap_strike, bomb_doubletap_shot);
	} else {
		input_strike = false;
	});

	input_pause_ok_sense(6, 7, group_1, group_2);

	if(
		(bomb_doubletap_strike >= 2 && bomb_doubletap_shot >= 2) ||
		((input_lr == INPUT_LEFT_RIGHT) && input_shot)
	) {
		input_bomb = true;
		bomb_doubletap_strike = 0;
		bomb_doubletap_shot = 0;
	}

	if(mode_test == true) {
		group_1 = key_sense(6);
		group_1 |= key_sense(6);

		// Hilarious bug: debug_mem() itself renders a sub-screen in a blocking
		// way, and senses input after a 3-frame delay, thus recursing back
		// into this function. Therefore, debug_mem() will also be recursively
		// called for every 3 frames you're holding this key.
		// [input_prev[14]], which is supposed to prevent that, isn't set
		// until debug_mem() returns, making this variable entirely pointless.
		input_onchange(14, (group_1 & K6_ROLL_UP), {
			input_mem_enter = true;
			debug_mem();
		} else {
			input_mem_enter = false;
		});
		// And since this works as intended and only sets [input_mem_leave] to
		// true on the first non-repeated key down event, you need to actually
		// press and release this key once for every call to debug_mem() to get
		// back into the game - even though debug_show_game() will make it
		// appear as if you're already back in the game.
		input_onchange(15, (group_1 & K6_ROLL_DOWN), {
			input_mem_leave = true;
			debug_show_game();
		} else {
			input_mem_leave = false;
		});
	}
}

#include "th01/hardware/input_rs.cpp"
#include "th01/hardware/tram_x16.cpp"

// Largely copy-pasted from harryup_animate().
void pascal stage_num_animate(unsigned int stage_num)
{
	utram_kanji_amount_t x;
	upixel_t glyph_y;
	TRAMx16Row<dots_t(GLYPH_HALF_W)> row;
	TRAMCursor tram_cursor;
	unsigned int stage_num_local = stage_num;
	unsigned int i;
	REGS in;
	StupidBytewiseWrapperAround<pc98_glyph_ank_8x16_t> glyphs[7];

	fontrom_get(in, glyphs[0].t, 'S');
	fontrom_get(in, glyphs[1].t, 'T');
	fontrom_get(in, glyphs[2].t, 'A');
	fontrom_get(in, glyphs[3].t, 'G');
	fontrom_get(in, glyphs[4].t, 'E');
	// Yes, these are technically fontrom_get() calls as well, and were just
	// inlined for code generation reasons.
	int18h_14h(in, glyphs[5].t, (0x8000 + '0' + (stage_num_local / 10)));
	int18h_14h(in, glyphs[6].t, (0x8000 + '0' + (stage_num_local % 10)));

	tram_cursor.rewind_to_topleft();
	tram_cursor.putkanji_for_5_rows(' ', TX_BLACK);

	glyph_y = offsetof(pc98_glyph_ank_8x16_t, dots);
	while(glyph_y <= (sizeof(pc98_glyph_ank_8x16_t) - 1)) {
		for(i = 0; i < 5; i++) {
			tram_x16_row_put_red(row, tram_cursor, x, glyphs[i].byte[glyph_y]);
		}
		// 5 halfwidth glyphs scaled a factor of 16 just happen to exactly fit
		// into one TRAM row, so we're already at the next one here.
		glyph_y++;
	}
	tram_cursor.putkanji_until_end(' ', TX_BLACK);

	frame_delay(35);

	tram_cursor.rewind_to_topleft();
	tram_cursor.putkanji_for_5_rows(' ', TX_BLACK);

	glyph_y = offsetof(pc98_glyph_ank_8x16_t, dots);
	while(glyph_y <= (sizeof(pc98_glyph_ank_8x16_t) - 1)) {
		tram_x16_put_center_margin(tram_cursor, x, TX_BLACK);
		for(i = 5; i < 7; i++) {
			tram_x16_row_put_red(row, tram_cursor, x, glyphs[i].byte[glyph_y]);
		}
		tram_x16_put_center_margin(tram_cursor, x, TX_BLACK);
		glyph_y++;
	}
	tram_cursor.putkanji_until_end(' ', TX_BLACK);

	frame_delay(35);
	z_text_clear_inlined();
}

void load_and_init_stuff_used_in_all_stages(void)
{
	int i;

	scoredat_load_hiscore();
	hud_bg_load("mask.grf");
	player_48x48.load("miko_ac.bos");
	player_48x32.load("miko_ac2.bos");
	ptn_load(PTN_SLOT_STG, PTN_STG_CARDFLIP_FN);
	ptn_load(PTN_SLOT_MIKO, "miko.ptn");
	ptn_new(PTN_SLOT_BG_HUD, ((PTN_BG_last - PTN_BG_first) + 1));
	bomb_kuji_load();
	shootout_lasers_init(i);
	ptn_slot_stg_has_reduced_sprites = false;
}

void stage_entrance(int stage_id, const char* bg_fn, bool16 clear_vram_page_0)
{
	int x;
	int y;

	if(first_stage_in_scene == true) {
		text_fill_black(x, y);
		text_color_reset();

		if(strcmp(bg_fn, "empty.grf")) {
			grp_put_palette_show(bg_fn);
		}
		stage_palette_set(z_Palettes);
		graph_copy_accessed_page_to_other(); // 0 → 1, redundant
	} else {
		graph_accesspage_func(1);
		graph_copy_accessed_page_to_other();
		graph_accesspage_func(0);
		player_put_default(); // redundant
	}

	stageobjs_init_and_render(stage_id); // rendered to page 0

	if(first_stage_in_scene == true) {
		graph_copy_accessed_page_to_other(); // 0 → 1
	} else if(first_stage_in_scene == false) {
		// Yes, this entire function would not have been necessary.
		stageobjs_copy_0_to_1(stage_id);

		// :zunpet:
		graph_accesspage_func(0);
		graph_accesspage_func(1);
		graph_accesspage_func(0);
		player_put_default();
		items_bomb_render();
		items_point_render();
	}
	if(clear_vram_page_0) {
		z_graph_clear();
	}
	if(
		((stage_id % STAGES_PER_SCENE) == 0) ||
		((stage_id % STAGES_PER_SCENE) == BOSS_STAGE)
	) {
		touhou_reiiden_animate();
	}
	stage_num_animate(stage_num);
}

#include "th01/main/player/bomb.cpp"
#include "th01/main/stage/palette.cpp"
#include "th01/main/player/inv_spr.cpp"
#include "th01/main/player/orb.cpp"
#include "th01/main/hud/menu.cpp"
#include "th01/main/player/gameover.cpp"
#include "th01/main/extend.cpp"
#include "th01/main/debug.cpp"

bool16 stageobj_bgs_free_wrap(void)
{
	return stageobj_bgs_free();
}

void graphics_free_redundant_and_incomplete(void)
{
	stageobj_bgs_free();
	for(int i = PTN_SLOT_BOSS_1; i < PTN_SLOT_COUNT; i++) {
		ptn_free(static_cast<main_ptn_slot_t>(i));
		if(i < BOS_ENTITY_SLOT_COUNT) {
			bos_entity_free(i);
		}
	}
}

void error_resident_invalid(void)
{
	printf(ERROR_RESIDENT_INVALID);
}

void pellet_destroy_score_delta_commit(void)
{
	score += pellet_destroy_score_delta;
	hud_score_and_cardcombo_render();
	pellet_destroy_score_delta = 0;
}

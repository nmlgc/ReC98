/* ReC98
 * -----
 * Code segment #1 of TH01's REIIDEN.EXE
 */

#include <float.h>
#include <new.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include "platform/x86real/pc98/keyboard.hpp"
#include "platform/x86real/pc98/page.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/core/initexit.hpp"
#include "th01/core/resstuff.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/input.hpp"
#include "th01/hardware/palette.h"
#include "th01/hardware/text.h"
#include "th01/hardware/ztext.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/formats/cfg.hpp"
#include "th01/formats/grp.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/ptn_data.hpp"
#include "th01/hiscore/regist.hpp"
#include "th01/main/bonus.hpp"
#include "th01/main/debug.hpp"
#include "th01/main/player/anim.hpp"
#include "th01/main/player/bomb.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/player/shot.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/bullet/laser_s.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/stage/card.hpp"
#include "th01/main/stage/item.hpp"
#include "th01/main/stage/palette.hpp"
#include "th01/main/stage/stages.hpp"
#include "th01/main/stage/stageobj.hpp"
#include "th01/main/stage/timer.hpp"
#include "th01/main/hud/hud.hpp"
#include "th01/shiftjis/debug.hpp"
#include "th01/shiftjis/entrance.hpp"
#include "th01/shiftjis/fns.hpp"
#include "th01/shiftjis/scoredat.hpp"

// Redundant copies of resident structure fields to static data
// ------------------------------------------------------------

uint8_t rank;
bgm_mode_t bgm_mode = CFG_BGM_MODE_DEFAULT;
int8_t rem_bombs = CFG_CREDIT_BOMBS_DEFAULT;
int rem_lives = 4;
unsigned long frame_rand;
// ------------------------------------------------------------

struct {
	// Specifies whether PTN_SLOT_STG contains the full set of sprites required
	// for card-flipping stages (`false`), or the trimmed-down version for boss
	// stages (`true`).
	bool has_reduced_sprites;

	void switch_to_full(void) {
		if(has_reduced_sprites) {
			ptn_free(PTN_SLOT_STG);
			ptn_load(PTN_SLOT_STG, PTN_STG_CARDFLIP_FN);
			has_reduced_sprites = false;
		}
	}

	void switch_to_reduced(void) {
		if(!has_reduced_sprites) {
			ptn_free(PTN_SLOT_STG);
			ptn_load(PTN_SLOT_STG, PTN_STG_BOSS_FN);
			has_reduced_sprites = true;
		}
	}
} ptn_slot_stg = { false };

// Largely copy-pasted from harryup_animate().
void stage_num_animate(unsigned int stage_num)
{
	TRAMCursor tram_cursor;
	REGS in;
	font_glyph_ank_8x16_t glyphs[7];

	font_read(glyphs[0], 'S');
	font_read(glyphs[1], 'T');
	font_read(glyphs[2], 'A');
	font_read(glyphs[3], 'G');
	font_read(glyphs[4], 'E');
	font_read(glyphs[5], ('0' + (stage_num / 10)));
	font_read(glyphs[6], ('0' + (stage_num % 10)));

	tram_cursor.rewind_to_topleft();
	tram_cursor.putkanji_for_5_rows(' ', TX_BLACK);

	{for(upixel_t glyph_y = 0; glyph_y < GLYPH_H; glyph_y++) {
		for(unsigned int i = 0; i < 5; i++) {
			tram_x16_row_put_red(
				tram_cursor, &glyphs[i].dots[glyph_y], GLYPH_HALF_W
			);
		}
		// 5 halfwidth glyphs scaled by a factor of 16 just happen to exactly
		// fit into one TRAM row, so we're already at the next one here.
	}}
	tram_cursor.putkanji_until_end(' ', TX_BLACK);

	frame_delay(35);

	tram_cursor.rewind_to_topleft();
	tram_cursor.putkanji_for_5_rows(' ', TX_BLACK);

	{for(upixel_t glyph_y = 0; glyph_y < GLYPH_H; glyph_y++) {
		tram_x16_put_center_margin(tram_cursor, TX_BLACK);
		for(unsigned int i = 5; i < 7; i++) {
			tram_x16_row_put_red(
				tram_cursor, &glyphs[i].dots[glyph_y], GLYPH_HALF_W
			);
		}
		tram_x16_put_center_margin(tram_cursor, TX_BLACK);
	}}
	tram_cursor.putkanji_until_end(' ', TX_BLACK);

	frame_delay(35);
	z_text_clear_inlined();
}

void stage_entrance(int stage_id, const char* bg_fn, bool16 clear_vram_page_0)
{
	int x;
	int y;

	if(first_stage_in_scene == true) {
		text_fill_black(x, y);
		text_color_reset();

		if(strcmp(bg_fn, "empty.grf")) {
			grp_put(bg_fn, GPF_PALETTE_SHOW);
		}
		stage_palette_set(z_Palettes);

		// Copy the raw background image to page 1, so that
		// stageobjs_init_and_render() can snap the correct backgrounds.
		graph_copy_page_to_other(0);
		page_access(0);
	} else {
		graph_copy_page_to_other(1);

		// Keep the player on screen during stage_num_animate()
		page_access(0);
		player_put_default();
	}

	stageobjs_init_and_render(stage_id); // rendered to page 0

	if(first_stage_in_scene == true) {
		graph_copy_page_to_other(0); // 0 → 1, with new stage objects
		page_access(0);
	} else if(first_stage_in_scene == false) {
		// ZUN bloat: This entire function would not have been necessary if ZUN
		// just rendered the stage objects to page 1 and then always copied the
		// entire page, not just if [first_stage_in_scene] is true.
		stageobjs_copy_0_to_1(stage_id);

		// ZUN bloat: Already did this above.
		page_access(0);
		player_put_default();

		items_bomb_render();
		items_point_render();
	}
	if(clear_vram_page_0) {
		z_graph_clear();
	}
	if(stage_resets_game_state(stage_id)) {
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

// ZUN bloat: This function is only ever (meaningfully) called before process
// termination when the standard library heap is destroyed anyway. You might
// argue that it's cleaner to free all memory, but then, why doesn't it free
// PTN_SLOT_MIKO?
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

int8_t boss_id = BID_NONE; // ACTUAL TYPE: boss_id_t

void boss_free(void)
{
	switch(boss_id) {
	case BID_SINGYOKU:   	singyoku_free();   	break;
	case BID_YUUGENMAGAN:	yuugenmagan_free();	break;
	case BID_MIMA:       	mima_free();       	break;
	case BID_KIKURI:     	kikuri_free();     	break;
	case BID_ELIS:       	elis_free();       	break;
	case BID_SARIEL:     	sariel_free();     	break;
	case BID_KONNGARA:   	konngara_free();   	break;
	}
}

inline void debug_startup_delay(const char* str) {
	puts(str);
	debug_vars();
	frame_delay(40);
}

inline void debug_startup_delay() {
	debug_vars();
	frame_delay(40);
}

// Default filenames for the background image and music.
char default_grp_fn[15] = "ST .GRP";
char default_bgm_fn[15] = "ST .MDT";

int main_main(int, const char *[])
{
	bool stage_wait_for_shot_to_begin;

	int stage_id = 0;
	int bgm_reload_and_play_if_0 = 0;
	bool16 clear_vram_page_0;
	bool16 quit = false;
	int scene_id;
	char* grp_fn;
	int pellet_speed_raise_cycle;
	int stage_id_copy;
	char bgm_fn[16];

	if(!mdrv2_resident()) {
		error_resident_invalid();
		return 1;
	}
	if(resident_stuff_get(rank, frame_rand, stage_id) == 1) {
		error_resident_invalid();
		return 1;
	}

	score = resident->score;
	extend_next = ((resident->score / SCORE_PER_EXTEND) + 1);
	irand_init(frame_rand);
	game_init();
	key_start();

	// Disable all FPU exceptions
	_control87(MCW_EM, MCW_EM);

	route_t route = resident->route;
	if(resident->debug_mode != DM_OFF) {
		if(resident->stage_id == 0) {
			puts(STAGESELECT_TITLE "\n");

			// ZUN quirk: Does not prevent negative values from being entered.
			// Might be seen as a bug as well, but the resulting glitch stages
			// have a consistent appearance, and can therefore be considered
			// canon...
			puts(STAGESELECT_STAGE);
			scanf("%d", &stage_id);

			// %d assumes that the argument is an `int`, which `route_t` might
			// not be.
			int route_scanf_d;
			puts(STAGESELECT_ROUTE);
			scanf("%d", &route_scanf_d);
			route = static_cast<route_t>(route_scanf_d);

			if(!stage_on_route(stage_id)) {
				route = ROUTE_MAKAI;
			} else {
				if(route > ROUTE_JIGOKU) {
					route = ROUTE_JIGOKU;
				} else if(route < ROUTE_MAKAI) {
					route = ROUTE_MAKAI;
				}
			}
			resident->route = route;
		}
		if(resident->debug_mode == DM_TEST) {
			puts(DM_TEST_STARTING "\n");
			mode_test = true;
		}
		if(resident->debug_mode == DM_FULL) {
			puts(DM_FULL_STARTING "\n");
			mode_debug = true;
			mode_test = true;
		}
	}

	if(resident->bgm_mode == BGM_MODE_MDRV2) {
		mdrv2_enable_if_board_installed();
	}
	scene_id = (
		(stage_id < (1 * STAGES_PER_SCENE)) ? 0 :
		(stage_id < (2 * STAGES_PER_SCENE)) ? ((route == ROUTE_MAKAI) ? 1 : 2) :
		(stage_id < (3 * STAGES_PER_SCENE)) ? ((route == ROUTE_MAKAI) ? 3 : 4) :
		(stage_id < (4 * STAGES_PER_SCENE)) ? ((route == ROUTE_MAKAI) ? 5 : 6) :

		// Stages 21-25 confirmed to have been planned as an Extra Stage?
		// Seems way too specific to just be meant as a fallback.
		7
	);
	set_new_handler(out_of_memory_exit);
	arc_key = ARC_KEY;
	arc_load(ARC_FN);

	default_grp_fn[2] = (scene_id + '0');
	default_bgm_fn[2] = (scene_id + '0');

	scene_init_and_load(scene_id);

	if(mode_debug == true) {
		debug_startup_delay();
	}

	rem_lives = resident->rem_lives;
	rem_bombs = resident->rem_bombs;
	player_left = PLAYER_LEFT_START;

	if((resident->bgm_mode != BGM_MODE_OFF) && resident->snd_need_init) {
		mdrv2_bgm_load("init.mdt");
		mdrv2_bgm_play();
		mdrv2_se_load(SE_FN);
		// Kind of pointless if the flag isn't reset?
	}

	if(mode_debug == true) {
		debug_startup_delay("2 :");
	}

	coreleft_prev = coreleft();

	scoredat_load();
	resident->hiscore = scoredat_hiscore_get();
	scoredat_free();
	hud_bg_load("mask.grf");
	player_48x48.load("miko_ac.bos");
	player_48x32.load("miko_ac2.bos");
	ptn_load(PTN_SLOT_STG, PTN_STG_CARDFLIP_FN);
	ptn_load(PTN_SLOT_MIKO, "miko.ptn");
	ptn_new(PTN_SLOT_BG_HUD, ((PTN_BG_last - PTN_BG_first) + 1));
	bomb_kuji_load();
	ptn_slot_stg.has_reduced_sprites = false;

	z_graph_init();
	page_access(0);
	z_graph_clear();
	card_flip_cycle = (irand() % CARD_FLIP_CYCLE_INITIAL_MAX);
	first_stage_in_scene = true;
	stage_wait_for_shot_to_begin = true;
	bgm_reload_and_play_if_0 = (!resident->snd_need_init ? 1 : 0);

	// Stage loop
	while(1) {
		resident->stage_id = stage_id;

		resident->score = score;
		Pellets.unput_and_reset_nonclouds();
		Shots.unput_and_reset();

		grp_fn = default_grp_fn;

		boss_id = BID_NONE;
		player_invincible = false;
		player_invincibility_time = 0;

		switch(stage_id) {
		case ((0 * STAGES_PER_SCENE) + BOSS_STAGE):
			boss_id = BID_SINGYOKU;
			strcpy(grp_fn, "boss1.grp");
			strcpy(bgm_fn, "positive.mdt");
			clear_vram_page_0 = false;
			singyoku_load();
			break;

		case ((1 * STAGES_PER_SCENE) + BOSS_STAGE):
			boss_id = (BID_YUUGENMAGAN + route);
			if(route == ROUTE_MAKAI) {
				strcpy(bgm_fn, "LEGEND.mdt");
				strcpy(grp_fn, "boss2.grp");
				yuugenmagan_load();
			} else {
				strcpy(bgm_fn, "LEGEND.mdt");
				strcpy(grp_fn, "boss3.grp");
				mima_load();
			}
			clear_vram_page_0 = false;
			break;

		case ((2 * STAGES_PER_SCENE) + BOSS_STAGE):
			boss_id = (BID_KIKURI + (ROUTE_JIGOKU - route));
			if(route == ROUTE_JIGOKU) {
				strcpy(bgm_fn, "kami.mdt");
				strcpy(grp_fn, "boss4.grp");
				kikuri_load();
				clear_vram_page_0 = true;
			} else {
				strcpy(bgm_fn, "kami2.mdt");
				strcpy(grp_fn, "boss5.grp");
				elis_load();
				clear_vram_page_0 = false;
			}
			break;

		case ((3 * STAGES_PER_SCENE) + BOSS_STAGE):
			boss_id = (BID_SARIEL + route);

			// ZUN bloat: Both bosses have their own BGM playback calls.
			if(route == ROUTE_MAKAI) {
				strcpy(bgm_fn, "tensi.mdt");
				sariel_load_and_init();
				clear_vram_page_0 = true;
			} else {
				strcpy(bgm_fn, "alice.mdt");
				konngara_init();
				clear_vram_page_0 = false;
			}
			break;

		default:
			strcpy(bgm_fn, default_bgm_fn);
			clear_vram_page_0 = false;
			break;
		}

		if(boss_id != BID_NONE) {
			bgm_reload_and_play_if_0 = 0;
			first_stage_in_scene = true;
			items_reset();
			ptn_slot_stg.switch_to_reduced();
		} else {
			ptn_slot_stg.switch_to_full();
		}

		if(mode_debug == true) {
			debug_startup_delay("3 :");
		}

		stage_num = (stage_id + 1);

		if((boss_id != BID_SARIEL) && (boss_id != BID_KONNGARA)) {
			stage_entrance(
				(stage_id % STAGES_PER_SCENE), grp_fn, clear_vram_page_0
			);
		} else if(boss_id == BID_KONNGARA) {
			konngara_load_and_entrance(0);
		} else if(boss_id == BID_SARIEL) {
			sariel_entrance(0);
		}

		timer_init_for((stage_num - 1), route);
		hud_bg_snap_and_put();

		cardcombo_max = 0;
		orb_in_portal = false;
		bomb_frames = 0;

		if(mode_debug == true) {
			debug_startup_delay();
		}

		frames_since_start_of_binary = 0;
		orb_cur_left = ORB_LEFT_START;
		orb_cur_top = ORB_TOP_START;

		if(stage_resets_game_state(stage_id)) {
			player_left = PLAYER_LEFT_START;
		}
		orb_force = ORB_FORCE_START;
		orb_force_frame = 0;
		orb_velocity_x = ORB_VELOCITY_X_START;
		orb_prev_left = ORB_LEFT_START;
		orb_prev_top = ORB_TOP_START;
		player_deflecting = false;
		bomb_damaging = false;
		cardcombo_cur = 0;

		// Life loop
		while(1) {
			player_reset();
			player_put_default();
			orb_put_default();
			input_lr = INPUT_NONE;
			input_shot = false;
			input_ok = false;
			paused = false;
			hud_score_and_cardcombo_render();
			bomb_doubletap_frames = (BOMB_DOUBLETAP_WINDOW * 3);
			obstacles_update_and_render(true);

			// Play stage BGM. Why inside this loop though? The code would be
			// much simpler if that was part of the stage loop...
			if(
				(boss_id != BID_SARIEL) &&
				(boss_id != BID_KONNGARA) &&
				(bgm_reload_and_play_if_0 == 0)
			) {
				mdrv2_bgm_load(bgm_fn);
				mdrv2_bgm_play();
			}

			input_reset_sense();

			if(player_invincibility_time > 1) {
				player_invincible = true;
			}
			if(boss_id != BID_NONE) {
				// ZUN bloat: Moving these select entrance animations outside
				// the main gameplay loop has no discernible effect.
				switch(boss_id) {
				case BID_SINGYOKU:
					singyoku_main();
					break;

				case BID_MIMA:
					mima_main();
					break;

				case BID_KIKURI:
					// ZUN bloat: Kikuri has a blocking entrance animation as
					// well, during which Reimu isn't even visible? And once
					// it's done, this value is immediately re-sensed with the
					// actual key state before Kikuri's code gets to execute,
					// as this assignment completely bypasses the [input_prev]
					// mechanism.
					input_strike = false;
					break;
				}
			} else if(stage_wait_for_shot_to_begin == true) {
				while(!input_shot) {
					input_sense(false);

					// Allow the player to move before starting the stage
					player_unput_update_render();

					frame_delay(1);
					bomb_frames++;
				}
			}

			stage_wait_for_shot_to_begin = false;
			input_shot = false;
			irand_init(frame_rand);
			bomb_doubletap_frames = BOMB_DOUBLETAP_WINDOW;
			first_stage_in_scene = false;
			pellet_speed_raise_cycle = 3000; // ZUN bloat: Reassigned below

			// Main gameplay loop
			while(!player_is_hit) {
				frame_rand++;
				pellet_speed_raise_cycle = (
					1800 - (rem_lives * 200) - (rem_bombs * 50)
				);
				if((frame_rand % pellet_speed_raise_cycle) == 0) {
					pellet_speed_raise(0.025f);
				}
				input_sense(false);

				if(player_invincibility_time > 1) {
					player_invincibility_time--;
					player_invincible = true;
				} else if(player_invincibility_time == 1) {
					player_invincible = false;
					player_invincibility_time = 0;
				}

				player_unput_update_render();
				items_unput_update_render();
				frames_since_start_of_binary++;
				orb_force_frame++;
				bomb_frames++;
				bomb_doubletap_frames++;
				if((frame_rand & 3) == 0) {
					timer_tick_and_put();
				}

				if(mode_test == true) {
					if(input_ok) {
						test_damage = true;
					}
					if(input_down) {
						player_is_hit = true;
						rem_lives = 0;
					}
				}

				invincibility_sprites_update_and_render(player_invincible);

				switch(boss_id) {
				case BID_SINGYOKU:   	singyoku_main();   	break;
				case BID_YUUGENMAGAN:	yuugenmagan_main();	break;
				case BID_MIMA:       	mima_main();       	break;
				case BID_KIKURI:     	kikuri_main();     	break;
				case BID_ELIS:       	elis_main();       	break;
				case BID_SARIEL:     	sariel_main();     	break;
				case BID_KONNGARA:   	konngara_main();   	break;
				}

				// ZUN bloat: Why no loop?
				static_assert(SHOOTOUT_LASER_COUNT == 10);
				shootout_lasers[0].update_hittest_and_render();
				shootout_lasers[1].update_hittest_and_render();
				shootout_lasers[2].update_hittest_and_render();
				shootout_lasers[3].update_hittest_and_render();
				shootout_lasers[4].update_hittest_and_render();
				shootout_lasers[5].update_hittest_and_render();
				shootout_lasers[6].update_hittest_and_render();
				shootout_lasers[7].update_hittest_and_render();
				shootout_lasers[8].update_hittest_and_render();
				shootout_lasers[9].update_hittest_and_render();

				orb_and_pellets_and_stage_unput_update_render__vsync_wait(
					stage_id
				);

				if(paused == true) {
					quit = pause_menu();
				}
				if(quit == true) {
					goto op;
				}

				score_extend_update_and_render();

				if(mode_debug == true) {
					debug_vars();
				}

				if(game_cleared == true) {
					graphics_free_redundant_and_incomplete();
					resident->score = score;
					if(score > resident->score_highest) {
						resident->score_highest = score;
					}

					// frame_delay() abuses a non-ES_NONE [end_flag] to pick
					// FUUIN.EXE delay semantics. Therefore, we only set it
					// after the final delay.
					frame_delay(120);
					resident->end_flag = static_cast<end_sequence_t>(
						ES_MAKAI + route
					);

					game_switch_binary(EP_CUTSCENE);
				}

				// ZUN quirk: Placing this after the [game_cleared] branch robs
				// the player of the pellet destroy points gained on the last
				// frame of a final boss.
				if(pellet_destroy_score_delta) {
					score += pellet_destroy_score_delta;
					hud_score_and_cardcombo_render();
					pellet_destroy_score_delta = 0;
				}
			}
			// At this point, the player either lost a life or cleared a
			// non-final stage.
			z_vsync_wait_and_scrollup(0);
			resident->rand = frame_rand;
			test_damage = false;
			bomb_frames = 200;
			if((rem_lives <= 0) || stage_cleared) {
				break;
			}

			// Regular, non-Game Over life loss is the only remaining option
			// here. Perform the necessary updates and animations and restart
			// the life loop.
			mdrv2_se_play(5);
			resident->rem_lives--;
			rem_lives--;
			player_miss_animate_and_update();
			player_is_hit = false;
			bgm_reload_and_play_if_0++;
			player_invincibility_time = PLAYER_MISS_INVINCIBILITY_FRAMES;
		}
		// At this point, the player either cleared a non-final stage or
		// game-overed.
		if(stage_cleared == true) {
			stage_cleared = false;
			player_is_hit = false;
			if(boss_id != BID_NONE) {
				boss_free();
				stage_wait_for_shot_to_begin = true;
				first_stage_in_scene = true;
			}
			bgm_reload_and_play_if_0++;
			stage_id++;
			resident->stage_id = stage_id;
			if(boss_id != BID_NONE) {
				bgm_reload_and_play_if_0 = 0;
				totle_animate(stage_id);
			} else {
				stagebonus_animate(stage_id);
			}
			if(resident->pellet_speed < 0) {
				resident->pellet_speed = 0;
			}

			// Since [stage_id] already corresponds to the next stage, both
			// checks are necessary to handle switching into and out of a boss.
			if(stage_is_boss(stage_id) || (boss_id != BID_NONE)) {
				resident->score = score;
				resident->rem_lives = rem_lives;
				resident->snd_need_init = true;
				mdrv2_bgm_fade_out_nonblock();
				resident->rem_bombs = rem_bombs;
				game_switch_binary(EP_MAIN);
			}
			orb_in_portal = false;
			if(boss_id == BID_NONE) {
				page_access(1);
				stageobj_bgs_put_all();
				page_access(0);
			}
			stageobj_bgs_free();
			cards.free();
			obstacles.free();
		} else {
			break;
		}
	}

	// Game Over
	cards.free();
	obstacles.free();
	bgm_reload_and_play_if_0++; // ZUN bloat
	player_gameover_animate();
	Shots.unput_and_reset();
	Pellets.unput_and_reset_nonclouds();
	stageobj_bgs_free();
	extend_next = 1;
	if(boss_id != BID_NONE) {
		boss_free();
		first_stage_in_scene = true; // ZUN bloat
	}
	resident->score = score;

	z_graph_clear_0();
	z_palette_black();
	page_access(1);
	grp_put("game_o.grp", GPF_PALETTE_SHOW);
	graph_copy_page_to_other(1);
	page_access(1);
	z_palette_black_in();

	regist_menu(score, (stage_id + 1), (
		!stage_on_route(stage_id) ? SCOREDAT_ROUTE_SHRINE :
		(route == ROUTE_MAKAI) ? SCOREDAT_ROUTE_MAKAI : SCOREDAT_ROUTE_JIGOKU
	));

	resident->stage_id = stage_id;
	continue_menu();

op:
	graphics_free_redundant_and_incomplete();
	boss_free();
	key_end();
	arc_free();
	game_switch_binary(EP_OP);
	return 0;
}

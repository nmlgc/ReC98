#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/grp2xscs.hpp"
#include "th01/hardware/input.hpp"
#include "th01/hardware/palette.h"
#include "th01/hardware/scrollup.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/main/player/player.hpp"
#include "th01/shiftjis/routesel.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/boss/defeat.hpp"
#include "th01/main/stage/stages.hpp"
#include "platform/x86real/pc98/page.hpp"

void grcg_whiteline(screen_y_t y)
{
	vram_offset_t vo = vram_offset_muldiv(0, y);
	grcg_setcolor_rmw(V_WHITE);
	for(vram_word_amount_t x = 0; x < (ROW_SIZE / sizeof(dots16_t)); x++) {
		grcg_put(vo, 0xFFFF, 16);
		vo += static_cast<vram_offset_t>(sizeof(dots16_t));
	}
	grcg_off_func();
}

#define defeat_animate( \
	start_y, line_distance, whiteout_interval, whitein_interval \
) \
	svc2 col; \
	int comp; \
	screen_y_t top; \
	screen_y_t bottom; \
	int components_done; \
	int frame = 0; \
	\
	z_vsync_wait_and_scrollup(0); \
	\
	top = start_y; \
	bottom = start_y; \
	\
	while(1) { \
		if(top >= 0) { \
			grcg_whiteline(top); \
		} \
		if(bottom <= (RES_Y - 1)) { \
			grcg_whiteline(bottom); \
		} \
		top -= line_distance; \
		bottom += line_distance; \
		frame++; \
		if((top < 0) && (bottom > (RES_Y - 1))) { \
			break; \
		} \
		if((frame % whiteout_interval) == 0) { \
			z_palette_white_out_step(col, comp); \
		} \
		frame_delay(1); \
	} \
	\
	/* Aww? No ramping loop? */ \
	frame = 0; \
	z_palette_set_white(col, comp); \
	\
	/* Unblit all white lines and return to the regular stage background */ \
	graph_copy_page_to_other(1); \
	page_access(0); \
	\
	/* Reimu might not have been standing still, after all. */ \
	player_put_default(); \
	\
	/* Fade to [boss_post_defeat_palette] */ \
	while(1) { \
		frame++; \
		components_done = 0; \
		if((frame % whitein_interval) == 0) { \
			z_Palettes_set_func_and_show(col, comp, { \
				if( \
					z_Palettes[col].v[comp] > \
					boss_post_defeat_palette[col].v[comp] \
				) { \
					z_Palettes[col].v[comp]--; \
				} else { \
					components_done++; \
				} \
			}); \
		} \
		if(components_done >= (COLOR_COUNT * COMPONENT_COUNT)) { \
			break; \
		} \
		frame_delay(1); \
	}

void singyoku_defeat_animate_and_select_route(void)
{
	defeat_animate((boss_entity_0.cur_top + (SINGYOKU_H / 2)), 1, 15, 15);

	palette_foreach(col, comp, {
		if(z_Palettes[col].v[comp] > 0) {
			// Relies on the clamping behavior of z_palette_set_show().
			// (The >0 check wouldn't even have been necessary.)
			z_Palettes[col].v[comp] = (z_Palettes[col].v[comp] - 0x4);
		}
	});
	z_Palettes[V_WHITE].set(RGB4::max(), RGB4::max(), RGB4::max());
	z_palette_set_all_show(z_Palettes);

	// Route selection
	enum {
		MAKAI_TOP = 250,
		JIGOKU_TOP = 300,
		CURSOR_LEFT = 128,
	};
	struct {
		route_t v;

		void render(vc2 col_sel, vc2 col_other) {
			z_palette_set_show(col_sel, RGB4::max(), RGB4::max(), RGB4::max());
			z_palette_set_show(col_other, 0x9, 0x9, 0x9);
		}
	} route_sel;

	page_access(1);
	z_graph_clear(); // ZUN bloat: graph_glyphrow_put() passes FX_CLEAR_BG
	graph_glyphrow_put(0, V_WHITE, ROUTE_SEL_1);
	graph_glyphrow_put(2, V_WHITE, ROUTE_SEL_2);
	graph_glyphrow_put(4, V_WHITE, ROUTE_SEL_3);
	graph_glyphrow_put(6, COL_MAKAI, ROUTE_SEL_4);
	graph_glyphrow_put(8, COL_JIGOKU, ROUTE_SEL_5);
	page_access(0);
	route_sel.render(COL_MAKAI, COL_JIGOKU);

	graph_glyphrow_2xscale_1_to_0(64, 64, 0, shiftjis_w(ROUTE_SEL_1));
	graph_glyphrow_2xscale_1_to_0(32, 96, 2, shiftjis_w(ROUTE_SEL_2));
	graph_glyphrow_2xscale_1_to_0(32, 180, 4, shiftjis_w(ROUTE_SEL_3));
	graph_glyphrow_2xscale_1_to_0(256, MAKAI_TOP, 6, shiftjis_w(ROUTE_SEL_4));
	graph_glyphrow_2xscale_1_to_0(256, JIGOKU_TOP, 8, shiftjis_w(ROUTE_SEL_5));
	graph_copy_page_to_other(0);
	page_access(0);
	ptn_put_8(CURSOR_LEFT, MAKAI_TOP, PTN_ORB);

	route_sel.v = ROUTE_MAKAI;
	input_shot = false;
	input_ok = false;
	input_reset_sense();
	bool16 holding_up = false;
	bool16 holding_down = false;

	frame_delay(50);

	while(1) {
		input_sense(false);
		if((input_up && !holding_up) || (input_down && !holding_down)) {
			if(route_sel.v == ROUTE_MAKAI) {
				egc_copy_rect_1_to_0_16(CURSOR_LEFT, MAKAI_TOP, ORB_W, ORB_H);
				ptn_put_8(CURSOR_LEFT, JIGOKU_TOP, PTN_ORB);
				route_sel.render(COL_JIGOKU, COL_MAKAI);
				route_sel.v = ROUTE_JIGOKU;
			} else {
				egc_copy_rect_1_to_0_16(CURSOR_LEFT, JIGOKU_TOP, ORB_W, ORB_H);
				ptn_put_8(CURSOR_LEFT, MAKAI_TOP, PTN_ORB);
				route_sel.render(COL_MAKAI, COL_JIGOKU);
				route_sel.v = ROUTE_MAKAI;
			}
		}
		if(!input_up) {
			holding_up = false;
		}
		if(!input_down) {
			holding_down = false;
		}
		if(input_up) {
			holding_up = true;
		}
		if(input_down) {
			holding_down = true;
		}
		if((input_shot == true) || (input_ok == true)) {
			mdrv2_se_play(4);
			break;
		}
		frame_delay(5);
	}

	resident->route = route_sel.v;
	stage_cleared = true;
	player_is_hit = true;
}

void boss_defeat_animate(void)
{
	defeat_animate((orb_cur_top + (ORB_H / 2)), 2, 7, 5);
	stage_cleared = true;
	player_is_hit = true;
}

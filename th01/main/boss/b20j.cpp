/// Jigoku Stage 20 Boss - Konngara
/// -------------------------------

extern "C" {
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/hardware/graph.h"
}

#define flash_colors	konngara_flash_colors
#define invincible	konngara_invincible
#define invincibility_frame	konngara_invincibility_frame
#define initial_hp_rendered	konngara_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

#define select_for_rank konngara_select_for_rank
#include "th01/main/select_r.cpp"

void pellet_spawnray_unput_and_put(
	screen_x_t origin_x, vram_y_t origin_y,
	screen_x_t target_x, vram_y_t target_y,
	int col
)
{
	extern screen_x_t target_prev_x;
	extern vram_y_t target_prev_y;
	if(col == 99) {
		target_prev_x = -PIXEL_NONE;
		target_prev_y = -PIXEL_NONE;
		// Umm, shouldn't we unblit in this case?
		return;
	}
	if(
		(target_prev_x != -PIXEL_NONE) && (target_prev_y != -PIXEL_NONE) &&
		(target_prev_x >= 0) && (target_prev_x < RES_X) &&
		(target_prev_y >= 0) && (target_prev_y < RES_Y)
	) {
		graph_r_line_unput(origin_x, origin_y, target_prev_x, target_prev_y);
	}
	if(
		(target_x >= 0) && (target_x < RES_X) &&
		(target_y >= 0) && (target_y < RES_Y)
	) {
		graph_r_line(origin_x, origin_y, target_x, target_y, col);
	}
	target_prev_x = target_x;
	target_prev_y = target_y;
}

char konngara_esc_mode_graph[] = "\x1B)3";
char konngara_esc_color_bg_black_fg_black[] = "\x1B[16;40m";
char konngara_esc_cursor_to_x0_y0_0[] = "\x1B[0;0H";
char konngara_space[] = " ";
char konngara_esc_mode_kanji[] = "\x1B)0";
char konngara_esc_color_reset[] = "\x1B[0m";
char konngara_esc_cursor_to_x0_y0_1[] = "\x1B[1;1H";

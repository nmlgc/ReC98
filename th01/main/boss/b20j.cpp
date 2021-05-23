/// Jigoku Stage 20 Boss - Konngara
/// -------------------------------

extern "C" {
#include "platform.h"
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

char konngara_esc_mode_graph[] = "\x1B)3";
char konngara_esc_color_bg_black_fg_black[] = "\x1B[16;40m";
char konngara_esc_cursor_to_x0_y0_0[] = "\x1B[0;0H";
char konngara_space[] = " ";
char konngara_esc_mode_kanji[] = "\x1B)0";
char konngara_esc_color_reset[] = "\x1B[0m";
char konngara_esc_cursor_to_x0_y0_1[] = "\x1B[1;1H";

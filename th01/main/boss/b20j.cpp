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

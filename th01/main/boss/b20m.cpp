/// Makai Stage 20 Boss - Sariel
/// ----------------------------

extern "C" {
#include "platform.h"
#include "th01/main/vars.hpp"
}

#define flash_colors	sariel_flash_colors
#define invincible	sariel_invincible
#define invincibility_frame	sariel_invincibility_frame
#define initial_hp_rendered	sariel_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

#define select_for_rank sariel_select_for_rank
#include "th01/main/select_r.cpp"

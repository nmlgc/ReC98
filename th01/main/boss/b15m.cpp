/// Makai Stage 15 Boss - Elis
/// --------------------------

extern "C" {
#include "platform.h"
}

#define flash_colors	elis_flash_colors
#define invincibility_frame	elis_invincibility_frame
#define invincible	elis_invincible
#define initial_hp_rendered	elis_initial_hp_rendered
extern int invincibility_frame;
extern bool16 invincible;
extern bool initial_hp_rendered;

#define select_for_rank elis_select_for_rank
#include "th01/main/select_r.cpp"

/// Makai Stage 10 Boss - YuugenMagan
/// ---------------------------------

extern "C" {
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/main/vars.hpp"
#include "th01/formats/ptn.hpp"
}

#define flash_colors	yuugenmagan_flash_colors
#define invincible	yuugenmagan_invincible
#define invincibility_frame	yuugenmagan_invincibility_frame
#define initial_hp_rendered	yuugenmagan_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

// Entities
// --------

static const main_ptn_slot_t PTN_SLOT_MISSILE = PTN_SLOT_BOSS_1;
// --------

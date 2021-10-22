/// Jigoku Stage 10 Boss - Mima
/// ---------------------------

extern "C" {
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/main/vars.hpp"
#include "th01/formats/ptn.hpp"
}

#define flash_colors	mima_flash_colors
#define invincibility_frame	mima_invincibility_frame
#define invincible	mima_invincible
#define initial_hp_rendered	mima_initial_hp_rendered
extern int invincibility_frame;
extern bool16 invincible;
extern bool initial_hp_rendered;

// Entities
// --------

static const main_ptn_slot_t PTN_SLOT_BG_ENT = PTN_SLOT_BOSS_1;
static const main_ptn_slot_t PTN_SLOT_MISSILE = PTN_SLOT_BOSS_2;
// --------

#define select_for_rank mima_select_for_rank
#include "th01/main/select_r.cpp"

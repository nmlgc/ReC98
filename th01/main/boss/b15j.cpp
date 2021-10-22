/// Jigoku Stage 15 Boss - Kikuri
/// -----------------------------

#include "th01/main/boss/palette.cpp"

extern "C" {
#include "planar.h"
#include "th01/formats/ptn.hpp"
}
#include "th01/main/vars.hpp"

#define flash_colors	kikuri_flash_colors
#define invincible	kikuri_invincible
#define invincibility_frame	kikuri_invincibility_frame
#define initial_hp_rendered	kikuri_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

// Entities (and animations)
// --------

static const main_ptn_slot_t PTN_SLOT_WAVE = PTN_SLOT_BOSS_1;
// --------

#define select_for_rank kikuri_select_for_rank
#include "th01/main/select_r.cpp"

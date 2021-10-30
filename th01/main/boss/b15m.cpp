/// Makai Stage 15 Boss - Elis
/// --------------------------

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/math/area.hpp"
#include "th01/formats/pf.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/main/vars.hpp"
#include "th01/main/boss/entity_a.hpp"
}
#include "th01/main/boss/boss.hpp"

#define flash_colors	elis_flash_colors
#define invincibility_frame	elis_invincibility_frame
#define invincible	elis_invincible
#define initial_hp_rendered	elis_initial_hp_rendered
extern int invincibility_frame;
extern bool16 invincible;
extern bool initial_hp_rendered;

// Entities
// --------

static const main_ptn_slot_t PTN_SLOT_BG_ENT = PTN_SLOT_BOSS_1;
static const main_ptn_slot_t PTN_SLOT_MISSILE = PTN_SLOT_BOSS_2;
// --------

void girl_bg_snap(int unncessary_parameter_that_still_needs_to_be_1_or_2)
;

void girl_bg_put(int unncessary_parameter_that_still_needs_to_be_1_or_2)
;

#define select_for_rank elis_select_for_rank
#include "th01/main/select_r.cpp"

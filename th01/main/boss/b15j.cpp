/// Jigoku Stage 15 Boss - Kikuri
/// -----------------------------

#include "th01/main/boss/palette.cpp"

extern "C" {
#include "planar.h"
#include "th01/formats/ptn.hpp"
}
#include "th01/main/vars.hpp"

// Entities
// --------

static const int TEAR_COUNT = 10;

#define tear_anim_frame	kikuri_tear_anim_frame
// Nonzero values are also used to indicate whether a given tear is alive.
extern int8_t tear_anim_frame[TEAR_COUNT];
// --------

#define flash_colors	kikuri_flash_colors
#define invincible	kikuri_invincible
#define invincibility_frame	kikuri_invincibility_frame
#define initial_hp_rendered	kikuri_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

// .PTN
// ----

static const main_ptn_slot_t PTN_SLOT_WAVE = PTN_SLOT_BOSS_1;
// ----

// Patterns
// --------

#define pattern_state	kikuri_pattern_state
extern union {
	int interval;
	int speed_multiplied_by_8;
} pattern_state;
// --------

#define select_for_rank kikuri_select_for_rank
#include "th01/main/select_r.cpp"

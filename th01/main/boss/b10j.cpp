/// Jigoku Stage 10 Boss - Mima
/// ---------------------------

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

#define flash_colors	mima_flash_colors
#define invincibility_frame	mima_invincibility_frame
#define invincible	mima_invincible
#define initial_hp_rendered	mima_initial_hp_rendered
extern int invincibility_frame;
extern bool16 invincible;
extern bool initial_hp_rendered;

// Entities
// --------

#define ent_still	boss_entities[0]
#define ent_anim 	boss_entities[1]

static const main_ptn_slot_t PTN_SLOT_BG_ENT = PTN_SLOT_BOSS_1;
static const main_ptn_slot_t PTN_SLOT_MISSILE = PTN_SLOT_BOSS_2;

static inline void ent_free(void) {
	bos_entity_free(0);
	bos_entity_free(1);
	ptn_free(PTN_SLOT_BG_ENT);
	ptn_free(PTN_SLOT_MISSILE);
}
// --------

void mima_free(void)
{
	ent_free();
}

#define select_for_rank mima_select_for_rank
#include "th01/main/select_r.cpp"

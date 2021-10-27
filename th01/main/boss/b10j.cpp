/// Jigoku Stage 10 Boss - Mima
/// ---------------------------

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/hardware/palette.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/vars.hpp"
#include "th01/main/boss/entity_a.hpp"
}
#include "th01/main/particle.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/hud/hp.hpp"

// Coordinates
// -----------

static const pixel_t MIMA_W = 128;
static const pixel_t MIMA_H = 160;
// -----------

#define flash_colors	mima_flash_colors
#define invincibility_frame	mima_invincibility_frame
#define invincible	mima_invincible
#define initial_hp_rendered	mima_initial_hp_rendered
extern int invincibility_frame;
extern bool16 invincible;
extern bool initial_hp_rendered;

// Entities
// --------

enum anim_cel_t {
	C_CAST = 0,
	C_METEOR = 1,
};

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

void mima_setup(void)
{
	boss_palette_snap();
	ent_still.bos_image = 0;
	ent_anim.bos_image = C_METEOR;
	z_palette_white_in();
	ent_still.pos_set(
		(PLAYFIELD_CENTER_X - (MIMA_W / 2)), PLAYFIELD_TOP, 48,
		PLAYFIELD_LEFT, (PLAYFIELD_RIGHT + ((MIMA_W / 4) * 3)),
		PLAYFIELD_TOP, (PLAYFIELD_BOTTOM - ((MIMA_H / 5) * 3))
	);
	ent_still.hitbox_set(
		((MIMA_W / 4) * 1), ((MIMA_H / 5) * 1),
		((MIMA_W / 4) * 3), ((MIMA_H / 5) * 4)
	);
	ent_still.hitbox_orb_inactive = false;
	boss_phase_frame = 0;
	boss_phase = 0;
	boss_hp = 12;
	hud_hp_first_white = 6;
	hud_hp_first_redwhite = 2;
	particles_unput_update_render(PO_INITIALIZE, V_WHITE);
}

void mima_free(void)
{
	ent_free();
}

#define select_for_rank mima_select_for_rank
#include "th01/main/select_r.cpp"

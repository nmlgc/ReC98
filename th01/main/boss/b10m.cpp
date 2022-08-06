/// Makai Stage 10 Boss - YuugenMagan
/// ---------------------------------

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/hardware/palette.h"
#include "th01/shiftjis/fns.hpp"
#undef MISSILE_FN
#define MISSILE_FN boss3_m_ptn
extern const char MISSILE_FN[];
#include "th01/main/vars.hpp"
#include "th01/formats/grp.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/main/particle.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/missile.hpp"
#include "th01/main/hud/hp.hpp"

#define flash_colors	yuugenmagan_flash_colors
#define invincible	yuugenmagan_invincible
#define invincibility_frame	yuugenmagan_invincibility_frame
#define initial_hp_rendered	yuugenmagan_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

// Always denotes the last phase that ends with that amount of HP.
enum yuugenmagan_hp_t {
	HP_TOTAL = 16,
	PHASE_3_END_HP = 12,
	PHASE_7_END_HP = 8,
};

// Entities
// --------

static const int EYE_COUNT = 5;

static const pixel_t EYE_W = 64;
static const pixel_t EYE_H = 48;

enum yuugenmagan_cel_t {
	C_HIDDEN = 0,
};

#define eye_west \
	reinterpret_cast<CBossEntitySized<EYE_W, EYE_H> &>(boss_entity_0)
#define eye_east \
	reinterpret_cast<CBossEntitySized<EYE_W, EYE_H> &>(boss_entity_1)
#define eye_southwest \
	reinterpret_cast<CBossEntitySized<EYE_W, EYE_H> &>(boss_entity_2)
#define eye_southeast \
	reinterpret_cast<CBossEntitySized<EYE_W, EYE_H> &>(boss_entity_3)
#define eye_north \
	reinterpret_cast<CBossEntitySized<EYE_W, EYE_H> &>(boss_entity_4)

inline void yuugenmagan_ent_load(void) {
	extern const char boss2_bos[];
	eye_west.load(boss2_bos, 0);
	eye_east.metadata_assign(eye_west);
	eye_southwest.metadata_assign(eye_west);
	eye_southeast.metadata_assign(eye_west);
	eye_north.metadata_assign(eye_west);
}
// --------

// .PTN
// ----

static const main_ptn_slot_t PTN_SLOT_MISSILE = PTN_SLOT_BOSS_1;
// ----

void yuugenmagan_load(void)
{
	yuugenmagan_ent_load();
	void yuugenmagan_setup(void);
	yuugenmagan_setup();
	Missiles.load(PTN_SLOT_MISSILE);
	Missiles.reset();
}

void yuugenmagan_setup(void)
{
	extern const char boss2_grp[];
	int col;
	int comp;

	grp_palette_load_show(boss2_grp);
	boss_palette_snap();

	eye_west     .set_image(C_HIDDEN);
	eye_east     .set_image(C_HIDDEN);
	eye_southwest.set_image(C_HIDDEN);
	eye_southeast.set_image(C_HIDDEN);
	eye_north    .set_image(C_HIDDEN);

	palette_copy(boss_post_defeat_palette, z_Palettes, col, comp);

	// These exactly correspond to the yellow boxes in BOSS2.GRP.
	eye_west     .pos_set( 64, 128);
	eye_east     .pos_set(512, 128);
	eye_southwest.pos_set(192, 176);
	eye_southeast.pos_set(384, 176);
	eye_north    .pos_set(288,  64);

	eye_west     .hitbox_orb_set(-4, -4, (EYE_W + 4), EYE_H);
	eye_east     .hitbox_orb_set(-4, -4, (EYE_W + 4), EYE_H);
	eye_southwest.hitbox_orb_set(-4, -4, (EYE_W + 4), EYE_H);
	eye_southeast.hitbox_orb_set(-4, -4, (EYE_W + 4), EYE_H);
	eye_north    .hitbox_orb_set(-4, -4, (EYE_W + 4), EYE_H);
	eye_west     .hitbox_orb_inactive = true;
	eye_east     .hitbox_orb_inactive = true;
	eye_southwest.hitbox_orb_inactive = true;
	eye_southeast.hitbox_orb_inactive = true;
	eye_north    .hitbox_orb_inactive = true;

	boss_phase_frame = 0;
	boss_phase = 0;
	boss_hp = HP_TOTAL;
	hud_hp_first_white = PHASE_3_END_HP;
	hud_hp_first_redwhite = PHASE_7_END_HP;

	// (redundant, no particles are shown in this fight)
	particles_unput_update_render(PO_INITIALIZE, V_WHITE);
}

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
extern "C" {
#include "th01/formats/grp.h"
}
#include "th01/formats/pf.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/main/particle.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/missile.hpp"
#include "th01/main/hud/hp.hpp"
#include "th01/main/player/orb.hpp"

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

static const pixel_t EYE_HITBOX_LEFT = (-4 + ORB_HITBOX_W);
static const pixel_t EYE_HITBOX_TOP = (-4 + ORB_HITBOX_W);
static const pixel_t EYE_HITBOX_RIGHT = (EYE_W + 4 - ORB_HITBOX_W);
static const pixel_t EYE_HITBOX_BOTTOM = (EYE_H - ORB_HITBOX_H);

enum yuugenmagan_cel_t {
	C_HIDDEN = 0,
};

enum yuugenmagan_eye_t {
	E_WEST = 0,
	E_EAST = 1,
	E_SOUTHWEST = 2,
	E_SOUTHEAST = 3,
	E_NORTH = 4,
};

#define eyes reinterpret_cast<CBossEntitySized<EYE_W, EYE_H> *>(boss_entities)

inline void yuugenmagan_ent_load(void) {
	extern const char boss2_bos[];
	eyes[0].load(boss2_bos, 0);
	eyes[1].metadata_assign(eyes[0]);
	eyes[2].metadata_assign(eyes[0]);
	eyes[3].metadata_assign(eyes[0]);
	eyes[4].metadata_assign(eyes[0]);
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

	// MODDERS: Loop over all eyes instead.
	eyes[0].set_image(C_HIDDEN);
	eyes[1].set_image(C_HIDDEN);
	eyes[2].set_image(C_HIDDEN);
	eyes[3].set_image(C_HIDDEN);
	eyes[4].set_image(C_HIDDEN);

	palette_copy(boss_post_defeat_palette, z_Palettes, col, comp);

	// These exactly correspond to the yellow boxes in BOSS2.GRP.
	eyes[     E_WEST].pos_set( 64, 128);
	eyes[     E_EAST].pos_set(512, 128);
	eyes[E_SOUTHWEST].pos_set(192, 176);
	eyes[E_SOUTHEAST].pos_set(384, 176);
	eyes[    E_NORTH].pos_set(288,  64);

	// MODDERS: Loop over all eyes instead.
	eyes[0].hitbox_set(
		EYE_HITBOX_LEFT, EYE_HITBOX_TOP, EYE_HITBOX_RIGHT, EYE_HITBOX_BOTTOM
	);
	eyes[1].hitbox_set(
		EYE_HITBOX_LEFT, EYE_HITBOX_TOP, EYE_HITBOX_RIGHT, EYE_HITBOX_BOTTOM
	);
	eyes[2].hitbox_set(
		EYE_HITBOX_LEFT, EYE_HITBOX_TOP, EYE_HITBOX_RIGHT, EYE_HITBOX_BOTTOM
	);
	eyes[3].hitbox_set(
		EYE_HITBOX_LEFT, EYE_HITBOX_TOP, EYE_HITBOX_RIGHT, EYE_HITBOX_BOTTOM
	);
	eyes[4].hitbox_set(
		EYE_HITBOX_LEFT, EYE_HITBOX_TOP, EYE_HITBOX_RIGHT, EYE_HITBOX_BOTTOM
	);
	eyes[0].hitbox_orb_inactive = true;
	eyes[1].hitbox_orb_inactive = true;
	eyes[2].hitbox_orb_inactive = true;
	eyes[3].hitbox_orb_inactive = true;
	eyes[4].hitbox_orb_inactive = true;

	boss_phase_frame = 0;
	boss_phase = 0;
	boss_hp = HP_TOTAL;
	hud_hp_first_white = PHASE_3_END_HP;
	hud_hp_first_redwhite = PHASE_7_END_HP;

	// (redundant, no particles are shown in this fight)
	particles_unput_update_render(PO_INITIALIZE, V_WHITE);
}

/// Makai Stage 10 Boss - YuugenMagan
/// ---------------------------------

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/overlap.hpp"
#include "th01/math/subpixel.hpp"
extern "C" {
#include "th01/hardware/graph.h"
}
#include "th01/hardware/input.hpp"
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
#include "th01/main/player/player.hpp"

// Coordinates
// -----------

static const pixel_t EYE_W = 64;
static const pixel_t EYE_H = 48;

static const pixel_t EYE_LATERAL_CENTER_DISTANCE_X = 224;
static const pixel_t EYE_SOUTH_CENTER_DISTANCE_X = 96;
static const pixel_t EYE_NORTH_LATERAL_DISTANCE_Y = 64;
static const pixel_t EYE_LATERAL_SOUTH_DISTANCE_Y = 48;

static const screen_x_t EYE_WEST_LEFT = (
	PLAYFIELD_CENTER_X - EYE_LATERAL_CENTER_DISTANCE_X - (EYE_W / 2)
);

static const screen_x_t EYE_EAST_LEFT = (
	PLAYFIELD_CENTER_X + EYE_LATERAL_CENTER_DISTANCE_X - (EYE_W / 2)
);

static const screen_x_t EYE_SOUTHWEST_LEFT = (
	PLAYFIELD_CENTER_X - EYE_SOUTH_CENTER_DISTANCE_X - (EYE_W / 2)
);

static const screen_x_t EYE_SOUTHEAST_LEFT = (
	PLAYFIELD_CENTER_X + EYE_SOUTH_CENTER_DISTANCE_X - (EYE_W / 2)
);

static const screen_x_t EYE_NORTH_LEFT = (PLAYFIELD_CENTER_X - (EYE_W / 2));

static const screen_y_t EYE_NORTH_TOP = PLAYFIELD_TOP;
static const screen_y_t EYE_LATERAL_TOP = (
	EYE_NORTH_TOP + EYE_NORTH_LATERAL_DISTANCE_Y
);
static const screen_y_t EYE_SOUTH_TOP = (
	EYE_LATERAL_TOP + EYE_LATERAL_SOUTH_DISTANCE_Y
);
// -----------

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

enum eye_cel_t {
	C_HIDDEN = 0,
	C_CLOSED = 1,
	C_HALFOPEN = 2,
	C_DOWN = 3,
	C_LEFT = 4,
	C_RIGHT = 5,
	C_AHEAD = 6,
};

struct CEyeEntity : public CBossEntitySized<EYE_W, EYE_H> {
	// Relative pupil and iris coordinates
	// -----------------------------------
	// These only apply to the player-facing cels (C_DOWN, C_LEFT, and C_RIGHT).

	// ZUN quirk: Doesn't really correspond to any precise feature of any eye
	// cel. The best match is the center of the iris on C_DOWN, but even that
	// would be off by 1 pixel – not to mention very wrong for every other cel.
	screen_x_t offcenter_x(void) const {
		return (cur_center_x() - 4);
	}

	// Correct for C_LEFT and C_RIGHT, off by 1 pixel for C_DOWN.
	screen_y_t iris_top(void) const {
		return (cur_center_y() + 4);
	}
	// -----------------------------------

	void downwards_laser_put(void) const {
		graph_r_vline(
			offcenter_x(), iris_top(), (PLAYFIELD_BOTTOM - 2), V_WHITE
		);
	}
};

#define eye_west     	reinterpret_cast<CEyeEntity &>(boss_entity_0)
#define eye_east     	reinterpret_cast<CEyeEntity &>(boss_entity_1)
#define eye_southwest	reinterpret_cast<CEyeEntity &>(boss_entity_2)
#define eye_southeast	reinterpret_cast<CEyeEntity &>(boss_entity_3)
#define eye_north    	reinterpret_cast<CEyeEntity &>(boss_entity_4)

inline void yuugenmagan_ent_load(void) {
	extern const char boss2_bos[];
	eye_west.load(boss2_bos, 0);
	eye_east.metadata_assign(eye_west);
	eye_southwest.metadata_assign(eye_west);
	eye_southeast.metadata_assign(eye_west);
	eye_north.metadata_assign(eye_west);
}

inline void yuugenmagan_ent_free(void) {
	bos_entity_free(0);
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
	eye_west     .pos_set(     EYE_WEST_LEFT, EYE_LATERAL_TOP);
	eye_east     .pos_set(     EYE_EAST_LEFT, EYE_LATERAL_TOP);
	eye_southwest.pos_set(EYE_SOUTHWEST_LEFT, EYE_SOUTH_TOP);
	eye_southeast.pos_set(EYE_SOUTHEAST_LEFT, EYE_SOUTH_TOP);
	eye_north    .pos_set(    EYE_NORTH_LEFT, EYE_NORTH_TOP);

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

void unused_formula(int a, int b, int& ret)
{
	double delta = (b - a);
	ret = ((delta * isqrt(3)) / 2.0f);
}

void yuugenmagan_free(void)
{
	yuugenmagan_ent_free();
	ptn_free(PTN_SLOT_MISSILE);
}

// Phases
// ------

static const int EYE_OPENING_FRAMES = 60;

enum phase_0_keyframe_t {
	KEYFRAME_LATERAL_OPENING = 100,
	KEYFRAME_SOUTH_OPENING = 120,
	KEYFRAME_NORTH_OPENING = 140,
	KEYFRAME_LATERAL_OPEN = (KEYFRAME_LATERAL_OPENING + EYE_OPENING_FRAMES),
	KEYFRAME_SOUTH_OPEN = (KEYFRAME_SOUTH_OPENING + EYE_OPENING_FRAMES),
	KEYFRAME_NORTH_OPEN = (KEYFRAME_NORTH_OPENING + EYE_OPENING_FRAMES),

	KEYFRAME_CLOSING = 240,
	KEYFRAME_CLOSED = 260,
	KEYFRAME_HIDDEN = 280,
	KEYFRAME_LATERAL_LASER_DONE = 300,
	KEYFRAME_SOUTH_LASER_DONE = 320,
	KEYFRAME_NORTH_LASER_DONE = 330,
};

void phase_0_downwards_lasers(void)
{
	#define laser_hittest(eye, player_w) ( \
		overlap_low_center_lt_gt( \
			player_left, player_w, eye.offcenter_x(), (EYE_W - (EYE_W / 4)) \
		) \
	)

	if(boss_phase_frame > KEYFRAME_LATERAL_OPEN) {
		if(boss_phase_frame < KEYFRAME_LATERAL_LASER_DONE) {
			eye_west.downwards_laser_put();
			eye_east.downwards_laser_put();

			// ZUN quirk: The hitbox for the rightmost eye is much larger than
			// the other ones?!
			if(
				laser_hittest(eye_west, PLAYER_W) ||
				laser_hittest(eye_east, (PLAYER_W / 4))
			) {
				done = true;
			}
		}
		if(boss_phase_frame > KEYFRAME_SOUTH_OPEN) {
			if(boss_phase_frame < KEYFRAME_SOUTH_LASER_DONE) {
				eye_southwest.downwards_laser_put();
				eye_southeast.downwards_laser_put();
				if(
					laser_hittest(eye_southwest, PLAYER_W) ||
					laser_hittest(eye_southeast, PLAYER_W)
				) {
					done = true;
				}
			}
			if(boss_phase_frame > KEYFRAME_NORTH_OPEN) {
				eye_north.downwards_laser_put();
				if(laser_hittest(eye_north, PLAYER_W)) {
					done = true;
				}
			}
		}
	}
	if(player_invincible) {
		done = false;
	}

	#undef laser_hittest
}
// ------

/// Makai Stage 10 Boss - YuugenMagan
/// ---------------------------------

#include <stdlib.h>
#include "platform.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/dir.hpp"
#include "th01/math/overlap.hpp"
#include "th01/math/polar.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/palette.h"
#include "th01/snd/mdrv2.h"
#include "th01/formats/grp.h"
#include "th01/formats/ptn.hpp"
#include "th01/sprites/pellet.h"
#include "th01/main/entity.hpp"
#include "th01/main/particle.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/boss/defeat.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/laser_s.hpp"
#include "th01/main/bullet/line.hpp"
#include "th01/main/bullet/missile.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/hud/hp.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/stage/palette.hpp"
#include "th01/main/stage/stages.hpp"

// Coordinates
// -----------

static const pixel_t EYE_W = 64;
static const pixel_t EYE_H = 48;
static const pixel_t PUPIL_H = 12;
static const pixel_t IRIS_H = 7;

static const pixel_t EYE_LATERAL_CENTER_DISTANCE_X = 224;
static const pixel_t EYE_SOUTH_CENTER_DISTANCE_X = 96;
static const pixel_t EYE_NORTH_LATERAL_DISTANCE_Y = 64;
static const pixel_t EYE_LATERAL_SOUTH_DISTANCE_Y = 48;

// Center of the kimono figure
static const screen_y_t PENTAGRAM_REGULAR_CENTER_Y = 189;

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

enum yuugenmagan_colors_t {
	COL_YOKOSHIMA = 15, // The big 邪 in the background
};

// Always denotes the last phase that ends with that amount of HP.
enum yuugenmagan_hp_t {
	HP_TOTAL = 16,
	HP_PHASE_1_END = 15,
	HP_PHASE_3_END = 12,
	HP_PHASE_5_END = 10,
	HP_PHASE_7_END = 8,
	HP_PHASE_9_END = 2,
	HP_PHASE_13_END = 0,
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

// Eye flags
typedef int8_t eye_flag_t;

// Code generation wants 16-bit constants, unfortunately
static const int EF_NONE = 0;
static const int EF_WEST = (1 << 0);
static const int EF_EAST = (1 << 1);
static const int EF_SOUTHWEST = (1 << 2);
static const int EF_SOUTHEAST = (1 << 3);
static const int EF_NORTH = (1 << 4);
static const int EF_RESET = (1 << 5);

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

	// Correct for C_LEFT and C_RIGHT, off by 1 pixel for C_DOWN.
	screen_y_t iris_center_y(void) const {
		return (iris_top() + (IRIS_H / 2) + 1);
	}

	// Correct for C_LEFT and C_RIGHT, off by 1 pixel for C_DOWN.
	screen_y_t pupil_bottom(void) const {
		return (cur_center_y() + PUPIL_H);
	}
	// -----------------------------------

	void track_player(void) {
		if((cur_center_x() - player_left) > (EYE_W / 2)) {
			set_image(C_LEFT);
		} else if((player_left - cur_center_x()) > (EYE_W / 2)) {
			set_image(C_RIGHT);
		} else {
			set_image(C_DOWN);
		}
	}

	void downwards_laser_put(void) const {
		graph_r_vline(
			offcenter_x(), iris_top(), (PLAYFIELD_BOTTOM - 2), V_WHITE
		);
	}

	void downwards_laser_unput(void) const {
		graph_r_line_unput(
			offcenter_x(), iris_top(), offcenter_x(), PLAYFIELD_BOTTOM
		);
	}

	void fire_from_iris_center(pellet_group_t group, float speed_base) const {
		Pellets.add_group(
			(cur_center_x()  - (PELLET_W / 2)),
			(iris_center_y() - (PELLET_H / 2)),
			group,
			to_sp(speed_base)
		);
	}

	void fire_from_bottom_center(pellet_group_t group, float speed_base) const {
		Pellets.add_group(
			(cur_center_x() - (PELLET_W / 2)),
			(pupil_bottom() - (PELLET_H / 2)),
			group,
			to_sp(speed_base)
		);
	}

	void fire_from_bottom_center(
		bool mirror_angle_horizontally,
		const unsigned char &angle,
		float speed_base,
		pellet_motion_t motion_type = PM_REGULAR,
		float speed_for_motion_fixed = 0.0f
	) const {
		Pellets.add_single(
			(cur_center_x() - (PELLET_W / 2)),
			(pupil_bottom() - (PELLET_H / 2)),
			(mirror_angle_horizontally ? (0x80 - angle) : angle),
			to_sp(speed_base),
			motion_type,
			to_sp(speed_for_motion_fixed)
		);
	}
};

#define eye_west     	reinterpret_cast<CEyeEntity &>(boss_entity_0)
#define eye_east     	reinterpret_cast<CEyeEntity &>(boss_entity_1)
#define eye_southwest	reinterpret_cast<CEyeEntity &>(boss_entity_2)
#define eye_southeast	reinterpret_cast<CEyeEntity &>(boss_entity_3)
#define eye_north    	reinterpret_cast<CEyeEntity &>(boss_entity_4)

// For [eye_predicate], pass a macro that takes a single eye_flag_t parameter.
#define eyes_foreach_if(eye_predicate, method) { \
	if(eye_predicate(     EF_WEST)) {      eye_west.method(); } \
	if(eye_predicate(     EF_EAST)) {      eye_east.method(); } \
	if(eye_predicate(EF_SOUTHWEST)) { eye_southwest.method(); } \
	if(eye_predicate(EF_SOUTHEAST)) { eye_southeast.method(); } \
	if(eye_predicate(    EF_NORTH)) {     eye_north.method(); } \
}

inline void eyes_locked_unput_and_put_then_track(eye_flag_t eye_flag) {
	#define eye_flag_is_set(bit) ( \
		eye_flag & bit \
	)

	// Unblitting/rendering first, and *then* tracking? Depending on when the
	// eye's cel is updated within the entity's lock, this order introduces a
	// variable tracking latency from 1 to 4 frames. Which isn't all too bad,
	// and might even be considered somewhat realistic. Certainly not ZUN quirk
	// territory.
	eyes_foreach_if(eye_flag_is_set, locked_unput_and_put_8);
	eyes_foreach_if(eye_flag_is_set, track_player);

	#undef eye_flag_is_set
}

#define eyes_set_image(eye_flag, cel) { \
	if(eye_flag &      EF_WEST) {      eye_west.set_image(cel); } \
	if(eye_flag &      EF_EAST) {      eye_east.set_image(cel); } \
	if(eye_flag & EF_SOUTHWEST) { eye_southwest.set_image(cel); } \
	if(eye_flag & EF_SOUTHEAST) { eye_southeast.set_image(cel); } \
	if(eye_flag &     EF_NORTH) {     eye_north.set_image(cel); } \
}

inline void yuugenmagan_ent_load(void) {
	eye_west.load("boss2.bos", 0);
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

// Patterns
// --------

// Yes! Finally a proper stateless version of this concept!
inline int select_for_rank(
	int for_easy, int for_normal, int for_hard, int for_lunatic
) {
	return (
		(rank == RANK_EASY) ? for_easy :
		(rank == RANK_NORMAL) ? for_normal :
		(rank == RANK_HARD) ? for_hard :
		(rank == RANK_LUNATIC) ? for_lunatic :
		for_normal
	);
}

static int pattern_interval;
// --------

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
	int col;
	int comp;

	grp_palette_load_show("boss2.grp");
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
	eye_west     .hitbox_orb_deactivate();
	eye_east     .hitbox_orb_deactivate();
	eye_southwest.hitbox_orb_deactivate();
	eye_southeast.hitbox_orb_deactivate();
	eye_north    .hitbox_orb_deactivate();

	boss_phase_frame = 0;
	boss_phase = 0;
	boss_hp = HP_TOTAL;
	hud_hp_first_white = HP_PHASE_3_END;
	hud_hp_first_redwhite = HP_PHASE_7_END;

	// ZUN bloat: Redundant, no particles are shown in this fight.
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
static const int EYE_TOGGLE_FRAMES = (EYE_OPENING_FRAMES + 10);
static const int SUBPHASE_PREPARE_FRAMES = 100;
static const int SUBPHASE_TIMEOUT_FRAMES = 200;

enum phase_0_keyframe_t {
	KEYFRAME_LATERAL_OPENING = SUBPHASE_PREPARE_FRAMES,
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

// Matches the animation in eyes_toggle_and_yokoshima_recolor().
inline void phase_0_eye_open(CEyeEntity& eye, int frame, int frame_first) {
	eye.set_image(
		((frame - frame_first) < ((EYE_OPENING_FRAMES / 3) * 1)) ? C_CLOSED :
		((frame - frame_first) < ((EYE_OPENING_FRAMES / 3) * 2)) ? C_HALFOPEN :
		((frame - frame_first) < ((EYE_OPENING_FRAMES / 3) * 3)) ? C_AHEAD :
		/*                                                      */ C_DOWN
	);
}

inline void phase_0_eye_close(CEyeEntity& eye, int frame) {
	eye.set_image(
		(frame == KEYFRAME_CLOSING) ? C_HALFOPEN :
		(frame == KEYFRAME_CLOSED) ? C_CLOSED : C_HIDDEN
	);
}

inline void phase_0_eyes_open(int frame) {
	if(
		(frame >= KEYFRAME_LATERAL_OPENING) &&
		(frame <= KEYFRAME_LATERAL_OPEN)
	) {
		phase_0_eye_open(eye_west, frame, KEYFRAME_LATERAL_OPENING);
		phase_0_eye_open(eye_east, frame, KEYFRAME_LATERAL_OPENING);
	}
	if((frame >= KEYFRAME_SOUTH_OPENING) && (frame <= KEYFRAME_SOUTH_OPEN)) {
		phase_0_eye_open(eye_southwest, frame, KEYFRAME_SOUTH_OPENING);
		phase_0_eye_open(eye_southeast, frame, KEYFRAME_SOUTH_OPENING);
	}
	if((frame >= KEYFRAME_NORTH_OPENING) && (frame <= KEYFRAME_NORTH_OPEN)) {
		phase_0_eye_open(eye_north, frame, KEYFRAME_NORTH_OPENING);
	}
}

inline void phase_0_eyes_close(int frame) {
	phase_0_eye_close(eye_west, frame);
	phase_0_eye_close(eye_east, frame);
	phase_0_eye_close(eye_southwest, frame);
	phase_0_eye_close(eye_southeast, frame);
	phase_0_eye_close(eye_north, frame);
}

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
				player_is_hit = true;
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
					player_is_hit = true;
				}
			}
			if(boss_phase_frame > KEYFRAME_NORTH_OPEN) {
				eye_north.downwards_laser_put();
				if(laser_hittest(eye_north, PLAYER_W)) {
					player_is_hit = true;
				}
			}
		}
	}
	if(player_invincible) {
		player_is_hit = false;
	}

	#undef laser_hittest
}

inline void phase_0_fire(CEyeEntity& eye) {
	eye.fire_from_iris_center(PG_5_SPREAD_WIDE_AIMED, 3.375f);
}

inline void fire_from_lateral(pellet_group_t group, float speed_base) {
	eye_west.fire_from_bottom_center(group, speed_base);
	eye_east.fire_from_bottom_center(group, speed_base);
}

void phase_1_pellets_from_lateral()
{
	if((boss_phase_frame % pattern_interval) == 10) {
		fire_from_lateral(PG_2_SPREAD_WIDE_AIMED, 1.5f);
	} else if((boss_phase_frame % pattern_interval) == 25) {
		fire_from_lateral(PG_2_SPREAD_WIDE_AIMED, 1.75f);
	} else if((boss_phase_frame % pattern_interval) == 40) {
		fire_from_lateral(PG_2_SPREAD_WIDE_AIMED, 2.0f);
	} else if((boss_phase_frame % pattern_interval) == 60) {
		fire_from_lateral(PG_2_SPREAD_WIDE_AIMED, 2.75f);
	} else if((boss_phase_frame % pattern_interval) == 80) {
		fire_from_lateral(PG_2_SPREAD_WIDE_AIMED, 3.125f);
	} else if((boss_phase_frame % pattern_interval) == 110) {
		fire_from_lateral(PG_1_AIMED, 4.25f);
	}
}
// ------

// Aimed missiles
// --------------

static const int MISSILE_INTERVAL = 8;

// The original code generation of missile_angle() combines all constant parts
// into a single immediate argument, so these can't be defined in terms of
// CEyeEntity's cur_center_x() and cur_center_y() helpers.

// (cur_center_x() + 4) kind of corresponds to the right edge of C_DOWN.
static const pixel_t MISSILE_OFFSET_LEFT = ((EYE_W / 2) + 4 - (MISSILE_W / 2));

// (pupil_bottom() - (MISSILE_H / 2))
static const pixel_t MISSILE_OFFSET_TOP = (
	(EYE_H / 2) + PUPIL_H - (MISSILE_H / 2)
);

inline unsigned char missile_angle(
	const CEyeEntity& eye, const screen_x_t& target_x
) {
	return iatan2(
		(player_bottom() - eye.cur_top  + MISSILE_OFFSET_TOP),
		(target_x        - eye.cur_left + MISSILE_OFFSET_LEFT)
	);
}

void pascal near fire_missile_pair_from_south(
	unsigned char angle_for_southwest, unsigned char angle_for_southeast
)
{
	point_t velocity;

	vector2(velocity.x, velocity.y, 8, angle_for_southwest);
	Missiles.add(
		(eye_southwest.cur_left + MISSILE_OFFSET_LEFT),
		(eye_southwest.cur_top  + MISSILE_OFFSET_TOP),
		velocity.x,
		velocity.y
	);
	vector2(velocity.x, velocity.y, 8, angle_for_southeast);
	Missiles.add(
		(eye_southeast.cur_left + MISSILE_OFFSET_LEFT),
		(eye_southeast.cur_top  + MISSILE_OFFSET_TOP),
		velocity.x,
		velocity.y
	);
}

enum missile_subphase_t {
	MSP_PREPARE = 0,
	MSP_AIM_AND_FIRE_AROUND = 1,
	MSP_SHIFT_ANGLE_1 = 2,
	MSP_SHIFT_ANGLE_2 = 3,
	MSP_COUNT = 4,
};

#define missile_subphase_variation(variation, msp) ( \
	(variation * MSP_COUNT) + msp \
)

// MODDERS: Simply replace with ((subphase / MSP_COUNT) == variation).
#define missile_subphase_variation_is( \
	subphase, variation, msp, variations_max \
) ( \
	(variations_max >= (variation + 1)) && \
	(subphase == missile_subphase_variation(variation, msp)) \
)

// MODDERS: Simply replace with ((subphase % MSP_COUNT) == msp).
#define missile_subphase_is(subphase, msp, variations_max) ( \
	missile_subphase_variation_is(subphase, 0, msp, variations_max) || \
	missile_subphase_variation_is(subphase, 1, msp, variations_max) || \
	missile_subphase_variation_is(subphase, 2, msp, variations_max) \
)

inline void missile_pairs_shift_angle_1_away(
	const int& subphase,
	unsigned char& angle_southwest,
	unsigned char& angle_southeast
) {
	angle_southwest -= 0x02;
	angle_southeast += 0x02;
}

#define missile_pairs_shift_angle_2_towards( \
	subphase, angle_southwest, angle_southeast \
) { \
	if(subphase == missile_subphase_variation(0, MSP_SHIFT_ANGLE_2)) { \
		angle_southwest += 0x04; \
	} else if(subphase == missile_subphase_variation(1, MSP_SHIFT_ANGLE_2)) { \
		angle_southeast -= 0x04;\
	} else if(subphase == missile_subphase_variation(2, MSP_SHIFT_ANGLE_2)) { \
		angle_southwest += 0x02; \
		angle_southeast -= 0x02; \
	} \
}

inline void missile_pairs_shift_angle_1_clock(
	const int& subphase,
	unsigned char& angle_southwest,
	unsigned char& angle_southeast
) {
	if(subphase == missile_subphase_variation(0, MSP_SHIFT_ANGLE_1)) {
		angle_southwest -= 0x02;
		angle_southeast -= 0x02;
	} else {
		angle_southwest += 0x02;
		angle_southeast += 0x02;
	}
}

#define missile_pairs_shift_angle_2_clock( \
	subphase, angle_southwest, angle_southeast \
) { \
	if(subphase == missile_subphase_variation(0, MSP_SHIFT_ANGLE_2)) { \
		angle_southwest += 0x03; \
		angle_southeast += 0x03; \
	} else if(subphase == missile_subphase_variation(1, MSP_SHIFT_ANGLE_2)) { \
		angle_southwest -= 0x03; \
		angle_southeast -= 0x03; \
	} \
}

// Processes a single frame of the missile pair pattern. [subphase] cycles
// between the fields of missile_subphase_t, offset by randomly selected
// variations. These can be differentiated in [shift_angle_1_func] and
// [shift_angle_2_func].
#define pattern_missile_pairs_from_south( \
	subphase, \
	missile_pairs_fired_in_subphase, \
	target_left, \
	angle_southwest, \
	angle_southeast, \
	iterations_done, \
	variations_max, \
	shift_angle_1_func, \
	shift_angle_2_func \
) { \
	eyes_locked_unput_and_put_then_track(EF_SOUTHWEST | EF_SOUTHEAST); \
	\
	if(boss_phase_frame >= (SUBPHASE_PREPARE_FRAMES - 10)) { \
		/** \
		 * Hardcoding two maximum variations? Doesn't matter though: \
		 * If we're in MSP_PREPARE, we're always in variation 0 (see below). \
		 */ \
		if(missile_subphase_is(subphase, MSP_PREPARE, 2)) { \
			eye_southwest.set_image(C_CLOSED); \
			eye_southeast.set_image(C_CLOSED); \
		} \
	} \
	if( \
		(boss_phase_frame == SUBPHASE_PREPARE_FRAMES) || \
		missile_subphase_is(subphase, MSP_AIM_AND_FIRE_AROUND, variations_max) \
	) { \
		if(missile_subphase_variation_is(subphase, 0, MSP_PREPARE, 1)) { \
			subphase = missile_subphase_variation( \
				(rand() % variations_max), MSP_AIM_AND_FIRE_AROUND \
			); \
			target_left = (player_left - (MISSILE_W / 2)); \
			angle_southwest = missile_angle(eye_southwest, target_left); \
			angle_southeast = missile_angle(eye_southeast, target_left); \
			angle_southwest -= 0x10; \
			angle_southeast += 0x10; \
		} \
		if((boss_phase_frame % MISSILE_INTERVAL) == 0) { \
			fire_missile_pair_from_south(angle_southwest, angle_southeast); \
		} \
		if(boss_phase_frame == SUBPHASE_TIMEOUT_FRAMES) { \
			subphase++; \
			missile_pairs_fired_in_subphase = 0; \
		} \
	} \
	if(missile_subphase_is(subphase, MSP_SHIFT_ANGLE_1, variations_max)) { \
		if((boss_phase_frame % MISSILE_INTERVAL) == 1) { \
			missile_pairs_fired_in_subphase++; \
			shift_angle_1_func(subphase, angle_southwest, angle_southeast); \
			fire_missile_pair_from_south(angle_southwest, angle_southeast); \
			if(missile_pairs_fired_in_subphase > 10) { \
				subphase++; \
				missile_pairs_fired_in_subphase = 0; \
			} \
		} \
	} else if( \
		missile_subphase_is(subphase, MSP_SHIFT_ANGLE_2, variations_max) \
	) { \
		if((boss_phase_frame % MISSILE_INTERVAL) == 1) { \
			missile_pairs_fired_in_subphase++; \
			shift_angle_2_func(subphase, angle_southwest, angle_southeast); \
			fire_missile_pair_from_south(angle_southwest, angle_southeast); \
			if(missile_pairs_fired_in_subphase > 10) { \
				/** \
				 * Yup, always resetting to variation 0, which will in turn \
				 * select a new random one. \
				 */ \
				subphase = missile_subphase_variation(0, MSP_PREPARE); \
				\
				missile_pairs_fired_in_subphase = 0; \
				boss_phase_frame = 0; \
				iterations_done++; \
			} \
		} \
	} \
}
// --------------

// Lasers across the playfield
// ---------------------------

static const pixel_t LASER_W = 3;
static const pixel_t LASER_VELOCITY = 4;
static const int LASER_INTERVAL = 4;
static const pixel_t LASER_VELOCITY_STEP = (LASER_VELOCITY * LASER_INTERVAL);
static const dots8_t LASER_DOTS = (
	((1 << LASER_W) - 1) << (BYTE_DOTS - LASER_W) // (***_____)
);

enum laser_subphase_t {
	LSP_PREPARE = 0,
	LSP_ACTIVE = 1,
	LSP_DONE = 2,
};

inline int laser_subphase(int iteration, laser_subphase_t lsp) {
	return ((iteration * LSP_DONE) + lsp);
}

#define laser_pattern_should_run(subphase, iteration) ( \
	( \
		(boss_phase_frame == 40) && \
		(subphase == laser_subphase(iteration, LSP_PREPARE)) \
	) || (subphase == laser_subphase(iteration, LSP_ACTIVE)) \
)

#define laser_eye eye_north

inline screen_x_t laser_left(void) {
	return laser_eye.offcenter_x();
}

inline screen_y_t laser_top(void) {
	return laser_eye.iris_top();
}

inline screen_x_t laser_right(const pixel_t& x_edge_offset, x_direction_t dir) {
	return ((dir == X_LEFT)
		? (PLAYFIELD_RIGHT - x_edge_offset)
		: (PLAYFIELD_LEFT + x_edge_offset)
	);
}

inline void laser_unput_render_hittest(
	const pixel_t& x_edge_offset, x_direction_t dir
) {
	screen_x_t cur_right = laser_right(x_edge_offset, dir);
	screen_y_t cur_top = laser_top();
	screen_y_t cur_left = laser_left();

	screen_x_t prev_right = (laser_right(x_edge_offset, dir) - (
		dir ? -LASER_VELOCITY_STEP : LASER_VELOCITY_STEP
	));
	screen_y_t prev_top = laser_top();
	screen_y_t prev_left = laser_left();

	linebullet_unput(prev_left, prev_top, prev_right, PLAYFIELD_BOTTOM);
	linebullet_put_patterned_and_hittest(
		cur_left, cur_top, cur_right, PLAYFIELD_BOTTOM, V_WHITE, LASER_DOTS
	);
}

inline void laser_unput(const pixel_t& x_edge_offset, x_direction_t dir) {
	linebullet_unput(
		laser_left(),
		laser_top(),
		laser_right(x_edge_offset, dir),
		PLAYFIELD_BOTTOM
	);
}

// Separate function to work around the `Condition is always true/false` and
// `Unreachable code` warnings. Should really be done unconditionally, though.
inline void conditionally_reset(pixel_t& x_edge_offset, bool cond) {
	if(cond) {
		x_edge_offset = 0;
	}
}

#define pattern_single_laser_across_playfield( \
	subphase, redundant_lvalue, x_edge_offset, iteration, right_to_left \
) \
	if(subphase == laser_subphase(iteration, LSP_PREPARE)) { \
		subphase = laser_subphase(iteration, LSP_ACTIVE); \
		redundant_lvalue = 0; /* ZUN bloat */ \
		conditionally_reset(x_edge_offset, right_to_left); \
	} \
	if((boss_phase_frame % LASER_INTERVAL) == 1) { \
		/* Track the laser target */ \
		if(x_edge_offset <= (PLAYFIELD_CENTER_X - EYE_W)) { \
			laser_eye.set_image(right_to_left ? C_RIGHT : C_LEFT); \
		} else if(x_edge_offset >= (PLAYFIELD_CENTER_X + EYE_W)) { \
			laser_eye.set_image(right_to_left ? C_LEFT : C_RIGHT); \
		} else { \
			laser_eye.set_image(C_DOWN); \
		} \
		\
		laser_unput_render_hittest(x_edge_offset, right_to_left); \
		if(x_edge_offset >= (PLAYFIELD_W - (PLAYER_W + (PLAYER_W / 2)))) { \
			laser_unput(x_edge_offset, right_to_left); \
			subphase = laser_subphase((iteration + 1), LSP_PREPARE); \
			boss_phase_frame = 0; \
			\
			/**
			 * ZUN bloat: Done after LSP_PREPARE, where it's much more \
			 * appropriate. \
			 */ \
			x_edge_offset = 0; \
			\
			if(rank > RANK_NORMAL) { \
				laser_eye.fire_from_iris_center( \
					PG_3_SPREAD_NARROW_AIMED, 0.1875f \
				); \
			} \
		} \
		x_edge_offset += LASER_VELOCITY_STEP; \
	}

#define pattern_dual_lasers_across_playfield( \
	subphase, redundant_lvalue, x_edge_offset, iteration \
) \
	if(subphase == laser_subphase(iteration, LSP_PREPARE)) { \
		subphase = laser_subphase(iteration, LSP_ACTIVE); \
		redundant_lvalue = 0; /* ZUN bloat */ \
		x_edge_offset = 0; \
	} \
	if((boss_phase_frame % LASER_INTERVAL) == 1) { \
		laser_eye.set_image(C_AHEAD); \
		\
		/** \
		 * ZUN bug: The really should be both unblitted and *then* both \
		 * rendered. With graph_r_line_unput() unblitting 32 horizontal \
		 * pixels for every row, the top part of the X_RIGHT-moving laser \
		 * will never be fully visible. \
		 */ \
		laser_unput_render_hittest(x_edge_offset, X_RIGHT); \
		laser_unput_render_hittest(x_edge_offset, X_LEFT); \
		if(x_edge_offset >= (PLAYFIELD_CENTER_X - PLAYER_W)) { \
			laser_unput(x_edge_offset, X_RIGHT); \
			laser_unput(x_edge_offset, X_LEFT); \
			subphase = laser_subphase(iteration, LSP_DONE); \
			boss_phase_frame = 0; \
			x_edge_offset = 0; \
			if(rank == RANK_HARD) { \
				laser_eye.fire_from_iris_center( \
					PG_3_SPREAD_NARROW_AIMED, 0.1875f \
				); \
			} \
			if(rank == RANK_LUNATIC) { \
				laser_eye.fire_from_iris_center( \
					PG_5_SPREAD_NARROW_AIMED, 0.25f \
				); \
			} \
		} \
		x_edge_offset += LASER_VELOCITY_STEP; \
	}
// ---------------------------

/// Pentagram
/// ---------

static const int PENTAGRAM_INTERVAL = 4;
static const int PENTAGRAM_POINTS = 5;
static struct {
	// Corners, arranged in counterclockwise order.
	screen_x_t x[PENTAGRAM_POINTS];
	screen_y_t y[PENTAGRAM_POINTS];

	pixel_t radius;
	screen_point_t center;

	// This reversed order ruins a potential PUSH optimization...
	pixel_t velocity_y;
	pixel_t velocity_x;

	void unput(void) {
		linebullet_unput(x[0], y[0], x[2], y[2]);
		linebullet_unput(x[2], y[2], x[4], y[4]);
		linebullet_unput(x[4], y[4], x[1], y[1]);
		linebullet_unput(x[1], y[1], x[3], y[3]);
		linebullet_unput(x[3], y[3], x[0], y[0]);
	}

	void put_and_hittest(void) {
		linebullet_put_and_hittest(x[0], y[0], x[2], y[2], V_WHITE);
		linebullet_put_and_hittest(x[2], y[2], x[4], y[4], V_WHITE);
		linebullet_put_and_hittest(x[4], y[4], x[1], y[1], V_WHITE);
		linebullet_put_and_hittest(x[1], y[1], x[3], y[3], V_WHITE);
		linebullet_put_and_hittest(x[3], y[3], x[0], y[0], V_WHITE);
	}

	void aim(const screen_x_t& target_x, screen_y_t target_y) {
		vector2_between(
			center.x, inhibit_Z3(center.y),
			target_x, target_y,
			velocity_x, velocity_y,
			4
		);
	}

	void move(bool dumb_workaround_for_different_call_positions = true) {
		if(dumb_workaround_for_different_call_positions) {
			center.y += velocity_y;
			center.x += velocity_x;
		}
	}
} pentagram;

// Initial position of the pentagram, with corners in eyes
// -------------------------------------------------------

inline void pentagram_between_eyes_put(
	const CEyeEntity& eye_1, const CEyeEntity& eye_2
) {
	linebullet_put_and_hittest(
		eye_1.offcenter_x(), eye_1.iris_top(),
		eye_2.offcenter_x(), eye_2.iris_top(), V_WHITE
	);
}

inline void pentagram_between_eyes_put(void) {
	pentagram_between_eyes_put(eye_north, eye_southwest);
	pentagram_between_eyes_put(eye_southwest, eye_east);
	pentagram_between_eyes_put(eye_east, eye_west);
	pentagram_between_eyes_put(eye_west, eye_southeast);
	pentagram_between_eyes_put(eye_southeast, eye_north);
}
// -------------------------------------------------------

// Shrink animation
// ----------------

// No weird fraction for once!
static const screen_y_t PENTAGRAM_SHRINK_TARGET_CENTER_Y = PLAYFIELD_CENTER_Y;

static const pixel_t PENTAGRAM_RADIUS_FINAL = 64;
static const unsigned char PENTAGRAM_ANGLE_INITIAL = 0xC0; // (-0x40)

// As the largest distance, we can define all other shrink distances in terms
// of this one. Technically, the radius factor should be
//
// 	cos(PENTAGRAM_ANGLE_INITIAL + (1 × (360° / PENTAGRAM_POINTS)))
//
// for the 1st clockwise point on the pentagram. But since that comes out to
// roughly ≈ 0.95 and thus *almost* 1, it's acceptable to just round up.
static const pixel_t PENTAGRAM_SHRINK_DISTANCE = (
	EYE_LATERAL_CENTER_DISTANCE_X - (PENTAGRAM_RADIUS_FINAL * 1)
);

inline screen_x_t pentagram_shrink_x(eye_flag_t eye, const pixel_t& distance) {
	enum {
		DISTANCE_SOUTH = static_cast<pixel_t>(
			// cos(PENTAGRAM_ANGLE_INITIAL + (2 × (360° / PENTAGRAM_POINTS)))
			EYE_SOUTH_CENTER_DISTANCE_X - (PENTAGRAM_RADIUS_FINAL * 0.587f)
		),
		// Integer arithmetic can never be precise for the distances required
		// here. All these calculations are at least an attempt of deriving
		// those magic shrink factors, even if we have to cheat by "rounding
		// up" in the end.
		DIVISOR_SOUTH = ((PENTAGRAM_SHRINK_DISTANCE / DISTANCE_SOUTH) + 1),
	};

	if(eye == EF_WEST) {
		return (     eye_west.offcenter_x() + distance);
	} else if(eye == EF_EAST) {
		return (     eye_east.offcenter_x() - distance);
	} else if(eye == EF_SOUTHWEST) {
		return (eye_southwest.offcenter_x() + (distance / DIVISOR_SOUTH));
	} else if(eye == EF_SOUTHEAST) {
		return (eye_southeast.offcenter_x() - (distance / DIVISOR_SOUTH));
	}
	return eye_north.offcenter_x();
}

inline screen_y_t pentagram_shrink_y(eye_flag_t eye, const pixel_t& distance) {
	enum {
		TARGET_CENTER_Y = PENTAGRAM_SHRINK_TARGET_CENTER_Y,

		TARGET_NORTH = static_cast<pixel_t>(
			// sin(PENTAGRAM_ANGLE_INITIAL + (1 × (360° / PENTAGRAM_POINTS)))
			TARGET_CENTER_Y - (PENTAGRAM_RADIUS_FINAL * 1)
		),
		TARGET_LATERAL = static_cast<pixel_t>(
			// sin(PENTAGRAM_ANGLE_INITIAL + (2 × (360° / PENTAGRAM_POINTS)))
			TARGET_CENTER_Y + (PENTAGRAM_RADIUS_FINAL * -0.309f)
		),
		TARGET_SOUTH = static_cast<pixel_t>(
			// sin(PENTAGRAM_ANGLE_INITIAL + (3 × (360° / PENTAGRAM_POINTS)))
			TARGET_CENTER_Y + (PENTAGRAM_RADIUS_FINAL * +0.809f)
		),

		DISTANCE_NORTH = (TARGET_NORTH - (EYE_NORTH_TOP + (EYE_H / 2))),
		DISTANCE_LATERAL = (TARGET_LATERAL - (EYE_LATERAL_TOP + (EYE_H / 2))),
		DISTANCE_SOUTH = (TARGET_SOUTH - (EYE_LATERAL_TOP + (EYE_H / 2))),

		// Integer arithmetic can never be precise for the distances required
		// here. All these calculations are at least an attempt of deriving
		// those magic shrink factors, even if we have to cheat by "rounding
		// up" in the end.
		DIVISOR_NORTH = (PENTAGRAM_SHRINK_DISTANCE / DISTANCE_NORTH),
		DIVISOR_LATERAL = ((PENTAGRAM_SHRINK_DISTANCE / DISTANCE_LATERAL) + 1),
		DIVISOR_SOUTH = ((PENTAGRAM_SHRINK_DISTANCE / DISTANCE_SOUTH) + 1),
	};

	if(eye == EF_WEST) {
		return (eye_west.iris_top() + (distance / DIVISOR_LATERAL));
	} else if(eye == EF_EAST) {
		return (eye_east.iris_top() + (distance / DIVISOR_LATERAL));
	} else if(eye == EF_SOUTHWEST) {
		return (eye_southwest.iris_top() + (distance / DIVISOR_SOUTH));
	} else if(eye == EF_SOUTHEAST) {
		return (eye_southeast.iris_top() + (distance / DIVISOR_SOUTH));
	}
	return (eye_north.iris_top() + (distance / DIVISOR_NORTH));
}

inline void pentagram_shrink_unput(
	eye_flag_t eye_1, eye_flag_t eye_2, const pixel_t& distance
) {
	linebullet_unput(
		pentagram_shrink_x(eye_1, distance),
		pentagram_shrink_y(eye_1, distance),
		pentagram_shrink_x(eye_2, distance),
		pentagram_shrink_y(eye_2, distance)
	);
}

inline void pentagram_shrink_put(
	eye_flag_t eye_1, eye_flag_t eye_2, const pixel_t& distance
) {
	linebullet_put_and_hittest(
		pentagram_shrink_x(eye_1, distance),
		pentagram_shrink_y(eye_1, distance),
		pentagram_shrink_x(eye_2, distance),
		pentagram_shrink_y(eye_2, distance),
		V_WHITE
	);
}

#define pentagram_shrink(func, distance) { \
	func(EF_NORTH, EF_SOUTHWEST, distance); \
	func(EF_SOUTHWEST, EF_EAST, distance); \
	func(EF_EAST, EF_WEST, distance); \
	func(EF_WEST, EF_SOUTHEAST, distance); \
	func(EF_SOUTHEAST, EF_NORTH, distance); \
}
// ----------------

// Regular pentagram, with spin and slam phases
// --------------------------------------------

#define pentagram_corners_set_regular(i, angle_offset) { \
	for(i = 0; i < PENTAGRAM_POINTS; i++) { \
		pentagram.x[i] = polar_x( \
			pentagram.center.x, \
			pentagram.radius, \
			(angle_offset + (i * (0x100 / PENTAGRAM_POINTS))) \
		); \
		pentagram.y[i] = polar_y( \
			pentagram.center.y, \
			pentagram.radius, \
			(angle_offset + (i * (0x100 / PENTAGRAM_POINTS))) \
		); \
	} \
}

// Not "subphases", as these run independent of [boss_phase] – that one does
// in fact loop back at the end of the *_SLAM_INTO_PLAYER_* phases.
enum pentagram_attack_phase_t {
	PAP_PREPARE_1 = 0,
	PAP_SPIN_CLOCKWISE_1 = 1,
	PAP_SPIN_COUNTERCLOCKWISE_1 = 2,
	PAP_SPIN_CLOCKWISE_2 = 3,
	PAP_SPIN_COUNTERCLOCKWISE_2 = 4,
	PAP_SPIN_CLOCKWISE_3 = 5,
	PAP_SLAM_INTO_PLAYER_1 = 6,
	PAP_PREPARE_2 = 7,
	PAP_GROW = 8,
	PAP_SLAM_INTO_PLAYER_2 = 9,

	_pentagram_attack_phase_t_FORCE_INT16 = 0x7FFF
};

#define pentagram_in_slam_phase(phase) ( \
	(phase == PAP_SLAM_INTO_PLAYER_1) || (phase == PAP_SLAM_INTO_PLAYER_2) \
)

#define pentagram_in_clockwise_spin_phase(phase) ( \
	(phase == PAP_SPIN_CLOCKWISE_1) || \
	(phase == PAP_SPIN_CLOCKWISE_2) || \
	(phase == PAP_SPIN_CLOCKWISE_3) \
)

#define pentagram_in_counterclockwise_spin_phase(phase) ( \
	(phase == PAP_SPIN_COUNTERCLOCKWISE_1) || \
	(phase == PAP_SPIN_COUNTERCLOCKWISE_2) \
)

// Also performs collision detection.
void pascal near pentagram_regular_unput_update_render(
	int angle_offset // ACTUAL TYPE: unsigned char
)
{
	int i;
	pentagram.unput();
	pentagram_corners_set_regular(i, angle_offset);
	pentagram.put_and_hittest();
}

// MODDERS: Merge into the other pentagram structure.
struct Pentagram {
	pentagram_attack_phase_t phase;
	int angle; // ACTUAL TYPE: unsigned char

	void spin(clock_direction_t dir) {
		if(dir == CLOCKWISE) {
			angle += ((boss_phase_frame / 64) + 0x02);
		} else {
			angle -= ((boss_phase_frame / 64) + 0x02);
		}
	}

	void unput_update_render_regular(void) const {
		pentagram_regular_unput_update_render(angle);
	}
};

// ZUN bug: The pentagram is not rendered in the preparation phases, and can
// thus easily be unblitted by overlapping sprites, most notably player shots
// or HARRY UP pellets.
#define pentagram_prepare_update(pentagram_, phase_id) { \
	if( \
		(boss_phase_frame == SUBPHASE_PREPARE_FRAMES) && \
		(pentagram_.phase == phase_id) \
	) { \
		pentagram_.phase = static_cast<pentagram_attack_phase_t>( \
			phase_id + 1 \
		); \
		boss_phase_frame = 0; \
	} \
}

// The next two are forced to be used inside an `if` statement, returning a
// non-zero value if the phase is done.
#define pentagram_spin_unput_update_render(pentagram_, dir) \
	(boss_phase_frame % PENTAGRAM_INTERVAL) == 0) { \
		pentagram_.spin(dir); \
		pentagram_.unput_update_render_regular(); \
	} \
	if(boss_phase_frame >= SUBPHASE_TIMEOUT_FRAMES


#define pentagram_slam_unput_update_render( \
	pentagram_, homing_threshold_from_bottom, move_first \
) \
	(boss_phase_frame % PENTAGRAM_INTERVAL) == 0) { \
		if(pentagram.center.y < ( \
			PLAYFIELD_BOTTOM - (homing_threshold_from_bottom) \
		)) { \
			pentagram.aim(player_left, player_bottom()); \
		} \
		pentagram.move(move_first); \
		pentagram_.spin(CLOCKWISE); \
		pentagram.move(!move_first); \
		pentagram_.unput_update_render_regular(); \
	} \
	if(pentagram.center.y >= (PLAYFIELD_BOTTOM + ((PLAYFIELD_H / 84) * 5))
// --------------------------------------------
/// ---------

// Function ordering fails
// -----------------------

// Opens and closes the given eyes, and changes the 邪 color in [stage_palette]
// (and, via transferring it to [z_Palettes], also the hardware color) by
// gradually incrementing and decrementing the given components on 9 out of 10
// frames. Takes ownership of [frame]. To keep the 邪 color unchanged, set
// [yokoshima_comp_inc] and [yokoshima_comp_dec] to a value ≥ COMPONENT_COUNT.
//
// ZUN quirk: While the final [z_Palettes] values are clamped to 0x0 and 0xF,
// the [yokoshima_comp_inc] component in the [stage_palette] is *not* clamped
// to 0xF after incrementing. This overflow can (and does) affect the final
// color on successive recoloring operations.
//
// MODDERS: Make the component parameters unsigned.
void eyes_toggle_and_yokoshima_recolor(
	eye_flag_t eyes_to_close,
	eye_flag_t eyes_to_open,
	int yokoshima_comp_dec,
	int yokoshima_comp_inc,
	int& frame
);
// -----------------------

// Separate function to work around the `Condition is always true/false` and
// `Unreachable code` warnings. (It's unnecessary anyway, though.)
inline void conditionally_reset_missiles(bool cond) {
	if(cond) {
		Missiles.reset();
	}
}

#define yuugenmagan_defeat_if(cond, reset_missiles, tmp_i) { \
	if(cond) { \
		mdrv2_bgm_fade_out_nonblock(); \
		Pellets.unput_and_reset(); \
		conditionally_reset_missiles(reset_missiles); \
		\
		/* 5? Triply broken, since this fight doesn't even use lasers... */ \
		shootout_lasers_unput_and_reset_broken(tmp_i, 5); \
		boss_defeat_animate(); \
		\
		/** \
		 * ZUN bloat: Already done at the start of REIIDEN.EXE's main(). \
		 * The REIIDEN.EXE process restarts after the end of a scene \
		 * anyway, making this load doubly pointless. \
		 */ \
		scene_init_and_load(3); \
	} \
}

void yuugenmagan_main(void)
{
	const unsigned char flash_colors[2] = { 1, 11 };
	int i;

	static int invincibility_frame;

	static union {
		int missile_pairs_fired_in_subphase;
		int subphase_frame;

		// Always increasing, even when going right-to-left.
		pixel_t x_edge_offset;

		pixel_t distance;
		int unused;
	} u1;

	static union {
		int subphase;
		int yokoshima_comp_dec;
		int unused;
	} u2;

	static screen_x_t target_left;
	static pixel_t unused_distance;

	// Compared to just reusing [invincibility_frame], this "copy" has the
	// advantage of not being reset every 40 frames, and thus lasting the full
	// EYE_TOGGLE_FRAMES.
	static int after_hit_frames;

	static Pentagram pentagram_;

	static union {
		int8_t iterations_done;
		int8_t yokoshima_comp_inc;
		eye_flag_t eyes_open;
		int8_t unused;
	} u3;

	static struct {
		bool initial_hp_rendered;

		void frame_common(void) {
			boss_phase_frame++;
			invincibility_frame++;
		}

		void next(int phase_new) {
			boss_phase = phase_new;
			boss_phase_frame = 0;
			invincibility_frame = 0;
		}

		void next(int phase_new, int& u2_element_to_reset) {
			boss_phase = phase_new;
			u2_element_to_reset = 0;
			boss_phase_frame = 0;
			invincibility_frame = 0;
		}

		void next(
			int phase_new,
			int& u2_element_to_reset,
			int8_t& u3_element_to_reset,
			int8_t new_value_for_u3 = 0
		) {
			boss_phase = phase_new;
			u2_element_to_reset = 0;
			u3_element_to_reset = new_value_for_u3;
			boss_phase_frame = 0;
			invincibility_frame = 0;
		}

		// Respawns the pentagram.
		void back_from_13_to_10(pentagram_attack_phase_t pentagram_phase_new) {
			if(pentagram_phase_new == PAP_PREPARE_1) {
				pentagram_.phase = pentagram_phase_new;
			}
			boss_phase_frame = 0;
			boss_phase = 10;
			u2.yokoshima_comp_dec = COMPONENT_COUNT;
			u3.yokoshima_comp_inc = COMPONENT_COUNT;
			if(pentagram_phase_new == PAP_PREPARE_2) {
				pentagram_.phase = pentagram_phase_new;
			}
			invincibility_frame = 0;
			u1.unused = 0;
			pentagram.unput();
		}
	} phase;

	static union {
		unsigned char missile_southwest;
		unsigned char pellet_east;
		unsigned char tmp; // MODDERS: Turn into a scope-local variable
	} angle;

	static unsigned char angle_missile_southeast;

	static struct {
		bool16 invincible;

		void update_and_render(const unsigned char (&flash_colors)[2]) {
			#define hittest(eye) ( \
				(eye.hittest_orb() == true) && (eye.image() != C_HIDDEN) \
			)

			boss_hit_update_and_render(
				invincibility_frame,
				invincible,
				boss_hp,
				flash_colors,
				sizeof(flash_colors),
				5000,
				boss_nop,
				(
					hittest(eye_west) ||
					hittest(eye_east) ||
					hittest(eye_southwest) ||
					hittest(eye_southeast) ||
					hittest(eye_north)
				)
			);

			#undef hittest
		}
	} hit = { false };

	Missiles.unput_update_render();

	if(boss_phase == 0) {
		// Downwards lasers from every eye, in a symmetric sequence from the
		// left and right edges of the playfield towards the center

		hud_hp_increment_render(
			phase.initial_hp_rendered, boss_hp, boss_phase_frame
		);

		boss_phase_frame++;

		eye_west.locked_unput_and_put_8();
		eye_east.locked_unput_and_put_8();
		eye_southwest.locked_unput_and_put_8();
		eye_southeast.locked_unput_and_put_8();
		eye_north.locked_unput_and_put_8();

		phase_0_downwards_lasers();

		if((boss_phase_frame % 40) == 0) {
			// Target color: (13, 13, 5) ⇒ #DD5
			z_Palettes[COL_YOKOSHIMA].c.r++; // ZUN bloat
			z_Palettes[COL_YOKOSHIMA].c.g++; // ZUN bloat
			stage_palette[COL_YOKOSHIMA].c.r++;
			stage_palette[COL_YOKOSHIMA].c.g++;
			z_palette_set_all_show(stage_palette);
		}
		if(boss_phase_frame == KEYFRAME_LATERAL_OPENING) {
			phase_0_eyes_open(KEYFRAME_LATERAL_OPENING);

			// ZUN bloat: Without a call to hit.update_and_render(), any hitbox
			// manipulation in this phase is doubly redundant...
			eye_west.hitbox_orb_activate();
			eye_east.hitbox_orb_activate();
		} else if(boss_phase_frame == KEYFRAME_SOUTH_OPENING) {
			phase_0_eyes_open(KEYFRAME_SOUTH_OPENING);
			eye_southwest.hitbox_orb_activate();
			eye_southeast.hitbox_orb_activate();
		} else if(boss_phase_frame == KEYFRAME_NORTH_OPENING) {
			phase_0_eyes_open(KEYFRAME_NORTH_OPENING);
			eye_north.hitbox_orb_activate();
		} else if(boss_phase_frame == KEYFRAME_LATERAL_OPEN) {
			phase_0_eyes_open(KEYFRAME_LATERAL_OPEN);
		} else if(boss_phase_frame == KEYFRAME_SOUTH_OPEN) {
			phase_0_eyes_open(KEYFRAME_SOUTH_OPEN);
		} else if(boss_phase_frame == KEYFRAME_NORTH_OPEN) {
			phase_0_eyes_open(KEYFRAME_NORTH_OPEN);
		} else if(boss_phase_frame == KEYFRAME_CLOSING) {
			phase_0_eyes_close(KEYFRAME_CLOSING);
			eye_west.hitbox_orb_deactivate();
			eye_east.hitbox_orb_deactivate();
			eye_southwest.hitbox_orb_deactivate();
			eye_southeast.hitbox_orb_deactivate();
			eye_north.hitbox_orb_deactivate();

			// ZUN quirk: Did you mean ">= RANK_HARD"? Because...
			if(rank == RANK_HARD) {
				phase_0_fire(eye_north);
				phase_0_fire(eye_southeast);
				phase_0_fire(eye_southwest);

				// ... this condition can now never be true, making the Lunatic
				// version of this subpattern effectively unused.
				if(rank == RANK_LUNATIC) {
					phase_0_fire(eye_west);
					phase_0_fire(eye_east);
				}
			}
		} else if(boss_phase_frame == KEYFRAME_CLOSED) {
			phase_0_eyes_close(KEYFRAME_CLOSED);

			if(rank == RANK_LUNATIC) {
				phase_0_fire(eye_north);
				phase_0_fire(eye_southeast);
				phase_0_fire(eye_southwest);
				phase_0_fire(eye_west);
				phase_0_fire(eye_east);
			}
		} else if(boss_phase_frame == KEYFRAME_HIDDEN) {
			phase_0_eyes_close(KEYFRAME_HIDDEN);
		} else if(boss_phase_frame == KEYFRAME_LATERAL_LASER_DONE) {
			eye_west.set_image(C_CLOSED);
			eye_east.set_image(C_CLOSED);

			eye_west.downwards_laser_unput();
			eye_east.downwards_laser_unput();
		} else if(boss_phase_frame == KEYFRAME_SOUTH_LASER_DONE) {
			eye_west.set_image(C_HALFOPEN);
			eye_east.set_image(C_HALFOPEN);

			eye_west.hitbox_orb_activate();
			eye_east.hitbox_orb_activate();

			eye_southwest.downwards_laser_unput();
			eye_southeast.downwards_laser_unput();
		} else if(boss_phase_frame > KEYFRAME_NORTH_LASER_DONE) {
			boss_phase = 1;
			hit.invincible = false;
			boss_phase_frame = 0;
			z_palette_set_all_show(stage_palette);
			boss_palette_snap();
			phase.initial_hp_rendered = false; // ZUN bloat

			// ZUN bloat: These won't be visible at all, since we get here on
			// the second frame with the entity lock active. On the next frame,
			// these two eyes will immediately adjust themselves to the
			// player's tracked position.
			eye_west.set_image(C_LEFT);
			eye_east.set_image(C_DOWN);

			pattern_interval = select_for_rank(350, 300, 200, 130);

			eye_north.downwards_laser_unput();
		}
	} else if(boss_phase == 1) {
		// Slow pellets from the lateral eyes

		phase.frame_common();
		eyes_locked_unput_and_put_then_track(EF_WEST | EF_EAST);

		phase_1_pellets_from_lateral();
		hit.update_and_render(flash_colors);
		if((boss_hp <= HP_PHASE_1_END) || (boss_phase_frame > 1100)) {
			phase.next(2);
		}
	} else if(boss_phase == 2) {
		// (13, 13, 5) → (0, 13, 68) ⇒ #0DF (cyan)
		eyes_toggle_and_yokoshima_recolor(
			(EF_WEST | EF_EAST),
			(EF_SOUTHWEST | EF_SOUTHEAST),
			COMPONENT_R,
			COMPONENT_B,
			boss_phase_frame
		);
		if(boss_phase_frame >= EYE_TOGGLE_FRAMES) {
			phase.next(3, u2.subphase, u3.iterations_done);
			u1.missile_pairs_fired_in_subphase = 0;

			z_palette_set_all_show(stage_palette);
			boss_palette_snap();
			pattern_interval = select_for_rank(8, 12, 16, 20); // (unused)
		}
	} else if(boss_phase == 3) {
		// Missiles from the southern eyes, whose angles first shift away from
		// Reimu's tracked position and then towards it

		phase.frame_common();
		pattern_missile_pairs_from_south(
			u2.subphase,
			u1.missile_pairs_fired_in_subphase,
			target_left,
			angle.missile_southwest,
			angle_missile_southeast,
			u3.iterations_done,
			3,
			missile_pairs_shift_angle_1_away,
			missile_pairs_shift_angle_2_towards
		);
		hit.update_and_render(flash_colors);
		if((boss_hp <= HP_PHASE_3_END) || (u3.iterations_done >= 5)) {
			phase.next(4);
		}
	} else if(boss_phase == 4) {
		// (0, 13, 68) → (63, 0, 68) ⇒ #F0F (magenta)
		eyes_toggle_and_yokoshima_recolor(
			(EF_SOUTHWEST | EF_SOUTHEAST),
			(EF_WEST | EF_EAST),
			COMPONENT_G,
			COMPONENT_R,
			boss_phase_frame
		);
		if(boss_phase_frame >= EYE_TOGGLE_FRAMES) {
			phase.next(5, u2.subphase, u3.iterations_done);
			u1.subphase_frame = 0;

			z_palette_set_all_show(stage_palette);
			boss_palette_snap();
			unused_distance = (player_bottom() - eye_west.cur_top);
			pattern_interval = select_for_rank(12, 8, 4, 2);
			angle.pellet_east = 0x00;
		}
	} else if(boss_phase == 5) {
		// Circular pellets sprayed from the lateral eyes

		enum phase_5_subphase_t {
			P5_PREPARE_1 = 0,
			P5_SPRAY_1 = 1,
			P5_PREPARE_2 = 2,
			P5_SPRAY_2 = 3,
		};

		phase.frame_common();

		// ZUN bloat: Redundant and confusing. Just use the regular
		// [boss_phase_frame] exclusively?
		u1.subphase_frame++;

		angle.pellet_east--;

		eyes_locked_unput_and_put_then_track(EF_WEST | EF_EAST);

		if(
			(boss_phase_frame == SUBPHASE_PREPARE_FRAMES) &&
			(u2.subphase == P5_PREPARE_1)
		) {
			u1.subphase_frame = 0;
			u2.subphase = P5_SPRAY_1;
		}
		if(u2.subphase == P5_SPRAY_1) {
			if((u1.subphase_frame % pattern_interval) == 0) {
				eye_west.fire_from_bottom_center(
					true, angle.pellet_east, 4.0f
				);
				eye_east.fire_from_bottom_center(
					false, angle.pellet_east, 4.0f
				);
			}
			if((u1.subphase_frame / 5) >= 36) {
				u2.subphase = P5_PREPARE_2;
				boss_phase_frame = 0;
			}
		}
		if(
			(u2.subphase == P5_PREPARE_2) &&
			(boss_phase_frame > (SUBPHASE_PREPARE_FRAMES / 2))
		) {
			u1.subphase_frame = -15;
			u2.subphase = P5_SPRAY_2;
			angle.pellet_east = 0x80;
		}
		if(u2.subphase == P5_SPRAY_2) {
			if((u1.subphase_frame % pattern_interval) == 0) {
				// Since these pellets don't reach the top of the playfield
				// before this subphase ends, they don't actually move
				// differently compared to the first subphase.
				eye_west.fire_from_bottom_center(
					true,
					angle.pellet_east,
					4.0f,
					PM_FALL_STRAIGHT_FROM_TOP_THEN_REGULAR,
					4.0f
				);
				eye_east.fire_from_bottom_center(
					false,
					angle.pellet_east,
					4.0f,
					PM_FALL_STRAIGHT_FROM_TOP_THEN_REGULAR,
					4.0f
				);
			}
			if((u1.subphase_frame / 5) >= 20) {
				u2.subphase = P5_PREPARE_1;
				boss_phase_frame = 0;
				u3.iterations_done++;
				angle.pellet_east = 0x00;
			}
		}
		hit.update_and_render(flash_colors);
		if((boss_hp <= HP_PHASE_5_END) || (u3.iterations_done > 4)) {
			phase.next(6);
		}
	} else if(boss_phase == 6) {
		// (63, 0, 68) → (0, 0, 68) ⇒ #00F (blue)
		eyes_toggle_and_yokoshima_recolor(
			(EF_WEST | EF_EAST),
			(EF_SOUTHWEST | EF_SOUTHEAST),
			COMPONENT_R,
			COMPONENT_COUNT,
			boss_phase_frame
		);
		if(boss_phase_frame >= EYE_TOGGLE_FRAMES) {
			phase.next(7, u2.subphase, u3.iterations_done);
			u1.missile_pairs_fired_in_subphase = 0;
			pentagram_.angle = 0x00; // ZUN bloat

			z_palette_set_all_show(stage_palette);
			boss_palette_snap();
			pattern_interval = select_for_rank(10, 16, 20, 24); // (unused)
		}
	} else if(boss_phase == 7) {
		// Missiles from the southern eyes, with (counter)clockwise angle shifts

		phase.frame_common();
		pattern_missile_pairs_from_south(
			u2.subphase,
			u1.missile_pairs_fired_in_subphase,
			target_left,
			angle.missile_southwest,
			angle_missile_southeast,
			u3.iterations_done,
			2,
			missile_pairs_shift_angle_1_clock,
			missile_pairs_shift_angle_2_clock
		);
		hit.update_and_render(flash_colors);
		if((boss_hp <= HP_PHASE_7_END) || (u3.iterations_done > 4)) {
			phase.next(8);
		}
	} else if(boss_phase == 8) {
		// (0, 0, 68) → (0, 63, 5) ⇒ #0F5 (green, via cyan)
		eyes_toggle_and_yokoshima_recolor(
			(EF_SOUTHWEST | EF_SOUTHEAST),
			EF_NORTH,
			COMPONENT_B,
			COMPONENT_G,
			boss_phase_frame
		);
		if(boss_phase_frame >= EYE_TOGGLE_FRAMES) {
			phase.next(9, u2.subphase);
			u1.x_edge_offset = 0;
			pentagram_.angle = 0x00;

			z_palette_set_all_show(stage_palette);
			boss_palette_snap();
		}
	} else if(boss_phase == 9) {
		// 3-pixel 3-laser sequence from the northern eye

		phase.frame_common();
		laser_eye.locked_unput_and_put_8();

		if((boss_phase_frame >= 30) && (
			(u2.subphase == laser_subphase(0, LSP_PREPARE)) ||
			(u2.subphase == laser_subphase(1, LSP_PREPARE)) ||
			(u2.subphase == laser_subphase(2, LSP_PREPARE))
		)) {
			laser_eye.set_image(C_CLOSED);
		}
		if(laser_pattern_should_run(u2.subphase, 0)) {
			pattern_single_laser_across_playfield(
				u2.subphase, pentagram_.angle, u1.x_edge_offset, 0, X_RIGHT
			);
		} else if(laser_pattern_should_run(u2.subphase, 1)) {
			pattern_single_laser_across_playfield(
				u2.subphase, pentagram_.angle, u1.x_edge_offset, 1, X_LEFT
			);
		} else if(laser_pattern_should_run(u2.subphase, 2)) {
			pattern_dual_lasers_across_playfield(
				u2.subphase, pentagram_.angle, u1.x_edge_offset, 2
			);
		}
		hit.update_and_render(flash_colors);
		if(
			(boss_hp <= HP_PHASE_9_END) ||
			(u2.subphase == laser_subphase(2, LSP_DONE))
		) {
			// ZUN bug: We can get here with a laser still on screen,
			// particularly when holding ↵ Return in debug mode. There should
			// at least be an unblitting call here.

			boss_phase = 10;
			boss_phase_frame = 0;
			invincibility_frame = 0;
			u2.yokoshima_comp_dec = COMPONENT_G;
			u3.yokoshima_comp_inc = COMPONENT_R;

			// Must be done here, as phase 13 loops back into phase 10 with
			// this phase variable set to PAP_PREPARE_2.
			pentagram_.phase = PAP_PREPARE_1;
		}
	} else if(boss_phase == 10) {
		// Prepare pentagram spawning by opening all eyes

		// First iteration: (0, 63, 5) → (63, 0, 5) ⇒ #F05 (red, via yellow)
		// Later iterations don't change the color; see back_from_13_to_10().
		eyes_toggle_and_yokoshima_recolor(
			EF_NONE,
			(EF_WEST | EF_EAST | EF_SOUTHWEST | EF_SOUTHEAST | EF_NORTH),
			u2.yokoshima_comp_dec,
			u3.yokoshima_comp_inc,
			boss_phase_frame
		);
		if(boss_phase_frame >= EYE_TOGGLE_FRAMES) {
			phase.next(11, u2.subphase, u3.unused, 31 /* ZUN bloat */);
			u1.distance = 0;
			pentagram_.angle = 0x00; // Finally not redundant.

			z_palette_set_all_show(stage_palette);
			boss_palette_snap();
		}
	} else if(boss_phase == 11) {
		// Spawns the pentagram with one corner out of every eye, then
		// gradually shrinks and moves it towards the center of the playfield

		enum phase_11_subphase_t {
			P11_PREPARE = 0,
			P11_CORNERS_IN_EYES = 1,
			P11_MOVE = 2,
			P11_DONE = 3,
		};

		phase.frame_common();
		eyes_locked_unput_and_put_then_track(
			EF_WEST | EF_EAST | EF_SOUTHWEST | EF_SOUTHEAST | EF_NORTH
		);
		if(
			(boss_phase_frame == SUBPHASE_PREPARE_FRAMES) ||
			(u2.subphase == P11_CORNERS_IN_EYES)
		) {
			if(u2.subphase == P11_PREPARE) {
				u2.subphase = P11_CORNERS_IN_EYES;
				target_left = player_left; // unused
			}

			// Every frame, for a change? No unblitting glitches here, then. :P
			pentagram_between_eyes_put();

			if(boss_phase_frame == 140) {
				u2.subphase = P11_MOVE;
				u1.distance = 0;
			}
		}

		if(
			(u2.subphase == P11_MOVE) &&
			((boss_phase_frame % PENTAGRAM_INTERVAL) == 1)
		) {
			// ZUN bug: Doing this after blitting the eyes is guaranteed to
			// rip holes into them for at least one frame.
			pentagram_shrink(pentagram_shrink_unput, u1.distance);

			u1.distance += (PENTAGRAM_SHRINK_DISTANCE / 20);
			pentagram_shrink(pentagram_shrink_put, u1.distance);

			// ZUN quirk: Should be >=, and ideally even be clamped to exactly
			// that value. With >, the shrink animation lasts for one step
			// longer than it should, leaving the pentagram both smaller and
			// moved slightly off-center.
			if(u1.distance > PENTAGRAM_SHRINK_DISTANCE) {
				// ZUN quirk: This uses offcenter_x(), which makes sure that
				// the regular pentagram will stay off-center even *if* the
				// above condition were corrected.
				pentagram.x[0] = pentagram_shrink_x(EF_NORTH, u1.distance);
				pentagram.y[0] = pentagram_shrink_y(EF_NORTH, u1.distance);

				// ZUN bloat: All further coordinate assignments are unused and
				// can be deleted. The values are never read in this phase, and
				// phase 12 directly assigns regular polygon coordinates before
				// rendering.
				// Correct ones, too: This seems to be a relic from a time when
				// ZUN stored pentagram corner coordinates in interleaved line
				// order (north → southwest → east → west → southeast) rather
				// than in (counter-)clockwise angle order. Therefore, these
				// wouldn't even result in a pentagram with the rendering
				// function that ended up in the final game.
				pentagram.x[1] = pentagram_shrink_x(EF_SOUTHWEST, u1.distance);
				pentagram.y[1] = pentagram_shrink_y(EF_SOUTHWEST, u1.distance);
				pentagram.x[2] = pentagram_shrink_x(EF_EAST, u1.distance);
				pentagram.y[2] = pentagram_shrink_y(EF_EAST, u1.distance);
				pentagram.x[3] = pentagram_shrink_x(EF_WEST, u1.distance);
				pentagram.y[3] = pentagram_shrink_y(EF_WEST, u1.distance);
				pentagram.x[4] = pentagram_shrink_x(EF_SOUTHEAST, u1.distance);
				pentagram.y[4] = pentagram_shrink_y(EF_SOUTHEAST, u1.distance);

				u2.subphase = P11_DONE;
			}
		}
		hit.update_and_render(flash_colors);
		yuugenmagan_defeat_if((boss_hp <= HP_PHASE_13_END), false, i);
		if(
			((boss_hp <= HP_PHASE_13_END) || (u2.subphase == P11_DONE)) &&
			!hit.invincible
		) {
			phase.next(12, u2.unused, u3.eyes_open, EF_WEST);
			u1.unused = 0;
			pentagram.center.y = (pentagram.y[0] + PENTAGRAM_RADIUS_FINAL);
			pentagram.center.x = pentagram.x[0];
			pentagram.radius = PENTAGRAM_RADIUS_FINAL;

			// ZUN bloat: Done for every rendering call in phase 12.
			// (And also wrong, since PENTAGRAM_ANGLE_INITIAL is different.)
			pentagram_corners_set_regular(i, 0x00);

			// Work around the inaccuracies of 8-bit angles and make sure that
			// at least the lateral corners perfectly line up vertically.
			pentagram.y[1] = pentagram.y[4];

 			// Used in phase 13.
			pattern_interval = select_for_rank(24, 14, 10, 8);
		}
	} else if(boss_phase == 12) {
		// Moves the pentagram on top of the kimono figure

		enum {
			// Fixing the 8 pixels we've overshot above. In fact, the whole
			// reason for overshooting in the first place might have been to
			// ensure that *this* distance cleanly divides by 3?!
			DISTANCE_Y = ((
				PENTAGRAM_SHRINK_TARGET_CENTER_Y - PENTAGRAM_REGULAR_CENTER_Y
			) + 8),

			STEPS = (EYE_TOGGLE_FRAMES / PENTAGRAM_INTERVAL),
			Y_STEP = (DISTANCE_Y / STEPS),
		};

		// ZUN bloat: [boss_phase_frame] would have worked as well, and saved
		// the addition.
		invincibility_frame++;

		// ZUN quirk: Stays on red for the first iteration of the phase, due to
		// merely going
		//
		// 	(63, 0, 5) → (126, 0, 5) ⇒ #F05
		//
		// On the second iteration though, the same addition causes the red
		// component to overflow into negative numbers, which are clamped to
		// zero:
		//
		// 	(126, 0, 5) → (-67, 0, 5) ⇒ #005 (dark blue)
		//
		// The apparent pattern then repeats, leading to the color alternating
		// between red and dark blue on every 2.03 iterations if the player
		// manages to stall the fight long enough.
		eyes_toggle_and_yokoshima_recolor(
			(EF_EAST | EF_SOUTHWEST | EF_SOUTHEAST | EF_NORTH),
			EF_WEST,
			COMPONENT_G,
			COMPONENT_R,
			boss_phase_frame
		);
		if((invincibility_frame % PENTAGRAM_INTERVAL) == 0) {
			// ZUN bug: Missing an unblitting call for the final appearance of
			// the shrunk pentagram from the previous phase. This would
			// require:
			// • storing the shrink animation coordinates inside the structure
			//   rather than recalculating them for both unblitting and
			//   blitting operations,
			// • and not overwriting them with wrong ones at the end of the
			//   previous phase.

			pentagram.center.y -= Y_STEP;
			pentagram_regular_unput_update_render(PENTAGRAM_ANGLE_INITIAL);
		}
		if(boss_phase_frame >= EYE_TOGGLE_FRAMES) {
			phase.next(13, u2.unused, u3.eyes_open, EF_WEST);
			u1.unused = 0;

			// ZUN quirk: Should *maybe* have been PENTAGRAM_ANGLE_INITIAL to
			// achieve a seamless shift between moving up and spinning. Would
			// change the final pattern, though.
			pentagram_.angle = 0x00;

			after_hit_frames = 0;
			z_palette_set_all_show(stage_palette);
			boss_palette_snap();
		}
	} else if(boss_phase == 13) {
		enum {
			GROW_RADIUS = (SUBPHASE_TIMEOUT_FRAMES / PENTAGRAM_INTERVAL),
			GROWN_RADIUS = (PENTAGRAM_RADIUS_FINAL + GROW_RADIUS),
		};

		#define eye_is_open(bit) ( \
			u3.eyes_open & bit \
		)

		// ZUN bloat: Just a more pedantic version of the one above.
		#define eye_is_open_pedantic(bit) ( \
			eye_is_open(bit) == bit \
		)

		phase.frame_common();
		u1.unused++;
		eyes_foreach_if(eye_is_open_pedantic, locked_unput_and_put_8);
		if(hit.invincible && (after_hit_frames == 0)) {
			u3.eyes_open <<= 1;
			after_hit_frames = 1;
			if(u3.eyes_open == EF_RESET) {
				u3.eyes_open = EF_WEST;
			}
		} else if(after_hit_frames > 0) {
			eyes_toggle_and_yokoshima_recolor(
				(u3.eyes_open == EF_WEST) ? EF_NORTH : (u3.eyes_open >> 1),
				u3.eyes_open,
				COMPONENT_COUNT,
				COMPONENT_COUNT,
				after_hit_frames
			);
			if(after_hit_frames >= EYE_TOGGLE_FRAMES) {
				after_hit_frames = 0;
				u1.unused = 0;
			}
		} else {
			eyes_foreach_if(eye_is_open, track_player);
		}

		if(
			(u2.unused == 0) &&
			((boss_phase_frame % pattern_interval) == 0) &&
			!pentagram_in_slam_phase(pentagram_.phase)
		) {
			for(i = 0; i < PENTAGRAM_POINTS; i++) {
				angle.tmp = iatan2(
					(pentagram.y[i] - pentagram.center.y),
					(pentagram.x[i] - pentagram.center.x)
				);
				Pellets.add_single(
					pentagram.x[i], pentagram.y[i], angle.tmp, to_sp(3.0f)
				);
			}
		}

		pentagram_prepare_update(pentagram_, PAP_PREPARE_1);
		pentagram_prepare_update(pentagram_, PAP_PREPARE_2);
		if(pentagram_in_clockwise_spin_phase(pentagram_.phase)) {
			if(pentagram_spin_unput_update_render(pentagram_, CLOCKWISE)) {
				reinterpret_cast<int &>(pentagram_.phase)++;
				boss_phase_frame = 0;
			}
		}
		if(pentagram_in_counterclockwise_spin_phase(pentagram_.phase)) {
			if(pentagram_spin_unput_update_render(
				pentagram_, COUNTERCLOCKWISE
			)) {
				reinterpret_cast<int &>(pentagram_.phase)++;
				boss_phase_frame = 0;
				pentagram.aim(player_left, player_bottom());
			}
		} else if(pentagram_.phase == PAP_SLAM_INTO_PLAYER_1) {
			if(pentagram_slam_unput_update_render(
				pentagram_, (PLAYER_H + 4 + PENTAGRAM_RADIUS_FINAL), false
			)) {
				phase.back_from_13_to_10(PAP_PREPARE_2);
			}
		} else if(pentagram_.phase == PAP_GROW) {
			if((boss_phase_frame % PENTAGRAM_INTERVAL) == 0) {
				pentagram.radius++;
				pentagram_.spin(CLOCKWISE);
				pentagram_.unput_update_render_regular();
			}
			if(boss_phase_frame >= SUBPHASE_TIMEOUT_FRAMES) {
				pentagram_.phase = PAP_SLAM_INTO_PLAYER_2;
				boss_phase_frame = 0;
				pentagram.aim(player_left, player_bottom());
			}
		}
		if(pentagram_.phase == PAP_SLAM_INTO_PLAYER_2) {
			if(pentagram_slam_unput_update_render(
				pentagram_, (GROWN_RADIUS + (PLAYER_H - 6)), true
			)) {
				phase.back_from_13_to_10(PAP_PREPARE_1);
			}
		}
		hit.update_and_render(flash_colors);
		yuugenmagan_defeat_if((boss_hp <= HP_PHASE_13_END), true, i);

		#undef eye_is_open_pedantic
		#undef eye_is_open
	}
}

void eyes_toggle_and_yokoshima_recolor(
	eye_flag_t eyes_to_close,
	eye_flag_t eyes_to_open,
	int yokoshima_comp_dec,
	int yokoshima_comp_inc,
	int& frame
)
{
	#define eye_should_be_closed(bit) ( \
		eyes_to_close & bit \
	)

	#define eye_should_be_opened(bit) ( \
		eyes_to_open & bit \
	)

	#define eye_is_toggled(bit) ( \
		((eyes_to_close & bit) == bit) || ((eyes_to_open & bit) == bit) \
	)

	eyes_foreach_if(eye_is_toggled, locked_unput_and_put_8);
	frame++;

	// ZUN quirk: That's a color change on every frame *except* the 10th one...
	if((frame % 10) != 0) {
		if(yokoshima_comp_dec < COMPONENT_COUNT) {
			// This clamping condition is actually rather important to keep
			// [stage_palette] from running into negative numbers.
			if(z_Palettes[COL_YOKOSHIMA].v[yokoshima_comp_dec] > 0) {
				z_Palettes[COL_YOKOSHIMA].v[yokoshima_comp_dec]--; // ZUN bloat
				stage_palette[COL_YOKOSHIMA].v[yokoshima_comp_dec]--;
			}
		}
		if(yokoshima_comp_inc < COMPONENT_COUNT) {
			// ZUN quirk: No equivalent clamping condition here. The final
			// color in [z_Palettes] is clamped to 0xF, but there's nothing to
			// prevent the [stage_palette] version from running past 0xF.
			// If a component that was previously incremented like this is then
			// decremented in subsequent recoloring operations, this overflow
			// manifests itself as a noticeable delay: The component will spend
			// most of the recoloring time above 0xF, and only fall back into
			// the valid color range at the *end* of the recoloring phase. If
			// the previously component additionally started out with a non-0x0
			// value (which is the case for the blue component in the original
			// game), decrementing it for a constant amount of frames can only
			// ever reach that brighter initial value again.
			z_Palettes[COL_YOKOSHIMA].v[yokoshima_comp_inc]++; // ZUN bloat
			stage_palette[COL_YOKOSHIMA].v[yokoshima_comp_inc]++;
		}

		// ZUN bloat: z_palette_set_show(COL_YOKOSHIMA) is enough.
		z_palette_set_all_show(stage_palette);
	}

	// Matches the animation in phase_0_eye_open().
	if(frame == ((EYE_OPENING_FRAMES / 3) * 1)) {
		eyes_set_image(eyes_to_close, C_HALFOPEN);
		eyes_set_image(eyes_to_open, C_CLOSED);
		eyes_foreach_if(eye_should_be_opened, hitbox_orb_activate);
	} else if(frame == ((EYE_OPENING_FRAMES / 3) * 2)) {
		eyes_set_image(eyes_to_close, C_CLOSED);
		eyes_set_image(eyes_to_open, C_HALFOPEN);
		eyes_foreach_if(eye_should_be_closed, hitbox_orb_deactivate);
	} else if(frame == ((EYE_OPENING_FRAMES / 3) * 3)) {
		eyes_set_image(eyes_to_close, C_HIDDEN);
		eyes_set_image(eyes_to_open, C_AHEAD);
	}

	#undef eye_should_be_closed
	#undef eye_should_be_opened
	#undef eye_is_toggled
}

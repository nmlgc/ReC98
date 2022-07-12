/// Jigoku Stage 10 Boss - Mima
/// ---------------------------

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/dir.hpp"
#include "th01/math/polar.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th01/hardware/egc.h"
extern "C" {
#include "th01/hardware/graph.h"
#include "th01/hardware/palette.h"
#include "th01/snd/mdrv2.h"
}
#include "th01/formats/grp.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/sprites/pellet.h"
#include "th01/main/playfld.hpp"
#include "th01/main/vars.hpp"
#include "th01/shiftjis/fns.hpp"
#undef MISSILE_FN
#define MISSILE_FN boss3_m_ptn_0
extern const char MISSILE_FN[];
#include "th01/main/particle.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/missile.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/hud/hp.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/stage/palette.hpp"

// Coordinates
// -----------

static const pixel_t MIMA_W = 128;
static const pixel_t MIMA_H = 160;

static const pixel_t MIMA_ANIM_TOP = 48; // relative to the sprite's top edge
static const pixel_t MIMA_ANIM_H = 64;

static const screen_y_t BASE_CENTER_Y = (
	PLAYFIELD_TOP + ((PLAYFIELD_H / 42) * 17)
);

static const screen_y_t BASE_TOP = (BASE_CENTER_Y - (MIMA_H / 2));

// Not quite matching the image, but close enough.
static const pixel_t SEAL_RADIUS = 80;

// The radius of the circumscribed square around a circle with radius 𝓇 is
// 𝓇 * √2; see https://www.desmos.com/calculator/u8mtn9y9wo.
static const pixel_t SEAL_CIRCUMSQUARE_RADIUS = static_cast<pixel_t>(
	SEAL_RADIUS * 1.41f
);
// -----------

#define meteor_active	mima_meteor_active
#define spreadin_interval	mima_spreadin_interval
#define spreadin_speed	mima_spreadin_speed
#define flash_colors	mima_flash_colors
#define invincibility_frame	mima_invincibility_frame
#define invincible	mima_invincible
#define initial_hp_rendered	mima_initial_hp_rendered
extern int invincibility_frame;
extern bool16 invincible;
extern bool initial_hp_rendered;

// Whether meteor_put() has any effect.
extern bool meteor_active;

// Amount of frames between the individual steps of the spread-in transition
extern uint8_t spreadin_interval;

// Sprite pixels to spread in per frame, in one half of Mima's sprite
extern uint8_t spreadin_speed;

// File names
// ----------

extern const char boss3_1_bos[];
extern const char boss3_2_bos[];
extern const char boss3_grp_0[];
extern const char boss5_gr_grc[];
// ----------

// Entities
// --------

static const int METEOR_CELS = 4;

enum anim_cel_t {
	C_CAST = 0,
	C_METEOR = 1,
	C_METEOR_last = (C_METEOR + METEOR_CELS - 1),
};

#define ent_still \
	reinterpret_cast<CBossEntitySized<MIMA_W, MIMA_H> &>(boss_entities[0])

#define ent_anim 	boss_entities[1]

inline void mima_ent_load(void) {
	ent_still.load(boss3_1_bos, 0);
	ent_anim.load(boss3_2_bos, 1);
}

inline void mima_ent_free(void) {
	bos_entity_free(0);
	bos_entity_free(1);
}
// --------

// .PTN
// ----

static const main_ptn_slot_t PTN_SLOT_BG_ENT = PTN_SLOT_BOSS_1;
static const main_ptn_slot_t PTN_SLOT_MISSILE = PTN_SLOT_BOSS_2;

// Three unused background .PTN IDs, for three unused 32×32 animations?
static const int BG_ENT_OFFSET = 3;
// ----

// Patterns
// --------

#define pattern_state mima_pattern_state
extern union {
	subpixel_t speed;
} pattern_state;
// --------

void mima_load(void)
{
	int col;
	int comp;

	mima_ent_load();
	grp_palette_load_show(boss3_grp_0);
	palette_copy(boss_post_defeat_palette, z_Palettes, col, comp);
	void mima_setup(void);
	mima_setup();
	ptn_new(
		PTN_SLOT_BG_ENT,
		(((MIMA_W / PTN_W) * (MIMA_H / PTN_H)) + BG_ENT_OFFSET + 1)
	);
	Missiles.load(PTN_SLOT_MISSILE);
	Missiles.reset();
}

inline void ent_anim_sync_with_still(void) {
	ent_anim.pos_cur_set(
		ent_still.cur_left, (ent_still.cur_top + MIMA_ANIM_TOP)
	);
}

inline void ent_anim_sync_with_still_and_put_both(int cel) {
	ent_anim_sync_with_still();
	ent_anim.set_image(cel);
	graph_accesspage_func(1);	ent_anim.put_8(cel);
	graph_accesspage_func(0);	ent_anim.put_8(cel);
}

void meteor_put(void)
{
	if(meteor_active && ((boss_phase_frame % 8) == 0)) {
		ent_anim_sync_with_still();
		ent_anim.set_image_unput_and_put_8(
			(C_METEOR + ((boss_phase_frame / 8) % METEOR_CELS))
		);
	}
}

void mima_put_cast_both(void)
{
	// ZUN bug: Does not unblit the meteor if `true`, and C_CAST does not
	// completely overlap any C_METEOR cel. In that case, small parts of the
	// meteor are guaranteed to be left in VRAM until they're unblitted as a
	// result of another sprite flying over them.
	meteor_active = false;

	ent_anim_sync_with_still_and_put_both(C_CAST);
}

void meteor_activate(void)
{
	if(!meteor_active) {
		meteor_active = true;
		ent_anim_sync_with_still_and_put_both(C_METEOR);
	}
}

void mima_put_still_both(void)
{
	graph_accesspage_func(1);	ent_still.put_8();
	graph_accesspage_func(0);	ent_still.put_8();
}

void mima_bg_snap(void)
{
	int ptn_x;
	int ptn_y;
	screen_x_t left = ent_still.cur_left;
	screen_y_t top = ent_still.cur_top;
	int image = BG_ENT_OFFSET;

	ptn_snap_rect_from_1_8(
		left, top, MIMA_W, MIMA_H, PTN_SLOT_BG_ENT, image, ptn_x, ptn_y
	);
}

void mima_unput(bool16 just_the_animated_part = false)
{
	int ptn_x;
	int image = BG_ENT_OFFSET;
	screen_x_t left = ent_still.cur_left;
	screen_y_t top = ent_still.cur_top;

	if(!just_the_animated_part) {
		int ptn_y;
		ptn_put_rect_noalpha_8(
			left, top, MIMA_W, MIMA_H, PTN_SLOT_BG_ENT, image, ptn_x, ptn_y
		);
		return;
	}

	// (The code below is never executed in the original game.)

	// Advance to the .PTN background row that contains the background behind
	// the animating part of Mima's sprite (i.e., the second one)
	image = (BG_ENT_OFFSET + ((MIMA_ANIM_TOP / PTN_H) * (MIMA_W / PTN_W)));

	// And since MIMA_ANIM_TOP is only a multiple of 16 and not 32, we have to
	// first awkwardly unblit a MIMA_W×16 area...
	for(ptn_x = 0; ptn_x < (MIMA_W / PTN_W); ptn_x++) {
		ptn_put_quarter_noalpha_8(
			(left + (0 * PTN_QUARTER_W) + (ptn_x * PTN_W)),
			(top + MIMA_ANIM_TOP),
			PTN_ID(PTN_SLOT_BG_ENT, image),
			(((MIMA_ANIM_TOP % PTN_H) / PTN_QUARTER_H) * 2)
		);
		ptn_put_quarter_noalpha_8(
			(left + (1 * PTN_QUARTER_W) + (ptn_x * PTN_W)),
			(top + MIMA_ANIM_TOP),
			PTN_ID(PTN_SLOT_BG_ENT, image),
			((((MIMA_ANIM_TOP % PTN_H) / PTN_QUARTER_H) * 2) + 1)
		);
		image++;
	}

	// ZUN bug (?): Why is MIMA_ANIM_H assumed to be 48 (16 above + 32 here)?
	// This might have even worked if the bottom 16 pixels of all [ent_anim]
	// cels were identical, but they differ between C_CAST and C_METEOR.
	//
	// Note that this has nothing to do with Mima's infamous "third arm"
	// (remember, the game never executes this code), but wouldn't exactly
	// prevent it from happening either.
	#define bug_top (top + MIMA_ANIM_TOP + PTN_QUARTER_H)
	ptn_put_row_noalpha_8(left, bug_top, MIMA_W, PTN_SLOT_BG_ENT, image, ptn_x);
	#undef bug_top
}

inline void mima_unput_both(void) {
	graph_accesspage_func(1);	mima_unput();
	graph_accesspage_func(0);	mima_unput();
}

inline pixel_t spreadin_bottom_cur(void) {
	return ((spreadin_speed / spreadin_interval) * (boss_phase_frame - 10));
}

static const int KEYFRAME_SPREADIN_START = 10;

// Renders a frame of the spread-in animation that ultimately ends in a full
// Mima at the given position. Sets [boss_phase_frame] to 0 to indicate that
// the animation completed.
void phase_spreadin(screen_x_t final_left, screen_y_t final_top)
{
	pixel_t row;
	pixel_t line_on_top;

	if(boss_phase_frame < KEYFRAME_SPREADIN_START) {
		return;
	} else if(boss_phase_frame == KEYFRAME_SPREADIN_START) {
		ent_still.pos_cur_set(final_left, final_top);
		mima_bg_snap();
		line_on_top = (final_top + (MIMA_H / 2));
		return;
	} else if((boss_phase_frame % spreadin_interval) != 0) {
		return;
	}

	line_on_top = ((MIMA_H / 2) - spreadin_bottom_cur());
	if(line_on_top < 0) {
		boss_phase_frame = 0;
		mima_put_still_both();
		return;
	}
	for(row = 0; spreadin_bottom_cur() > row; row++) {
		ent_still.unput_and_put_1line(
			final_left, (final_top + line_on_top + row), ent_still.image(), row
		);
		ent_still.unput_and_put_1line(
			final_left,
			((final_top + MIMA_H) - line_on_top - row),
			ent_still.image(),
			((MIMA_H - 1) - row)
		);
	}
}

// Only called while Mima isn't visible anyway. But even apart from that, it
// barely would have any effect anywhere, as the Mima sprite is blitted to both
// VRAM pages. This *might* have been supposed to crossfade between various
// cels? …Nah, why would you do that by blitting whole lines.
void mima_vertical_sprite_transition_broken(void)
{
	if((boss_phase_frame < 10) || ((boss_phase_frame % 4) != 0)) {
		return;
	}
	pixel_t half_h = ((boss_phase_frame - 10) * 2);
	if(half_h >= (MIMA_H / 2)) {
		boss_phase_frame = 0;
		return;
	}
	// And besides, *VRAM width*?! This is completely broken.
	egc_copy_rect_1_to_0_16(
		ent_still.cur_left, (ent_still.cur_top + half_h), ent_still.vram_w, 8
	);
	egc_copy_rect_1_to_0_16(
		ent_still.cur_left,
		(ent_still.cur_top + (MIMA_H - 8) - half_h),
		ent_still.vram_w,
		8
	);
}

void mima_setup(void)
{
	boss_palette_snap();
	ent_still.set_image(0);
	ent_anim.set_image(C_METEOR);
	z_palette_white_in();
	ent_still.pos_set((PLAYFIELD_CENTER_X - (MIMA_W / 2)), PLAYFIELD_TOP);
	ent_still.hitbox_orb_set(
		((MIMA_W / 8) * 1), ((MIMA_H / 10) * 1),
		((MIMA_W / 8) * 7), ((MIMA_H / 10) * 9)
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
	mima_ent_free();
	ptn_free(PTN_SLOT_BG_ENT);
	ptn_free(PTN_SLOT_MISSILE);
}

#define select_for_rank mima_select_for_rank
#include "th01/main/select_r.cpp"

// Rotating square
// ---------------

static const int SQUARE_POINTS = 4;
static const int SQUARE_INTERVAL = 8;
static const pixel_t SQUARE_RADIUS_PER_FRAME = 1;
static const pixel_t SQUARE_RADIUS_STEP = (
	SQUARE_INTERVAL * SQUARE_RADIUS_PER_FRAME
);

void pascal near regular_polygon(
	screen_x_t *corners_x,
	screen_y_t *corners_y,
	screen_x_t center_x,
	screen_y_t center_y,
	pixel_t radius,
	unsigned char angle,
	int points
)
{
	for(int i = 0; i < points; i++) {
		corners_x[i] = polar_x(center_x, radius, angle);
		corners_y[i] = polar_y(center_y, radius, angle);
		angle += (0x100 / points);
	}
}

struct SquareState {
	unsigned char angle;
	pixel_t radius;

	void init(void) {
		radius = static_cast<pixel_t>(SEAL_RADIUS * 0.4f);
		angle = 0x00;
	}
};

// Pseudo-structure for all local square data, since the original set of data
// unfortunately is both partly stored in registers, and located on the stack
// in a way that prevents even parts of it to be turned into a structure.
// MODDERS: Turn into a proper template class, with all the macros below as
// methods.
#define SquareLocal(name) \
	screen_x_t name##_corners_x[SQUARE_POINTS]; \
	screen_y_t name##_corners_y[SQUARE_POINTS]; \
	screen_x_t name##_center_x; \
	screen_y_t name##_center_y;

#define SquareLocal2(name) \
	screen_x_t name##_corners_ccw_x[SQUARE_POINTS]; \
	screen_y_t name##_corners_ccw_y[SQUARE_POINTS]; \
	screen_x_t name##_corners_cw_x[SQUARE_POINTS]; \
	screen_y_t name##_corners_cw_y[SQUARE_POINTS]; \
	screen_x_t name##_center_x; \
	screen_y_t name##_center_y;

#define square_center_set(sql) { \
	sql##_center_x = ent_still.cur_center_x(); \
	sql##_center_y = ent_still.cur_center_y(); \
}

#define square_corners_set(sql, corners, radius, angle) { \
	regular_polygon( \
		corners##_x, \
		corners##_y, \
		sql##_center_x, \
		sql##_center_y, \
		radius, \
		angle, \
		SQUARE_POINTS \
	); \
}

#define square_unput(corners) { \
	graph_r_lineloop_unput(corners##_x, corners##_y, SQUARE_POINTS); \
}

#define square_put(corners) { \
	graph_r_lineloop_put(corners##_x, corners##_y, SQUARE_POINTS, V_WHITE); \
}

#define square_set_coords_and_unput(sql, corners, radius, angle) { \
	square_center_set(sql); \
	square_corners_set(sql, corners, radius, angle); \
	square_unput(corners); \
}

#define square_set_coords_and_put(sql, corners, radius, angle) { \
	/* (always redundant in context) */ \
	square_corners_set(sql, corners, radius, angle); \
	\
	square_put(corners); \
}
// ---------------

#define fire_static_from_corner(angle, sql, corner_x, corner_y, speed) { \
	angle = iatan2((corner_y - sql_center_y), (corner_x - sql_center_x)); \
	Pellets.add_single(corner_x, corner_y, angle, speed); \
}

void pattern_aimed_then_static_pellets_from_square_corners(void)
{
	#define sq	pattern0_sq

	extern SquareState sq;
	SquareLocal(sql);

	if(boss_phase_frame < 100) {
		return;
	}
	if(boss_phase_frame == 100) {
		sq.init();
		select_subpixel_for_rank(pattern_state.speed, 4.0f, 4.5f, 5.0f, 5.5f);
		mdrv2_se_play(8);
	}
	if((boss_phase_frame % SQUARE_INTERVAL) == 0) {
		square_set_coords_and_unput(sql, sql_corners, sq.radius, sq.angle);
		sq.angle += ((boss_phase_frame < 260) ? +0x0C : -0x0C);
		if(sq.radius < SEAL_CIRCUMSQUARE_RADIUS) {
			sq.radius += SQUARE_RADIUS_STEP;
		} else if(boss_phase_frame > 280) {
			// Recurring quirk with all of these patterns: They spawn their
			// bullets at the *previous* corner positions, i.e., the ones
			// calculated for the unblitting call, right before blitting the
			// square at the new position.

			for(int i = 0; i < SQUARE_POINTS; i++) {
				unsigned char angle;
				fire_static_from_corner(
					angle,
					sql,
					sql_corners_x[i],
					sql_corners_y[i],
					pattern_state.speed
				);
				mdrv2_se_play(7);
			}
		} else {
			for(int i = 0; i < SQUARE_POINTS; i++) {
				unsigned char angle = iatan2(
					(player_center_y() - sql_corners_y[i]),
					((player_center_x() - (PELLET_W / 2) - sql_corners_x[i]))
				);
				Pellets.add_single(
					sql_corners_x[i],
					sql_corners_y[i],
					angle,
					(pattern_state.speed / 2)
				);
				mdrv2_se_play(7);
			}
		}
		square_set_coords_and_put(sql, sql_corners, sq.radius, sq.angle);
	}
	if(boss_phase_frame > 360) {
		square_set_coords_and_unput(sql, sql_corners, sq.radius, sq.angle);
		boss_phase_frame = 0;
	}

	#undef sq
}

void pattern_aimed_missiles_from_square_corners(void)
{
	#define sq         	pattern1_sq
	#define target_left	pattern1_target_left

	extern SquareState sq;
	SquareLocal(sql);
	int i;
	Subpixel velocity_x;
	Subpixel velocity_y;
	extern screen_x_t target_left;

	if(boss_phase_frame < 100) {
		return;
	}
	if(boss_phase_frame == 100) {
		sq.init();
		select_subpixel_for_rank(pattern_state.speed, 6.0f, 6.5f, 7.0f, 7.375f);
		mdrv2_se_play(8);
	}
	if((boss_phase_frame % SQUARE_INTERVAL) == 0) {
		square_set_coords_and_unput(sql, sql_corners, sq.radius, sq.angle);
		sq.angle -= 0x0C;
		if(sq.radius < SEAL_RADIUS) {
			sq.radius += SQUARE_RADIUS_STEP;
		} else if(boss_phase_frame == 224) {
			target_left = player_left;
		} else if(boss_phase_frame > 240) {
			// Same corner coordinate quirk as seen in the first pattern.

			vector2_between(
				sql_center_x,
				sql_center_y,
				(target_left + (PLAYER_W / 2) - (MISSILE_W / 2)),
				player_center_y(),
				velocity_x.v,
				velocity_y.v,
				pattern_state.speed
			);
			for(i = 0; i < SQUARE_POINTS; i++) {
				Missiles.add(
					sql_corners_x[i],
					sql_corners_y[i],
					velocity_x.to_pixel(),
					velocity_y.to_pixel()
				);
			}
			mdrv2_se_play(6);
		}
		square_set_coords_and_put(sql, sql_corners, sq.radius, sq.angle);
	}
	if(boss_phase_frame > 320) {
		square_set_coords_and_unput(sql, sql_corners, sq.radius, sq.angle);
		boss_phase_frame = 0;
	}

	#undef target_left
	#undef sq
}

void pattern_static_pellets_from_corners_of_two_squares(void)
{
	#define sq	pattern2_sq

	extern SquareState sq;
	SquareLocal2(sql);

	if(boss_phase_frame == 50) {
		mima_put_cast_both();
	}
	if(boss_phase_frame < 100) {
		return;
	}
	if(boss_phase_frame == 100) {
		sq.init();
		select_subpixel_for_rank(pattern_state.speed, 4.0f, 4.5f, 5.0f, 5.5f);
		mdrv2_se_play(8);
	}
	if((boss_phase_frame % SQUARE_INTERVAL) == 0) {
		square_center_set(sql);
		square_corners_set(sql, sql_corners_ccw, sq.radius, sq.angle);
		square_corners_set(sql, sql_corners_cw, sq.radius, (0x00 - sq.angle));
		square_unput(sql_corners_ccw);
		square_unput(sql_corners_cw);

		sq.angle -= 0x06;
		Pellets.spawn_with_cloud = true;

		if(sq.radius < SEAL_CIRCUMSQUARE_RADIUS) {
			sq.radius += SQUARE_RADIUS_STEP;
		} else {
			// Same corner coordinate quirk as seen in the first pattern.

			for(int i = 0; i < SQUARE_POINTS; i++) {
				unsigned char angle;
				fire_static_from_corner(
					angle,
					sql,
					sql_corners_ccw_x[i],
					sql_corners_ccw_y[i],
					pattern_state.speed
				);
				fire_static_from_corner(
					angle,
					sql,
					sql_corners_cw_x[i],
					sql_corners_cw_y[i],
					pattern_state.speed
				);
				mdrv2_se_play(7);
			}
		}
		square_corners_set(sql, sql_corners_ccw, sq.radius, sq.angle);
		square_corners_set(sql, sql_corners_cw, sq.radius, (0x00 - sq.angle));
		square_put(sql_corners_ccw);
		square_put(sql_corners_cw);
		Pellets.spawn_with_cloud = false;
	}
	if(boss_phase_frame > 320) {
		square_center_set(sql); // Not redundant!
		square_corners_set(sql, sql_corners_ccw, sq.radius, sq.angle);
		square_corners_set(sql, sql_corners_cw, sq.radius, (0x00 - sq.angle));
		square_unput(sql_corners_ccw);
		square_unput(sql_corners_cw);
		boss_phase_frame = 0;
		meteor_activate();
	}

	#undef sq
}

void pattern_hop_and_fire_chase_pellets(bool16 do_not_initialize = true)
{
	enum {
		HOP_DISTANCE = (PLAYFIELD_W / 5),
		SPREADIN_INTERVAL = 4,
		SPREADIN_FRAMES = 20,

		KEYFRAME_HOP = 1,
		KEYFRAME_TELEPORT = 4,
		KEYFRAME_HITBOX_ACTIVE = 12,
		KEYFRAME_SPREADIN_DONE = (KEYFRAME_SPREADIN_START + SPREADIN_FRAMES),
	};

	#define hop      	pattern3_hop
	#define direction	pattern3_direction

	extern uint8_t hop;
	extern x_direction_t direction;
	int i;
	int pellet_count;
	unsigned char angle;

	// Most of this could have been statically initialized, and even the random
	// direction wouldn't have required this separate parameter.
	if(!do_not_initialize) {
		hop = -1;
		spreadin_interval = SPREADIN_INTERVAL;
		direction = static_cast<x_direction_t>(rand() % 2);
		spreadin_speed = ((MIMA_H / 2) / (SPREADIN_FRAMES / SPREADIN_INTERVAL));
		return;
	}

	if(hop == static_cast<uint8_t>(-1)) {
		mima_unput_both();
		meteor_active = false;
		hop = 0;
		boss_phase_frame = KEYFRAME_HOP;
	}
	if(hop == 0) {
		ent_still.hitbox_orb_inactive = true;
		mima_vertical_sprite_transition_broken();
	} else {
		if(boss_phase_frame == 4) {
			ent_still.pos_cur_set(
				((direction == X_RIGHT)
					? (PLAYFIELD_LEFT + ((hop - 1) * HOP_DISTANCE))
					: (PLAYFIELD_RIGHT - (hop * HOP_DISTANCE))
				),
				(BASE_TOP - (PLAYFIELD_H / 14)) // Yup, not centered!
			);
			mima_bg_snap();
		}
		if(boss_phase_frame < KEYFRAME_HITBOX_ACTIVE) {
			ent_still.hitbox_orb_inactive = true;
		} else {
			ent_still.hitbox_orb_inactive = false;
		}
		phase_spreadin(ent_still.cur_left, ent_still.cur_top);
	}

	// Spread-in animation done?
	if(boss_phase_frame != 0) {
		return;
	}

	if(hop != 0) {
		if(hop != 4) {
			mima_unput_both();
		}

		select_subpixel_for_rank(
			pattern_state.speed, 1.875f, 2.1875f, 2.5f, 2.8125f
		);
		select_for_rank(pellet_count, 5, 8, 10, 12);

		for(
			(i = 0, angle = 0x00);
			i < pellet_count;
			(i++, angle += (0x100 / pellet_count))
		) {
			Pellets.add_single(
				ent_still.cur_center_x(),
				ent_still.cur_center_y(),
				angle,
				pattern_state.speed,
				PM_CHASE,
				pattern_state.speed
			);
		}
	}
	if(hop >= 4) {
		// MODDERS: Same as mima_put_still_both().
		graph_accesspage_func(1);	ent_still.put_8(0);
		graph_accesspage_func(0);	ent_still.put_8(0);

		z_palette_set_all_show(stage_palette);

		// Prepare a potential next run of this pattern
		hop = -1;
		direction = static_cast<x_direction_t>(X_LEFT - direction);

		meteor_active = true;
		boss_phase_frame = 0;
	} else {
		for(i = 0; i < COLOR_COUNT; i++) {
			z_palette_set_show(
				i,
				(z_Palettes[i].c.r - 0x4),
				(z_Palettes[i].c.g - 0x4),
				(z_Palettes[i].c.b - 0x4)
			);
		}
		hop++;
		boss_phase_frame = KEYFRAME_HOP;
	}

	#undef direction
	#undef hop
}

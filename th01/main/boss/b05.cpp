/// Stage 5 Boss - SinGyoku
/// -----------------------

#include <stddef.h>
#include "platform.h"
#include "decomp.hpp"
#include "pc98.h"
#include "master.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/clamp.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/input.hpp"
extern "C" {
#include "th01/hardware/palette.h"
#include "th01/snd/mdrv2.h"
#include "th01/formats/grp.h"
}
#include "th01/formats/pf.hpp"
#include "th01/sprites/pellet.h"
#include "th01/main/particle.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/vars.hpp"
#include "th01/main/hud/hp.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/stage/palette.hpp"

// Coordinates
// -----------

// SINGYOKU_W and SINGYOKU_H are defined in boss.hpp, as they are needed
// globally, by singyoku_defeat_animate_and_select_route() and as dummy default
// parameters for CBossEntity::pos_set().

static const screen_y_t BASE_CENTER_Y = (
	PLAYFIELD_TOP + ((PLAYFIELD_H / 21) * 5)
);

static const screen_y_t BASE_TOP = (BASE_CENTER_Y - (SINGYOKU_H / 2));
// -----------

// Always denotes the last phase that ends with that amount of HP.
enum singyoku_hp_t {
	HP_TOTAL = 8,
	PHASE_1_END_HP = 6,
	PHASE_2_END_HP = 0,
};

// State that's suddenly no longer shared with other bosses
// --------------------------------------------------------

#define boss_hp         	singyoku_hp
#define boss_phase      	singyoku_phase
#define boss_phase_frame	singyoku_phase_frame
extern int8_t boss_phase;
extern int boss_phase_frame;
extern int boss_hp;
// --------------------------------------------------------

// Entities
// --------

enum singyoku_form_t {
	F_WOMAN = 0,
	F_MAN = 1,

	_singyoku_form_t_FORCE_INT16 = 0x7FFF,
};

static const int SPHERE_CELS = 8;

// That's the position for the left hand, at least. The right hand would be a
// bit further in, but the game doesn't care.
static const pixel_t WOMAN_HAND_DISTANCE_FROM_EDGE = 16;

enum singyoku_flash_cel_t {
	C_SPHERE = 0,
	C_WOMAN = 1,
	C_MAN = 2,

	// Used for adding a singyoku_form_t on top.
	C_FLASH_FORM = C_WOMAN,
};

enum singyoku_person_cel_t {
	C_WOMAN_STILL = 0,
	C_WOMAN_ATTACK_1 = 1,
	C_WOMAN_ATTACK_2 = 2,
	C_MAN_STILL = 3,
	C_MAN_ATTACK = 4,

	// Used for multiplying with a singyoku_form_t.
	C_PERSON_FORM = (C_MAN_STILL - C_WOMAN_STILL),

	// Used for adding (C_PERSON_FORM * singyoku_form_t) on top.
	C_STILL = C_WOMAN_STILL,
	C_ATTACK_1 = C_WOMAN_ATTACK_1,
	C_ATTACK_2 = C_WOMAN_ATTACK_2,
};

#define ent_sphere \
	reinterpret_cast<CBossEntitySized<SINGYOKU_W, SINGYOKU_H> &>( \
		boss_entities[0] \
	)

#define ent_flash 	boss_entities[1]
#define ent_person	boss_entities[2]

inline void singyoku_ent_load(void) {
	ent_sphere.load("boss1.bos", 0);
	ent_flash.load("boss1_2.bos", 1);
	ent_person.load("boss1_3.bos", 2);
}

inline void singyoku_ent_free(void) {
	bos_entity_free(0);
	bos_entity_free(1);
	bos_entity_free(2);
}

// And that's how you avoid the entity position synchronization code that
// plagues Elis: By simply only using a single set of coordinates.
#define ent ent_sphere

#define ent_unput_and_put(ent_with_cel, cel) { \
	ent_with_cel.unput_and_put_8(ent.cur_left, ent.cur_top, cel); \
}
// --------

// Patterns
// --------

#define pattern_state	singyoku_pattern_state
extern union {
	int pellet_count;
	pixel_t speed_in_pixels;
	subpixel_t speed_in_subpixels;
	int unknown;
} pattern_state;
// --------

#define flash_colors	singyoku_flash_colors
#define invincible	singyoku_invincible
#define invincibility_frame	singyoku_invincibility_frame
#define initial_hp_rendered	singyoku_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool16 initial_hp_rendered;

void singyoku_load(void)
{
	int col;
	int comp;

	singyoku_ent_load();

	grp_palette_load_show_sane("boss1.grp");
	palette_copy(boss_post_defeat_palette, z_Palettes, col, comp);
	stage_palette_set(boss_post_defeat_palette);

	void singyoku_setup(void);
	singyoku_setup();
}

void singyoku_setup(void)
{
	boss_palette_snap();
	z_palette_set_all_show(z_Palettes);

	ent.pos_set(PLAYFIELD_RIGHT, PLAYFIELD_TOP, 32);
	ent.hitbox_set(
		((SINGYOKU_W / 4) * 1), ((SINGYOKU_H / 4) * 1),
		((SINGYOKU_W / 4) * 3), ((SINGYOKU_H / 4) * 3)
	);
	ent.hitbox_orb_inactive = false;
	ent_sphere.set_image(0);

	boss_hp = HP_TOTAL;
	hud_hp_first_white = PHASE_1_END_HP;
	hud_hp_first_redwhite = 2; // fully arbitrary, doesn't indicate anything
	boss_phase = 0;

	// (redundant, no particles are shown in this fight)
	particles_unput_update_render(PO_INITIALIZE, V_WHITE);
}

void singyoku_free(void)
{
	singyoku_ent_free();
}

// Rotates the sphere by the given [cel_delta]. [interval] could be used to
// restrict this function to certain [boss_phase_frame] intervals, but it's
// always either 1 or -1 in the original game.
void sphere_rotate_and_render(int interval, int cel_delta)
{
	if((boss_phase_frame % interval) != 0) {
		return;
	}

	// Yeah, why is the CBossEntity image variable 16 bits anywhere else to
	// begin with?
	int8_t image_new = (ent_sphere.image() + cel_delta);
	if(image_new > (SPHERE_CELS - 1)) {
		image_new = 0;
	} else if(image_new < 0) {
		image_new = (SPHERE_CELS - 1);
	}

	ent_sphere.set_image(image_new);
	ent_unput_and_put(ent_sphere, image_new);
}

#define select_for_rank singyoku_select_for_rank
#include "th01/main/select_r.cpp"

// Renders a frame of the sphere rotation, starting from a rotational speed of
// 0 and gradually speeding up.
void sphere_accelerate_rotation_and_render(int cel_delta)
{
	if(boss_phase_frame < 50) {
		ent_sphere.set_image(0);
		if((boss_phase_frame % 4) == 0) {
			ent_unput_and_put(ent_sphere, ent_sphere.image());
		}
		return;
	}
	if(boss_phase_frame == 50) {
		mdrv2_se_play(8);
	}
	if((boss_phase_frame < 100) && ((boss_phase_frame % 4) == 0)) {
		ent_unput_and_put(ent_sphere, ent_sphere.image());

		// Only 60 and 68 are actually divisible by 4. The other conditions
		// can never be true.
		if(
			(boss_phase_frame == 50) ||
			(boss_phase_frame == 60) ||
			(boss_phase_frame == 68) ||
			(boss_phase_frame == 74) ||
			(boss_phase_frame == 78) ||
			(boss_phase_frame == 82) ||
			(boss_phase_frame >  82)
		) {
			sphere_rotate_and_render(1, cel_delta);
		}
	}
}

void sphere_move_rotate_and_render(
	pixel_t delta_x, pixel_t delta_y, int interval = 1, int cel_delta = 1
)
{
	if(delta_y < 0) {
		egc_copy_rect_1_to_0_16(
			ent.cur_left,
			(ent.cur_top + delta_y + SINGYOKU_H),
			SINGYOKU_W,
			-delta_y
		);
	} else if(delta_y > 0) {
		egc_copy_rect_1_to_0_16(ent.cur_left, ent.cur_top, SINGYOKU_W, delta_y);
	}

	// ZUN bug: Why implicitly limit [delta_x] to 8? (Which is actually at
	// least 16, due to egc_copy_rect_1_to_0_16() rounding up to the next
	// word.) The actual maximum value for [delta_x] that doesn't permanently
	// leave sphere parts in VRAM is 23 – at 24, a byte-aligned sphere moves at
	// a speed of 3 VRAM words every 2 frames, outrunning these unblitting
	// calls which only span a single VRAM word every frame in that case.
	if(delta_x > 0) {
		egc_copy_rect_1_to_0_16(ent.cur_left, ent.cur_top, 8, SINGYOKU_H);
	} else if(delta_x < 0) {
		// ZUN bug: Should be (+ delta_x) instead of (- delta_y). While the
		// latter is always positive whenever we get here, it can easily be
		// smaller than [delta_x] if SinGyoku is moving over a large amount of
		// horizontal space. In that case, [delta_y] is smaller, and word
		// alignment doesn't just not consistently cancel out this bug, but
		// in fact makes it worse: (ent.cur_left - delta_y) will then align to
		// a different word than (ent.cur_left + delta_x) on at least a couple
		// of frames during the animation, and the left edge of the unblitted
		// area will be past the right edge of the sphere in the previous
		// frame. As a result, not a single sphere pixel will be unblitted,
		// and a small stripe of the sphere will be left in VRAM for one frame.
		egc_copy_rect_1_to_0_16(
			(ent.cur_left + SINGYOKU_W - delta_y), ent.cur_top, 8, SINGYOKU_H
		);
	}

	// The calling site stops any positive Y movement as soon as SinGyoku's
	// bottom coordinate has reached the bottom of the playfield, so we can get
	// by without any clipping here.
	screen_y_t new_top = (ent.cur_top + delta_y);

	screen_x_t new_left = clamp_max_2(clamp_min_2(
		(ent.cur_left + delta_x), 0), (PLAYFIELD_RIGHT - SINGYOKU_W)
	);

	ent.cur_left = new_left;
	ent.cur_top = new_top;

	// ZUN bug: We unblit the movement delta every frame, but only blit every
	// second frame?! (Then again, this is what prevents sphere parts from
	// remaining in VRAM at [delta_x] values between 17 and 23 inclusive.)
	if((boss_phase_frame % 2) == 0) {
		sphere_rotate_and_render(interval, cel_delta);
	}
}

void pattern_halfcircle_spray_downwards(void)
{
	enum {
		KEYFRAME_FIRE = 100,
		KEYFRAME_FIRE_DONE = 160,

		FIRE_FRAMES = (KEYFRAME_FIRE_DONE - KEYFRAME_FIRE),
	};

	#define angle    	pattern0_angle
	#define direction	pattern0_direction

	extern unsigned char angle;
	extern int8_t direction;

	if(boss_phase_frame == 10) {
		direction = ((rand() % 2) == 1) ? 1 : -1;
	}
	if(boss_phase_frame < KEYFRAME_FIRE) {
		sphere_accelerate_rotation_and_render(direction);
		return;
	}

	if(boss_phase_frame == KEYFRAME_FIRE) {
		select_for_rank(pattern_state.pellet_count, 10, 15, 20, 30);
		angle = (direction == -1) ? 0x00 : 0x80;
	}
	if(boss_phase_frame < KEYFRAME_FIRE_DONE) {
		sphere_rotate_and_render(direction, 1);

		if(
			(boss_phase_frame % (FIRE_FRAMES / pattern_state.pellet_count)) == 0
		) {
			Pellets.add_single(
				(ent.cur_center_x() - (PELLET_W / 2)),
				(ent.cur_center_y() - (PELLET_H / 2)),
				angle,
				to_sp(3.125f)
			);
			angle -= ((direction * 0x80) / pattern_state.pellet_count);
		}
	} else {
		boss_phase_frame = 0;
	}

	#undef direction
	#undef angle
}

void pattern_slam_into_player_and_back_up(void)
{
	#define velocity	pattern1_velocity

	extern point_t velocity;

	if(boss_phase_frame < 100) {
		sphere_accelerate_rotation_and_render(1);
		return;
	}
	if(boss_phase_frame == 100) {
		// Could be a local variable.
		select_for_rank(pattern_state.speed_in_pixels, 4, 4, 5, 6);

		vector2_between(
			(ent.cur_center_x() - (PLAYER_W / 2)),
			(ent.cur_center_y() - (PLAYER_H / 2)),
			player_left,
			player_top,
			velocity.x,
			velocity.y,
			pattern_state.speed_in_pixels
		);
	}

	// Leftover debug code?
	if(velocity.x != -PIXEL_NONE) {
		sphere_move_rotate_and_render(inhibit_Z3(velocity.x), velocity.y);
		if(ent.cur_top > (PLAYFIELD_BOTTOM - SINGYOKU_H)) {
			// Nope, it's in fact a way to differentiate the two subphases of
			// this "pattern", and their completion conditions...
			velocity.x = -PIXEL_NONE;

			// ... except that this variable also fulfills that job.
			velocity.y = -4;
		}
	} else if(velocity.y == -4) { // See?
		sphere_move_rotate_and_render(0, velocity.y);
		// < rather than <= and no clamping? That makes sure that SinGyoku will
		// overshoot the base position.
		if(ent.cur_top < BASE_TOP) {
			velocity.y = 0;
		}
	} else {
		boss_phase_frame = 0;
	}

	// A quadratic hitbox exactly covering all 96 pixels. Actually more lenient
	// than a perfect circular one.
	if(
		!player_invincible &&
		(ent.cur_left <= player_left) &&
		((ent.cur_left + (SINGYOKU_W - PLAYER_W)) >= player_left) &&
		(ent.cur_top >= (player_top - SINGYOKU_H))
	) {
		done = true;
	}

	#undef velocity
}

enum singyoku_transform_keyframe_t {
	TKF_START = 100,
	TKF_TO_PERSON = 105,
	TKF_TO_PERSON_RERENDER = 110,
	TKF_TO_PERSON_DONE = 115,
	TKF_PERSON_ATTACK_1 = 135,
	TKF_EXTERNAL_PATTERN_START = 140,
	TKF_PERSON_ATTACK_2 = 160,
	TKF_PERSON_STILL = 185,
	TKF_EXTERNAL_PATTERN_DONE = 220,
	TKF_TO_SPHERE = 240,
	TKF_TO_SPHERE_RERENDER = 245,
	TKF_TO_SPHERE_DONE = 250,
	TKF_DONE = 260,
};

// Ends its corresponding pattern at TKF_DONE.
void transform_to_person_and_back_to_sphere(
	singyoku_form_t form,
	void pascal on_attack_1() = boss_nop,
	void pascal on_attack_2() = boss_nop,
	void pascal on_still() = boss_nop
)
{
	#define person_cel_for_form (C_PERSON_FORM * form)

	if(boss_phase_frame < TKF_START) {
		sphere_accelerate_rotation_and_render(1);
		return;
	}
	if(boss_phase_frame == TKF_START) {
		ent_unput_and_put(ent_flash, C_SPHERE);
	} else if(
		(boss_phase_frame == TKF_TO_PERSON) ||
		(boss_phase_frame == TKF_TO_PERSON_RERENDER)
	) {
		ent_unput_and_put(ent_flash, (C_FLASH_FORM + form));
	} else if(boss_phase_frame == TKF_TO_PERSON_DONE) {
		ent_unput_and_put(ent_person, (C_STILL + person_cel_for_form));
	} else if(boss_phase_frame == TKF_PERSON_ATTACK_1) {
		ent_person.set_image(C_ATTACK_1 + person_cel_for_form);
		ent_unput_and_put(ent_person, (C_ATTACK_1 + person_cel_for_form));
		on_attack_1();
	} else if(boss_phase_frame == TKF_PERSON_ATTACK_2) {
		// Suggests that there was a male version of C_ATTACK_2 during earlier
		// stages of development?
		ent_person.set_image(C_ATTACK_2 + person_cel_for_form);

		if(form == F_WOMAN) {
			ent_unput_and_put(ent_person, C_WOMAN_ATTACK_2);
		} else {
			ent_unput_and_put(ent_person, C_MAN_ATTACK);
		}
		on_attack_2();
	} else if(boss_phase_frame == TKF_PERSON_STILL) {
		ent_person.set_image(C_STILL + person_cel_for_form);
		ent_unput_and_put(ent_person, (C_STILL + person_cel_for_form));
		on_still();
	} else if(
		(boss_phase_frame == TKF_TO_SPHERE) ||
		(boss_phase_frame == TKF_TO_SPHERE_RERENDER)
	) {
		ent_unput_and_put(ent_flash, (C_FLASH_FORM + form));
	} else if(boss_phase_frame == TKF_TO_SPHERE_DONE) {
		ent_unput_and_put(ent_flash, C_SPHERE);
	} else if(boss_phase_frame == TKF_DONE) {
		ent_unput_and_put(ent_sphere, 0);
		boss_phase_frame = 0;
	}

	if(
		(boss_phase_frame > TKF_PERSON_ATTACK_1) &&
		(boss_phase_frame < TKF_TO_SPHERE) &&
		((boss_phase_frame % 4) == 0)
	) {
		ent_unput_and_put(ent_person, ent_person.image());
	}

	#undef person_cel_for_form
}

void pascal fire_chasing_pellets(void)
{
	subpixel_t chase_speed;

	select_subpixel_for_rank(chase_speed, 3.4375f, 3.625f, 3.875f, 4.0625f);

	Pellets.add_single(
		(ent.cur_center_x() - (PELLET_W / 2)),
		(ent.cur_center_y() - (PELLET_H / 2)),
		(0x00 - 0x10),
		to_sp(1.0f),
		PM_CHASE,
		chase_speed
	);
	Pellets.add_single(
		(ent.cur_center_x() - (PELLET_W / 2)),
		(ent.cur_center_y() - (PELLET_H / 2)),
		(0x80 + 0x10),
		to_sp(1.0f),
		PM_CHASE,
		chase_speed
	);
};

void pascal fire_crossing_pellets(void)
{
	subpixel_t speed;

	select_subpixel_for_rank(speed, 3.75f, 4.375f, 4.6875f, 5.0f);

	Pellets.add_single(
		(ent.cur_left    + WOMAN_HAND_DISTANCE_FROM_EDGE - (PELLET_W / 2)),
		(ent.cur_center_y() - (PELLET_H / 2)),
		(0x40 - 0x10),
		speed
	);
	Pellets.add_single(
		(ent.cur_right() - WOMAN_HAND_DISTANCE_FROM_EDGE + (PELLET_W / 2)),
		(ent.cur_center_y() - (PELLET_H / 2)),
		(0x40 + 0x10),
		speed
	);
}

void pattern_chasing_pellets(void)
{
	transform_to_person_and_back_to_sphere(F_WOMAN);
	if(
		(boss_phase_frame > TKF_EXTERNAL_PATTERN_START) &&
		((boss_phase_frame % 8) == 0) &&
		(boss_phase_frame <= TKF_EXTERNAL_PATTERN_DONE)
	) {
		fire_chasing_pellets();
	}
}

void pattern_crossing_pellets(void)
{
	transform_to_person_and_back_to_sphere(F_WOMAN);
	if(
		(boss_phase_frame > TKF_EXTERNAL_PATTERN_START) &&
		((boss_phase_frame % 8) == 0)
	) {
		fire_crossing_pellets();
	}
}

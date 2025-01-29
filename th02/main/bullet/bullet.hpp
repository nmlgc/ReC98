#include "th01/math/subpixel.hpp"
#include "th02/sprites/main_pat.h"

#define BULLET_COUNT 150

static const pixel_t BOUNCE_MARGIN = 8; // ZUN quirk

// Global parameters for special motion types.
extern struct {
	union {
		Subpixel chase_speed;
		Subpixel gravity_speed;
		int16_t drift_angle;
	} u1;
	union {
		int16_t homing_duration;
		Subpixel drift_speed;
	} u2;

	// See the special motion type comment for why it makes sense that these
	// are 16-bit values, despite being compared against an 8-bit per-bullet
	// field.
	union {
		int16_t turns_max;
		int16_t drift_duration;
	} u3;
} bullet_special;

enum bullet_group_or_special_motion_t {
	// Not a valid group or special motion, due to a potential ZUN bug in
	// group_velocity_set()!
	BG_NONE = 0x00,

	// Groups
	// ------
	// Supported for both pellets and 16×16 bullets, and subject to the same
	// description that applies to TH01's `pellet_group_t`. The resulting
	// angles and speeds can be freely offset via the angle and speed
	// parameters to the bullet_add_*() functions.

	BG_1 = 0x20,
	BG_1_AIMED = 0x19,

	BG_2_SPREAD_NARROW = 0x01,
	BG_2_SPREAD_MEDIUM = 0x02,
	BG_2_SPREAD_WIDE = 0x03,
	BG_2_SPREAD_NARROW_AIMED = 0x04,
	BG_2_SPREAD_MEDIUM_AIMED = 0x05,
	BG_2_SPREAD_WIDE_AIMED = 0x06,
	BG_2_SPREAD_ULTRAWIDE_AIMED = 0x26,

	BG_3_SPREAD_NARROW = 0x07,
	BG_3_SPREAD_MEDIUM = 0x08,
	BG_3_SPREAD_WIDE = 0x09,
	BG_3_SPREAD_NARROW_AIMED = 0x0A,
	BG_3_SPREAD_MEDIUM_AIMED = 0x0B,
	BG_3_SPREAD_WIDE_AIMED = 0x0C,

	BG_4_SPREAD_NARROW = 0x0D,
	BG_4_SPREAD_MEDIUM = 0x0E,
	BG_4_SPREAD_WIDE = 0x0F,
	BG_4_SPREAD_NARROW_AIMED = 0x10,
	BG_4_SPREAD_MEDIUM_AIMED = 0x11,
	BG_4_SPREAD_WIDE_AIMED = 0x12,

	BG_5_SPREAD_NARROW = 0x13,
	BG_5_SPREAD_MEDIUM = 0x14,
	BG_5_SPREAD_WIDE = 0x15,
	BG_5_SPREAD_NARROW_AIMED = 0x16,
	BG_5_SPREAD_MEDIUM_AIMED = 0x17,
	BG_5_SPREAD_WIDE_AIMED = 0x18,

	// Ring out of N bullets.
	BG_2_RING = 0x22,
	BG_4_RING = 0x21,
	BG_8_RING = 0x24,
	BG_16_RING = 0x25,
	BG_32_RING = 0x27,

	// The values are randomized for every bullet within the stack, making them
	// not really feel like stacks in the end. The multi-bullet groups spawn
	// ([angle] + 1) bullets, making BG_1_RANDOM_ANGLE the only group whose
	// random angle can be offset without simultaneously affecting the bullet
	// count.
	// The added speed is within the [0.0f; 2.0f[ range.
	BG_1_RANDOM_ANGLE = 0x1A,
	BG_RANDOM_ANGLE = 0x1B,
	BG_RANDOM_ANGLE_AND_SPEED = 0x1C,

	// Fires a second bullet at (0x80 - [angle]).
	BG_2_SPREAD_HORIZONTALLY_SYMMETRIC = 0x23,
	// ------

	// Special motion types
	// --------------------
	// Only supported for 16×16 sprite bullets. These types always start with
	// the angle and (tuned) speed passed to bullets_add_16x16().
	// Most of these types are limited by the 16-bit duration or turn values in
	// [bullet_special] and reset the bullet to BG_NONE once its frame or turn
	// counter matches or exceeds the limiter. Since bullets track that counter
	// in the 8-bit [u1] field, setting the respective limiter to ≥256 prevents
	// this reset.

	BG_SPECIAL_MOTIONS = 0x80,

	// Adjusts the bullet's velocity by 0 or [bullet_special.u1.chase_speed] in
	// both coordinates on every frame, depending on the location of the player
	// relative to this bullet.
	BSM_CHASE = BG_SPECIAL_MOTIONS,

	// Recalculates the bullet's velocity on every frame to exactly hit the
	// player. Effectively ignores the passed [angle] value past the first
	// frame.
	// Resets to BG_NONE on the [bullet_special.u2.homing_duration]'th frame,
	// before adjusting the velocity.
	BSM_HOMING = 0x81,

	// Halves the bullet's velocity on every 8th [stage_frame], then aims to
	// the player at the bullet's initial speed on the frame the velocity would
	// reach zero.
	// Resets to BG_NONE immediately after max(bullet_special.u3.turns_max, 1)
	// turns.
	BSM_DECELERATE_THEN_TURN_AIMED = 0x82,

	// Accelerates the Y velocity of the bullet by
	// [bullet_special.u1.gravity_speed] every frame.
	// Speed won't be tuned for difficulty level or [playperf].
	BSM_GRAVITY = 0x83,

	// Adds [bullet_special.u1.drift_angle] and [bullet_special.u2.drift_speed]
	// to the bullet's angle and speed and recalculates its velocity on every
	// frame.
	// Resets to BG_NONE on the [bullet_special.u3.drift_duration]'th frame,
	// after adjusting the velocity.
	BSM_DRIFT_ANGLE_AND_SPEED = 0x84,

	// Adds [bullet_special.u1.drift_angle] to the bullet's angle, recalculates
	// its velocity, then applies the BSM_CHASE calculation with
	// [bullet_special.u2.drift_speed] as the chase speed on every frame.
	// Resets to BG_NONE on the [bullet_special.u3.drift_duration]'th frame,
	// after adjusting the velocity.
	BSM_DRIFT_ANGLE_CHASE = 0x85,

	// Bounces the bullet into the opposite direction once it's [BOUNCE_MARGIN]
	// pixels away from the respective edge of the playfield.
	// Resets to BG_NONE immediately after ([bullet_special.u3.turns_max] + 1)
	// turns.
	BSM_BOUNCE_LEFT_RIGHT_TOP_BOTTOM = 0x87,
	BSM_BOUNCE_TOP_BOTTOM = 0x88,

	// ZUN bloat: Equivalent to BG_1.
	BSM_1 = 0xFF,
	// --------------------
};

// ZUN bloat: Should be separate.
void bullets_and_sparks_init(void);

// Spawns a number of bullets according to the given group with corresponding
// velocities, or a single special motion bullet, at (left, top). [speed] is
// tuned according to the currently played difficulty and [playperf]. Special
// motions are only supported for 16×16 reasons, for what seem to be game
// design reasons.
void pascal near bullets_add_pellet(
	screen_x_t left,
	screen_y_t top,
	unsigned char angle,
	uint8_t group,
	subpixel_t speed
);
void pascal near bullets_add_16x16(
	screen_x_t left,
	screen_y_t top,
	unsigned char angle,
	bullet_group_or_special_motion_t group_or_special_motion,
	main_patnum_t patnum,
	subpixel_t speed
);

// Renders a pellet at the given position.
void pascal near pellet_render(screen_x_t left, screen_y_t top);

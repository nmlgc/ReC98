// Enemy formation script format
// -----------------------------
// All [duration] values are scaled based on [enemy_speed] and don't directly
// correspond to frames on any difficulty.

#include "th01/math/subpixel.hpp"

static const uint8_t ENEMY_SPEED_COUNT = 4;

enum enedat_op_code_t {
	// Sets [flag] to [EF_FREE] and stops script execution.
	// Uses `enedat_op_t`.
	EO_STOP = 0x00,

	// Moves the enemy at a fixed velocity.
	// Uses `enedat_op_linear_t`.
	EO_MOVE_LINEAR = 0x01,

	// Moves the enemy along a circular path by calculating a new velocity from
	// the given speed and the sine and cosine of the enemy's current [angle]
	// on every frame.
	// Starts by resetting [angle] to the given starting angle, and then adds
	// [angle_speed] on every frame of the motion.
	// Uses `enedat_op_circular_t`.
	EO_MOVE_CIRCULAR = 0x02,

	// Does nothing for a while.
	// Uses `enedat_op_duration_t`.
	EO_WAIT = 0x03,

	// Moves the enemy in a wavy horizontal or vertical motion by applying a
	// cosine oscillation to the velocity on the sine axis while using a
	// constant velocity on the other axis. Starts by resetting [angle] to
	// 0x00, and then adds [angle_speed] on every frame of the motion.
	// Uses `enedat_op_sine_t`.
	EO_MOVE_SINE_X = 0x04,
	EO_MOVE_SINE_Y = 0x05,

	// Moves the enemy in a straight line at its current velocity.
	// Uses `enedat_op_duration_t`.
	EO_MOVE = 0x06,

	// Moves the enemy with a new velocity calculated from the given speed and
	// the previously set angle.
	// Uses `enedat_op_speed_t`.
	EO_MOVE_WITH_SPEED = 0x07,

	// Like [EO_MOVE_LINEAR], but stops if the enemy's center coordinate
	// intersects with the player sprite on the Y or X axis.
	// Uses `enedat_op_linear_t`.
	EO_MOVE_LINEAR_STOP_AT_PLAYER_Y = 0x08,
	EO_MOVE_LINEAR_STOP_AT_PLAYER_X = 0x09,

	// Like [EO_MOVE_CIRCULAR], but adds a constant vector on top of the
	// recalculated per-frame velocity.
	// Uses `enedat_op_circular_plus_t`.
	EO_MOVE_CIRCULAR_PLUS = 0x0A,

	// Uses `enedat_op_spawn_t`.
	EO_SPAWN = 0x10,

	// Loops a script section for a given number of times, tracked in [loop_i].
	// Unused in the original game, and nonfunctional due to bugs in the
	// implementation. See the landmine in enemy_run().
	// Uses `enedat_op_loop_t`.
	EO_LOOP_ABS = 0x80,
	EO_LOOP_REL = 0x81,

	// Sets the [EPT_CLIP_X] flag.
	// Uses `enedat_op_t`.
	EO_CLIP_X = 0x82,

	// Sets the [EPT_CLIP_BOTTOM] flag.
	// Uses `enedat_op_t`.
	EO_CLIP_BOTTOM = 0x83,

	_enedat_op_code_t_FORCE_UINT8 = 0xFF
};

struct enedat_header_t {
	uint16_t size;
	uint16_t zero;
};

struct enedat_op_t {
	uint8_t code;
};

struct enedat_op_linear_t : public enedat_op_t {
	unsigned char angle;
	SubpixelLength8 speed;
	uint8_t duration;
};

struct enedat_op_circular_base_t : public enedat_op_t {
	unsigned char angle_start;
	SubpixelLength8 speed;
	int8_t angle_speed;
};

struct enedat_op_circular_t : public enedat_op_circular_base_t {
	uint8_t duration;
};

struct enedat_op_duration_t : public enedat_op_t {
	uint8_t duration;
};

struct enedat_op_sine_t : public enedat_op_t {
	SubpixelLength8 speed_on_sine_axis;
	int8_t angle_speed;
	Subpixel8 velocity_on_linear_axis;
	uint8_t duration;
};

struct enedat_op_speed_t : public enedat_op_t {
	SubpixelLength8 speed;
	uint8_t duration;
};

struct enedat_op_circular_plus_t : public enedat_op_circular_base_t {
	Subpixel8 velocity_x_plus;
	Subpixel8 velocity_y_plus;
	uint8_t duration;
};

struct enedat_op_spawn_t : public enedat_op_t {
	int8_t center_x_divided_by_8;
	int8_t center_y_divided_by_8;

	// The original formation with the 0-based ID 5 (Expanding/Contracting
	// Circle) is the only one that uses different sizes per speed for its
	// final four enemies.
	uvram_word_amount_8_t size_words[ENEMY_SPEED_COUNT];

	uint8_t hp[ENEMY_SPEED_COUNT];
	bool clip_x;
	bool clip_bottom;
	int8_t unused;
};

struct enedat_op_loop_t : public enedat_op_t {
	int8_t ip_disp; // At least what it's supposed to be?
	int8_t count;
};

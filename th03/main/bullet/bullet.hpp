#include "th03/main/playfld.hpp"
#include "th03/sprites/main_s16.hpp"

// Constants
// ---------

static const int TRAIL_POINTS_PER_SPRITE = 2;
static const int TRAIL_POINT_COUNT = (
	TRAIL_POINTS_PER_SPRITE * BULLET16_TRAIL_CELS
);
static const int TRAIL_RING_SIZE = 48;
// ---------

enum bullet_group_t {
	BG_1 = 0,
	BG_1_AIMED = 1,

	BG_2_SPREAD_NARROW = 2,
	BG_2_SPREAD_MEDIUM = 3,
	BG_2_SPREAD_WIDE = 4,
	BG_2_SPREAD_NARROW_AIMED = 5,
	BG_2_SPREAD_MEDIUM_AIMED = 6,
	BG_2_SPREAD_WIDE_AIMED = 7,

	BG_3_SPREAD_NARROW = 8,
	BG_3_SPREAD_MEDIUM = 9,
	BG_3_SPREAD_WIDE = 10,
	BG_3_SPREAD_NARROW_AIMED = 11,
	BG_3_SPREAD_MEDIUM_AIMED = 12,
	BG_3_SPREAD_WIDE_AIMED = 13,

	BG_4_SPREAD_NARROW = 14,
	BG_4_SPREAD_MEDIUM = 15,
	BG_4_SPREAD_WIDE = 16,
	BG_4_SPREAD_NARROW_AIMED = 17,
	BG_4_SPREAD_MEDIUM_AIMED = 18,
	BG_4_SPREAD_WIDE_AIMED = 19,

	BG_5_SPREAD_NARROW = 20,
	BG_5_SPREAD_MEDIUM = 21,
	BG_5_SPREAD_WIDE = 22,
	BG_5_SPREAD_NARROW_AIMED = 23,
	BG_5_SPREAD_MEDIUM_AIMED = 24,
	BG_5_SPREAD_WIDE_AIMED = 25,

	BG_1_RANDOM_ANGLE = 26,

	// These spawn ([count] + 1) bullets. The added speed is within the
	// [0.0f; 2.0f[ range.
	// ----------------------------------------------------------------

	BG_RANDOM_ANGLE = 27,
	BG_RANDOM_ANGLE_AND_SPEED = 28,

	// Constrains the random angle to the [-22.5 deg; +22.5 deg[ range.
	BG_RANDOM_CONSTRAINED_ANGLE_AIMED = 29,
	// ----------------------------------------------------------------

	// Ring out of N bullets.
	BG_2_RING = 33,
	BG_4_RING = 32,
	BG_8_RING = 35,
	BG_16_RING = 36,
	BG_32_RING = 37,
	BG_RING = 38,
	BG_2_RING_AIMED = 39,
	BG_4_RING_AIMED = 40,
	BG_8_RING_AIMED = 41,
	BG_16_RING_AIMED = 42,
	BG_32_RING_AIMED = 43,
	BG_RING_AIMED = 44,

	// Fires a second bullet at (0x80 - [angle]).
	BG_2_SPREAD_HORIZONTALLY_SYMMETRIC = 34,

	_bullet_group_t_FORCE_UINT8 = 0xFF
};

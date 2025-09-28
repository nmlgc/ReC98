#include "th01/math/subpixel.hpp"

typedef union {
	unsigned char spread_angle;
	SubpixelLength8 stack_speed;
} bullet_template_delta_t;

// All _AIMED groups define the 0° [angle] as the current player position,
// relative to the bullet origin.
typedef enum {
	// Ignoring [count]. Turned into a stack on Hard, and into a spread on
	// Lunatic.
	BG_SINGLE = 0x00,
	BG_SINGLE_AIMED = 0x01,

	// Multiple random bullets, number in [count]. Both angle and speed are
	// added to the template's [angle] and [speed] values, respectively.
	// The added speed is within the [0.0f; 2.0f[ range.
	BG_RANDOM_ANGLE = 0x1B,
	BG_RANDOM_ANGLE_AND_SPEED = 0x1C,
	// Constrains the random angle to the [-22.5 deg; +22.5 deg[ range.
	BG_RANDOM_CONSTRAINED_ANGLE_AIMED = 0x1D,

	// Ring out of [count] bullets, ignoring [delta].
	// ZUN bug: Must be ≥1 going into the bullets_add_*() functions to prevent
	// divisions by zero ("Divide error"). This is exactly what causes the
	// crash during Kurumi when playing on Easy and with minimum rank.
	BG_RING = 0x26,
	BG_RING_AIMED = 0x2C,

	// [count]-way arc centered around 0°, with [delta.spread_angle]° between
	// each bullet.
	BG_SPREAD = 0x2D,
	BG_SPREAD_AIMED = 0x2E,

	// Multi-bullet stack with varying speeds. Number of bullets in [count],
	// with each subsequent bullet getting faster by [delta.stack_speed].
	BG_STACK = 0x2F,
	BG_STACK_AIMED = 0x30,

	// Will always fire a single bullet, regardless of rank or playperf.
	BG_FORCESINGLE = 0x40,
	BG_FORCESINGLE_RANDOM_ANGLE = 0x1A,
	BG_FORCESINGLE_AIMED = 0x41,

	_bullet_group_t_FORCE_UINT8 = 0xFF
} bullet_group_t;

/// Spawn types
/// -----------
/// Not an enum for consistency with TH05, which uses two components OR'd
/// together.

// Won't spawn bullets at the end of a gather animation. Effectively becomes
// BST_BULLET16 when used outside a gather_t. (Mugetsu's 4th phase actually
// relies on this!)
#define BST_GATHER_ONLY 0

// Conceptually identical to the same constants in TH02, but not worth their
// own header to avoid the duplication.
#define BST_PELLET 1	/* ignoring [patnum] */
#define BST_BULLET16 2

#define BST_GATHER_PELLET 3
#define BST_BULLET16_CLOUD_FORWARDS 4
#define BST_BULLET16_CLOUD_BACKWARDS 5
/// -----------

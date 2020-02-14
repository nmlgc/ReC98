#pragma option -b-

// All _AIMED patterns define the 0° [angle] as the current player position,
// relative to the bullet origin.
typedef enum {
	// Ignoring [count]. Turned into a stack on Hard, and into a spread on
	// Lunatic.
	BP_SINGLE = 0x00,
	BP_SINGLE_AIMED = 0x01,

	// Multiple random bullets, number in [count]. Both angle and speed are
	// added to the template's [angle] and [speed] values, respectively.
	BP_RANDOM_ANGLE = 0x1B,
	BP_RANDOM_ANGLE_AND_SPEED = 0x1C,

	// Ring out of [count] bullets, ignoring [delta].
	BP_RING = 0x26,
	BP_RING_AIMED = 0x2C,

	// [count]-way arc centered around 0°, with [delta.spread_angle]° between
	// each bullet.
	BP_SPREAD = 0x2D,
	BP_SPREAD_RANDOM_ANGLE_AIMED = 0x1D,
	BP_SPREAD_AIMED = 0x2E,

	// Multi-bullet stack with varying speeds. Number of bullets in [count],
	// with each subsequent bullet getting faster by [delta.stack_speed].
	BP_STACK = 0x2F,
	BP_STACK_AIMED = 0x30,

	// Will always fire a single bullet, regardless of rank or playperf.
	BP_FORCESINGLE = 0x40,
	BP_FORCESINGLE_RANDOM_ANGLE = 0x1A,
	BP_FORCESINGLE_AIMED = 0x41,
} bullet_pattern_t;

#pragma option -b

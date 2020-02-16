#pragma option -b-

/// Pattern type components
/// -----------------------
// 0° angle definition, relative to the bullet origin.
#define BPC0_STATIC 0	/* 0° = right */
#define BPC0_AIMED  1	/* 0° = current player position */

// Circular distribution of a number of bullets, given in [spread].
#define BPCC_SPREAD 2 /* [spread]-way arc centered around 0°, with
                         [spread_delta_angle]° between each bullet */
#define BPCC_RING   4 /* Full circle, ignoring [spread_delta_angle] */

// Turns every bullet that would already be fired into a multi-bullet stack
// with varying speeds. Number of bullets in [stack], with each subsequent
// bullet getting faster by [stack_delta_speed].
#define BPCS_STACK  6
/// -----------------------
// Will always fire a single bullet, regardless of rank or playperf.
#define BPCF_SINGLE 14

typedef enum {
	// Turned into a stack on Hard, and into a spread on Lunatic.
	BP_SINGLE = (BPC0_STATIC),
	BP_SINGLE_AIMED = (BPC0_AIMED),

	BP_SPREAD = (BPCC_SPREAD + BPC0_STATIC),
	BP_SPREAD_AIMED = (BPCC_SPREAD + BPC0_AIMED),
	BP_RING = (BPCC_RING),
	BP_RING_AIMED = (BPCC_RING + BPC0_AIMED),
	BP_STACK = (BPCS_STACK),
	BP_STACK_AIMED = (BPCS_STACK + BPC0_AIMED),
	BP_SPREAD_STACK = (BPCS_STACK + BPCC_SPREAD + BPC0_STATIC),
	BP_SPREAD_STACK_AIMED = (BPCS_STACK + BPCC_SPREAD + BPC0_AIMED),
	BP_RING_STACK = (BPCS_STACK + BPCC_RING + BPC0_STATIC),
	BP_RING_STACK_AIMED = (BPCS_STACK + BPCC_RING + BPC0_AIMED),

	// Number of bullets taken from [spread]. Both angle and speed are added
	// to the template's [angle] and [speed] values, respectively.
	BP_RANDOM_ANGLE = 12,
	BP_RANDOM_ANGLE_AND_SPEED = 13,

	BP_FORCESINGLE = (BPCF_SINGLE),
	BP_FORCESINGLE_AIMED = (BPCF_SINGLE + BPC0_AIMED),
} bullet_pattern_t;

/// Spawn types
/// -----------
// Spawns special-moving bullets with BST_NORMAL after the gather animation.
// Effectively becomes BST_NORMAL when used outside a gather_t.
#define BST_GATHER_NORMAL_SPECIAL_MOVE 0xFE

#define BST_NORMAL 0x00
#define BST_GATHER_PELLET 0x01
#define BST_CLOUD_FORWARDS 0x02
#define BST_CLOUD_BACKWARDS 0x03

#define BST_SLOWDOWN 0x10	/* can be OR'd into any of the above */
/// -----------

#pragma option -b

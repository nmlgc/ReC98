/// Group type components
/// ---------------------
// 0° angle definition, relative to the bullet origin.
#define BGC0_STATIC 0	/* 0° = right */
#define BGC0_AIMED  1	/* 0° = current player position */

// Circular distribution of a number of bullets, given in [spread].
#define BGCC_SPREAD 2 /* [spread]-way arc centered around 0°, with
                         [spread_delta_angle]° between each bullet */
#define BGCC_RING   4 /* Full circle, ignoring [spread_delta_angle] */

// Turns every bullet that would already be fired into a multi-bullet stack
// with varying speeds. Number of bullets in [stack], with each subsequent
// bullet getting faster by [stack_delta_speed].
#define BGCS_STACK  6
/// ---------------------
// Will always fire a single bullet, regardless of rank or playperf.
#define BGCF_SINGLE 14

typedef enum {
	// Turned into a stack on Hard, and into a spread on Lunatic.
	BG_SINGLE = (BGC0_STATIC),
	BG_SINGLE_AIMED = (BGC0_AIMED),

	BG_SPREAD = (BGCC_SPREAD + BGC0_STATIC),
	BG_SPREAD_AIMED = (BGCC_SPREAD + BGC0_AIMED),
	BG_RING = (BGCC_RING),
	BG_RING_AIMED = (BGCC_RING + BGC0_AIMED),
	BG_STACK = (BGCS_STACK),
	BG_STACK_AIMED = (BGCS_STACK + BGC0_AIMED),
	BG_SPREAD_STACK = (BGCS_STACK + BGCC_SPREAD + BGC0_STATIC),
	BG_SPREAD_STACK_AIMED = (BGCS_STACK + BGCC_SPREAD + BGC0_AIMED),
	BG_RING_STACK = (BGCS_STACK + BGCC_RING + BGC0_STATIC),
	BG_RING_STACK_AIMED = (BGCS_STACK + BGCC_RING + BGC0_AIMED),

	// Number of bullets taken from [spread]. Both angle and speed are added
	// to the template's [angle] and [speed] values, respectively.
	BG_RANDOM_ANGLE = 12,
	BG_RANDOM_ANGLE_AND_SPEED = 13,

	// Not affected by tuning functions.
	BG_FORCESINGLE = (BGCF_SINGLE),
	BG_FORCESINGLE_AIMED = (BGCF_SINGLE + BGC0_AIMED),
} bullet_group_t;

/// Spawn types
/// -----------
// Spawns special-moving bullets with BST_NORMAL after the gather animation.
// Effectively becomes BST_NORMAL when used outside a gather_t.
#define BST_GATHER_NORMAL_SPECIAL_MOVE 0xFE
// Won't spawn bullets at the end of a gather animation.
#define BST_GATHER_ONLY 0xFF

#define BST_NORMAL 0x00
#define BST_GATHER_PELLET 0x01
#define BST_CLOUD_FORWARDS 0x02
#define BST_CLOUD_BACKWARDS 0x03

#define BST_SLOWDOWN 0x10	/* can be OR'd into any of the above */
/// -----------

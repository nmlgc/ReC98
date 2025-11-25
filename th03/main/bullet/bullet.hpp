#include "th03/main/playfld.hpp"
#include "th03/sprites/main_s16.hpp"

// Constants
// ---------

static const int BULLET_COUNT = 320;
static const int TRAIL_POINTS_PER_SPRITE = 2;
static const int TRAIL_POINT_COUNT = (
	TRAIL_POINTS_PER_SPRITE * BULLET16_TRAIL_CELS
);
static const int TRAIL_RING_SIZE = 48;
// ---------

enum bullet_type_t {
	BT_PELLET = 1,

	// Overrides [sprite_offset] with the default 16×16 bullet sprite at
	// [SO_BULLET16], relative to [pid.so_attack] at spawn time.
	BT_BULLET16_DEFAULT = 2,

	// Pellet flies to a random X position at the top of the other playfield
	// and then respawns as a [BT_PELLET_CLOUD]. Can not collide with anything
	// else.
	// Will always spawn a single pellet, ignoring [bullet_template.group].
	BT_PELLET_TRANSFER = 3,

	// Shows a 32×32-pixel delay cloud animation, then transitions to
	// [BT_PELLET].
	BT_PELLET_CLOUD = 4,

	BT_BULLET16_CUSTOM = 5, // unused

	// ZUN bloat: ZUN could have consistently applied the [accel_type] to every
	// newly spawned bullet instead of defaulting to [BAT_NONE] and only
	// reading [accel_type] when using these redundant bullet types. Especially
	// since these flags are only used for a grand total of two bullet groups.
	BT_PELLET_WITH_ACCEL = 6, // unused
	BT_BULLET16_DEFAULT_WITH_ACCEL = 7,
	BT_BULLET16_CUSTOM_WITH_ACCEL = 8,

	_bullet_type_t_FORCE_UINT8 = 0xFF
};

// Based on TH02's `bullet_group_or_special_motion_t`, with the following
// changes:
//
// • No special motion types
// • No invalid zero value (although passing invalid groups to bullets_add*()
//   is still broken in the same way it was in TH01 and TH02)
// • No ultra-wide aimed 2-spread
// • No pre-made support for stacks. This simplifies the semantics of the
//   randomized groups and removes the asterisk that TH02 required in their
//   documentation.
// • New aimed variants for the fixed power-of-2 ring types, which remained
//   unused in the final game
// • A new aimed and non-aimed N-ring type. Technically obsoletes TH02's fixed
//   power-of-2 types, but ZUN still kept using those throughout the game,
//   presumably to avoid mutating [bullet_template.count] in pattern code.
// • A new [BG_RANDOM_CONSTRAINED_ANGLE_AIMED] type. This type would reappear
//   in TH04's bullet system despite not being used in that game, proving that
//   TH04's overhauled system was indeed based on TH03's.
//
// The resulting angles and speeds are further offset by the [angle] and
// [speed] fields from the bullet template.
enum bullet_group_t {
	BG_1 = 0,
	BG_1_AIMED = 1,

	BG_2_SPREAD_NARROW = 2,
	BG_2_SPREAD_MEDIUM = 3, // unused
	BG_2_SPREAD_WIDE = 4, // unused
	BG_2_SPREAD_NARROW_AIMED = 5,
	BG_2_SPREAD_MEDIUM_AIMED = 6, // unused
	BG_2_SPREAD_WIDE_AIMED = 7, // unused

	BG_3_SPREAD_NARROW = 8,
	BG_3_SPREAD_MEDIUM = 9, // unused
	BG_3_SPREAD_WIDE = 10, // unused
	BG_3_SPREAD_NARROW_AIMED = 11,
	BG_3_SPREAD_MEDIUM_AIMED = 12, // unused
	BG_3_SPREAD_WIDE_AIMED = 13, // unused

	BG_4_SPREAD_NARROW = 14,
	BG_4_SPREAD_MEDIUM = 15,
	BG_4_SPREAD_WIDE = 16,
	BG_4_SPREAD_NARROW_AIMED = 17,
	BG_4_SPREAD_MEDIUM_AIMED = 18,
	BG_4_SPREAD_WIDE_AIMED = 19, // unused

	BG_5_SPREAD_NARROW = 20,
	BG_5_SPREAD_MEDIUM = 21,
	BG_5_SPREAD_WIDE = 22,
	BG_5_SPREAD_NARROW_AIMED = 23,
	BG_5_SPREAD_MEDIUM_AIMED = 24,
	BG_5_SPREAD_WIDE_AIMED = 25, // unused

	BG_1_RANDOM_ANGLE = 26, // unused

	// These spawn ([count] + 1) bullets. The added speed is within the
	// [0.0f; 2.0f[ range.
	// ----------------------------------------------------------------

	BG_RANDOM_ANGLE = 27, // unused
	BG_RANDOM_ANGLE_AND_SPEED = 28,

	// Constrains the random angle to the [-22.5 deg; +22.5 deg[ range.
	BG_RANDOM_CONSTRAINED_ANGLE_AIMED = 29,
	// ----------------------------------------------------------------

	// Ring out of N bullets. The `BG_[count]_RING_AIMED` types are unused.
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

// Acceleration flags
// ------------------

typedef uint8_t bullet_accel_type_t;

static const bullet_accel_type_t BAT_NONE = 0x00;

// Accelerates the Y velocity on each frame, up to a maximum of
// [BULLET_ACCEL_Y_VELOCITY_MAX].
static const bullet_accel_type_t BAT_Y = 0x80;

static const subpixel_length_8_t BULLET_ACCEL_Y_VELOCITY_MAX = TO_SP(5);
// ------------------

struct bullet_template_t {
	PlayfieldPoint center;
	SubpixelLength8 speed;
	unsigned char angle;
	pid_t pid;
	bullet_group_t group;
	bullet_accel_type_t accel_type;

	// Only used for groups that don't imply a fixed number of bullets.
	uint8_t count;

	// ZUN bloat: group_velocity_set() should have just received a mutable
	// reference to the bullet, like in TH02.
	SPPoint velocity_tmp;

	sprite16_offset_t sprite_offset;
	bullet_type_t type;
	bool is_collidable;
	bool is_animated;

	// Renders 16×16 bullets with a trail made up of that bullet's positions
	// during the last [TRAIL_POINT_COUNT] frames. These bullets will only be
	// removed once their last trail point has reached the clipping coordinate.
	// The game only supports up to [TRAIL_RING_SIZE] simultaneous trail
	// bullets across all playfields. Activating trails for pellets does
	// allocate a slot from the trail ring and subjects them to the different
	// clipping rules without any visual effect in exchange.
	bool has_trail;
};
extern bullet_template_t bullet_template;

// Sets default values for a subset of bullet template fields.
void bullet_template_reset_stuff(void);

void bullets_reset(void);

// Spawns new bullets based on the [bullet_template].
void bullets_add(void);

// Like bullets_add(), but overrides [bullet_template.type] with
// [BT_PELLET_TRANSFER].
void bullets_add_transfer_pellet(void);

#include "th03/main/bullet/bullet.hpp"

enum bullet_flag_t {
	BF_FREE = 0,
	BF_PELLET = 1,
	BF_BULLET16 = 2,
	BF_PELLET_TRANSFER = 3,
	BF_PELLET_CLOUD = 4,
	BF_INVALID = 5,

	_bullet_flag_t_FORCE_UINT8 = 0xFF
};

struct bullet_trail_coords_t {
	PlayfieldSubpixel v[TRAIL_POINT_COUNT];
};

struct bullet_trail_t {
	bullet_trail_coords_t center_x;
	bullet_trail_coords_t center_y;
};

struct bullet_t {
	bullet_flag_t flag;
	uint8_t age;
	PlayfieldPoint center;

	// Target X position within the target playfield.
	PlayfieldSubpixel target_center_x_for_target_pid;

	// Target X position relative to the originating playfield. Once [center.x]
	// reaches this position, the bullet is replaced with a new [group_next] of
	// [BF_PELLET_CLOUD] bullets at ([target_center_x_for_target_pid], 2.0f) on
	// the other playfield. [speed_next] and [angle_next] is also factored into
	// the velocity of this new group.
	// Technically redundant with the above value, but ZUN didn't write
	// subpixel-supporting functions for conversions from screen to playfield
	// space, so...
	PlayfieldSubpixel target_center_x_for_origin_pid;

	SPPoint velocity;
	SubpixelLength8 speed_next;
	unsigned char angle_next;
	pid_t pid;
	bullet_group_t group_next;

	sprite16_offset_t sprite_offset;
	bullet_accel_type_t accel_type;

	// ZUN bloat: The game never sets this to `false`. A per-instance `bool`
	// seems quite wasteful for what's supposedly a debugging feature, since
	// [flag] already decides whether a bullet can or can not be collided with.
	bool is_collidable;

	// Cycles through all 16×16 cels if [flag] == [BF_BULLET16], ignored
	// otherwise.
	bool is_animated;

	// ZUN bloat: 3 bytes per instance is at least one too many. At the very
	// leas, the per-instance `bool` could have been replaced by assigning
	// a `nullptr` to [trail], but this could have also been an 8-bit index
	// into [bullet_trail_ring] with a zero value.
	bool has_trail;
	bullet_trail_t near *trail;
};

// State
// -----

extern bullet_t bullets[BULLET_COUNT];

extern bullet_trail_t bullet_trail_ring[TRAIL_RING_SIZE];

// Index of the next `bullet_trail_t` instance within [bullet_trail_ring] to be
// assigned to a bullet with trail sprites.
extern uint8_t bullet_trail_ring_i;
// -----

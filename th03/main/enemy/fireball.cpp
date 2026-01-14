#include "th03/main/enemy/expl.hpp"
#include "th03/main/enemy/efe.hpp"

// Flags
// -----

static const efe_flag_t FF_FALL = 1;
static const efe_flag_t FF_TRANSFER = 2;
// -----

struct fireball_t {
	efe_flag_t flag;
	uint8_t frame;
	PlayfieldPoint center;
	uint8_t explosion_max_enemy_hits_half;
	uint8_t hp;
	pid_t pid;

	// Only influences the size of the explosion hitbox.
	pixel_length_8_t size_pixels;

	uint16_t unused_1[3];
	SPPoint velocity;

	// Target X position within the target playfield.
	PlayfieldSubpixel target_center_x_for_target_pid;

	// Target X position relative to the originating playfield. The fireball
	// transitions from [FF_TRANSFER] to [FF_FALL] once [center.x] reaches this
	// position.
	PlayfieldSubpixel target_center_x_for_origin_pid;

	uint8_t unused_3[3];

	// Assigned to [velocity.y] upon switching to [FF_FALL].
	subpixel_length_8_t fall_velocity_y;

	uint8_t chain_slot;
	uint8_t unused_4[3];
	uint8_t generation;
	int8_t padding[15];

	// ZUN bloat: A regular `fireball_variant_t` would have been much nicer.
	explosion_hittest_against_t& variant_as_eha(void) {
		return static_cast<explosion_hittest_against_t>(
			explosion_max_enemy_hits_half
		);
	};
};

inline void fireball_t_verify(void) {
	efe_subclass_verify(reinterpret_cast<fireball_t *>(nullptr));
}

static const int FIREBALL_COUNT = 24;

// State
// -----

#define fireballs ( \
	reinterpret_cast<fireball_t *>(&efes[EFE_COUNT - FIREBALL_COUNT]) \
)

extern fireball_variant_t variant;
// -----

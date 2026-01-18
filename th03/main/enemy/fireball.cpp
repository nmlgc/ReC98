#include "th03/main/enemy/expl.hpp"
#include "th03/main/enemy/efe.hpp"
#include "th03/sprites/main_s16.hpp"

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

// Constants
// ---------

static const int FIREBALL_COUNT = 24;

static const pixel_t FLY_W = 16;
static const pixel_t FLY_H = 16;
static const pixel_t FALL_W = 32;
static const pixel_t FALL_H = 32;
static const uint8_t FRAMES_PER_CEL = 4;
// ---------

// State
// -----

#define fireballs ( \
	reinterpret_cast<fireball_t *>(&efes[EFE_COUNT - FIREBALL_COUNT]) \
)

extern fireball_variant_t variant;
// -----

void near fireball_put(void)
{
	enum {
		FLY_VRAM_W = (FLY_W / BYTE_DOTS),
		FALL_VRAM_W = (FALL_W / BYTE_DOTS),
	};

	fireball_t near& p = *efe_p.fireball;
	sprite16_offset_t so;
	screen_x_t left;
	screen_y_t top;
	pixel_length_8_t size_half;

	uint8_t cycle = (p.frame % 8u);
	if(p.flag == FF_FALL) {
		// See, if [variant_as_eha] was a regular `fireball_variant_t`, ZUN
		// wouldn't have needed to translate it back into one here.
		so = (
			SO_FIREBALL_FALL -
			(EHA_FIREBALL * FIREBALL_CELS * FALL_VRAM_W) +
			(p.variant_as_eha() * (FIREBALL_CELS * FALL_VRAM_W))
		);
		if(cycle <= (FRAMES_PER_CEL - 1)) {
			so += (FALL_W / BYTE_DOTS);
		}
		sprite16_put_size.set(FALL_W, FALL_H);
		size_half = (FALL_W / 2);
	} else {
		// Or here.
		so = (
			SO_FIREBALL_FLY -
			(EHA_FIREBALL * FIREBALL_CELS * FLY_VRAM_W) +
			(p.variant_as_eha() * (FIREBALL_CELS * FLY_VRAM_W))
		);
		if(cycle <= (FRAMES_PER_CEL - 1)) {
			so += (FLY_W / BYTE_DOTS);
		}
		sprite16_put_size.set(FLY_W, FLY_H);
		size_half = (FLY_W / 2);
	}

	sprite16_clip.reset();
	left = (playfield_fg_x_to_screen(p.center.x, p.pid) - size_half);
	top  = (playfield_fg_y_to_screen(p.center.y, p.pid) - size_half);
	sprite16_put(left, top, so);
}

#include "th03/main/enemy/expl.hpp"
#include "th03/main/enemy/efe.hpp"
#include "th03/main/player/stuff.hpp"
#include "th03/main/difficul.hpp"
#include "th03/main/round.hpp"
#include "th03/math/randring.hpp"
#include "th03/math/vector.hpp"
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

fireball_variant_t variant = FV_BLUE;
uint8_t generation_prev;
// -----

void fireballs_add(void)
{
	#define origin (*efe_p.efe)

	fireball_t near *fireball_p;
	playfield_subpixel_t origin_center_x = origin.center.x;
	screen_x_t screen_x;
	int i;
	playfield_subpixel_t origin_center_y = origin.center.y;
	fireball_p = fireballs;

	static_assert(PLAYER_COUNT == 2);
	pid_t pid_target = (1 - origin.pid);

	subpixel_length_8_t speed;
	for(i = 0; i < FIREBALL_COUNT; (i++, fireball_p++)) {
		if(fireball_p->flag != EFF_FREE) {
			continue;
		}
		fireball_p->flag = FF_TRANSFER;
		fireball_p->center.x.v = origin_center_x;
		fireball_p->center.y.v = origin_center_y;
		fireball_p->pid = origin.pid;

		speed = (
			to_sp(1.25f) +
			(round_speed / 2) +
			randring2_next16_ge_lt_sp(0.0f, 2.0f)
		);

		// Technically not needed because [speed] can at most be
		// 	(3.25f + ([ROUND_SPEED_MAX] / 2)) = 7.1875f
		// but it does make sense as a sanity check.
		if(speed > to_sp8(8.0f)) {
			speed = to_sp8(8.0f);
		}

		fireball_p->fall_velocity_y = speed;
		fireball_p->hp = (variant + 2);
		fireball_p->variant_as_eha() = static_cast<explosion_hittest_against_t>(
			EHA_FIREBALL + variant
		);
		fireball_p->size_pixels = 48;
		fireball_p->unused_4[1] = 0; // ZUN bloat
		fireball_p->generation = (
			(variant == FV_BLUE) ? 0 : (generation_prev + 1)
		);

		// ZUN bloat: Identical to `origin.pid`.
		static_assert(PLAYER_COUNT == 2);
		screen_x = playfield_fg_x_to_screen(origin_center_x, (1 - pid_target));

		if((round_or_result_frame % 512) < 256) {
			origin_center_x = randring2_next16_ge_lt_sp(0.0f, PLAYFIELD_W);
		} else {
			origin_center_x = (
				players[pid_target].center.x.v +
				randring2_next16_ge_lt_sp(0.0f, 32.0f)
			);
		}
		fireball_p->target_center_x_for_target_pid.v = origin_center_x;

		// ZUN bloat: Should write to another variable.
		origin_center_x = playfield_fg_x_to_screen(origin_center_x, pid_target);

		// ZUN bloat: Inlining the calculation avoids overloading the variable.
		speed = (to_sp(4.375f) + (round_speed / 3));
		vector2_between_plus(
			TO_SP(screen_x),
			origin_center_y,
			TO_SP(origin_center_x),
			0,
			0,
			fireball_p->velocity.x.v,
			fireball_p->velocity.y.v,
			speed
		);

		// ZUN bloat: Again, identical to `origin.pid`.
		static_assert(PLAYER_COUNT == 2);
		fireball_p->target_center_x_for_origin_pid.v = screen_x_to_playfield(
			origin_center_x, (1 - pid_target)
		);
		return;
	}

	#undef origin
}

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

#define p (efe_p.fireball)

void near fireball_explosion_flag_update(void)
{
	if(p->frame == 14) {
		p->flag = EFF_EXPLOSION_HITTING_ENEMIES;
	} else if(p->frame == 32) {
		p->flag = EFF_EXPLOSION_IGNORING_ENEMIES;
	} else if(p->frame >= 36) {
		p->flag = EFF_FREE;
	}
}

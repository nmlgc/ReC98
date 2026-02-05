#pragma option -zPmain_04

#include "th03/main/enemy/expl.hpp"
#include "th03/main/enemy/efe.hpp"
#include "th03/main/player/bomb.hpp"
#include "th03/main/player/chain.hpp"
#include "th03/main/player/exatt.hpp"
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
	// ZUN quirk: 14 is two frames after we start rendering a different
	// sprite. This is why we don't use keyframes here, unlike for enemies.
	// (And yes, it's also one cycle later than enemy-originating explosions
	// start hitting enemies.)
	if(p->frame == 14) {
		p->flag = EFF_EXPLOSION_HITTING_ENEMIES;
	} else if(p->frame == 32) {
		p->flag = EFF_EXPLOSION_IGNORING_ENEMIES;
	} else if(p->frame >= 36) {
		p->flag = EFF_FREE;
	}
}

void near fireball_explosion_put(void)
{
	sprite16_offset_t so;
	uint8_t cycle;

	static_assert(EXPLOSION_CELS == 4);
	if(p->frame < 12) {
		so = SO_EXPLOSIONS_64X64[0];
	} else if(p->frame < 32) {
		cycle = (p->frame / 4);
		so = SO_EXPLOSIONS_64X64[1 + (cycle & 1)];
	} else if(p->frame < 36) {
		// ZUN bloat: ^ The condition doesn't need to duplicate the keyframe.
		so = SO_EXPLOSIONS_64X64[3];
	}
	sprite16_put_size.set(64, 64);

	screen_x_t left;
	screen_y_t top;
	left = (playfield_fg_x_to_screen(p->center.x, p->pid) - (64 / 2));
	top  = (playfield_fg_y_to_screen(p->center.y, p->pid) - (48 / 2));

	sprite16_put(left, top, so);
}

void fireballs_update(void)
{
	playfield_subpixel_t next;
	int i;

	// Players can only collide with falling fireballs.
	collmap_stripe_tile_w.set(FALL_W / 2);
	collmap_tile_h.set(FALL_H / 2);

	p = fireballs;
	for(i = 0; i < FIREBALL_COUNT; (i++, p++)) {
		if(p->flag == EFF_FREE) {
			continue;
		}
		p->frame++;

		if(p->flag >= EFF_EXPLOSION_IGNORING_ENEMIES) {
			fireball_explosion_flag_update();
		} else if(p->flag == FF_FALL) {
			next = p->center.x.v;
			next += p->velocity.x.v;
			if(
				(bomb_flag[p->pid] != BF_INACTIVE) ||
				(next <= to_sp(          0 - (FALL_W / 2))) ||
				(next >= to_sp(PLAYFIELD_W + (FALL_W / 2)))
			) {
free_and_continue:
				p->flag = EFF_FREE;
				continue;
			}
			p->center.x.v = next;

			next = p->center.y.v;
			next += p->velocity.y.v;
			if(next >= to_sp(PLAYFIELD_H + (FALL_H / 2))) {
				goto free_and_continue;
			}
			p->center.y.v = next;

			// ZUN bloat: We are already on the [FF_FALL] branch.
			if(p->flag == FF_FALL) {
				collmap_center.x = p->center.x;
				collmap_center.y.v = (
					p->center.y.v + to_sp(FALL_H / 4)
				);
				collmap_pid = p->pid;

				/* TODO: Replace with the decompiled call
				 * 	collmap_set_rect_striped();
				 * once that function is part of the same segment */
				_asm { nop; push cs; call near ptr collmap_set_rect_striped; }
			}
		} else if(p->flag == FF_TRANSFER) {
			next = p->center.x.v;
			next += p->velocity.x.v;

			// ZUN bloat: There are better ways of checking the coordinate than
			// hardcoding the assumption of the physical layout together with
			// the expected horizontal velocity.
			static_assert(PLAYER_COUNT == 2);
			if(p->pid == 0) {
				if(p->target_center_x_for_origin_pid.v <= next) {
switch_to_fall:
					p->center.x = p->target_center_x_for_target_pid;
					p->center.y.set(0.0f);
					p->velocity.x.set(0.0f);
					p->velocity.y.v = p->fall_velocity_y;
					p->flag = FF_FALL;
					p->pid = (1 - p->pid);
					continue;
				}
			} else {
				if(p->target_center_x_for_origin_pid.v >= next) {
					goto switch_to_fall;
				}
			}

			p->center.x.v = next;

			// ZUN bloat: Could have been a one-liner.
			next = p->center.y.v;
			next += p->velocity.y.v;
			p->center.y.v = next;
		}
	}
}

void pascal near chain_fire_charged_exatt(pid_t pid, unsigned int slot)
{
	if(chains.charge_exatt[pid][slot] >= (6 - (round_speed / to_sp(2.0f)))) {
		chains.charge_exatt[pid][slot] = 0;
		exatt_add(efe_p.efe->center.x, efe_p.efe->center.y, pid);
	}
}

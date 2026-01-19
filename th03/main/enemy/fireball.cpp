#pragma option -zPmain_04

#include "th03/main/enemy/expl.hpp"
#include "th03/main/enemy/efe.hpp"
#include "th03/main/player/bomb.hpp"
#include "th03/main/player/chain.hpp"
#include "th03/main/player/exatt.hpp"
#include "th03/main/player/stuff.hpp"
#include "th03/main/difficul.hpp"
#include "th03/main/hitbox.hpp"
#include "th03/main/round.hpp"
#include "th03/main/score.hpp"
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

	// Very inconsistently assigned to newly spawned red fireballs, as
	// explained for the [generation_prev] quirk.
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

// These *could* be turned into parameters to fireballs_add(). Has to be done
// carefully though: explosion_collision_chain_slot_fire_charged_fireball() can
// get called from explosions_hittest() and will read both of these globals:
//
// • The original game spawns red fireballs when explosions_hittest() is called
//   via fireballs_hittest() (which sets [variant] to [FV_RED]), and blue ones
//   ones when explosions_hittest() is called from anywhere else. (See the
//   quirk explanation in fireballs_hittest().)
//
// • ZUN quirk: [generation_prev] is only set *after* a fireball was destroyed.
//   Charged fireballs, however, are spawned *during* explosions_hittest(), and
//   will reuse whatever the last explosion-destroyed fireball wrote to this
//   variable.
//
// The intended values of these parameters would therefore have to be passed
// through the collision detection system as well.
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

	// ZUN bug: (16 / 2) pixels lower than where they should be, and where
	// collision detection constructs its hitbox.
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

// ZUN bloat: This should really be part of the chain translation unit. But
// that would require splitting segments and placing fireballs_hittest() into
// that second segment, which would ruin the far→near conversion of its two
// fireballs_add() calls and thus have an even worse effect on code quality.
void pascal near chain_fire_charged_exatt(pid_t pid, unsigned int slot)
{
	if(chains.charge_exatt[pid][slot] >= (6 - (round_speed / to_sp(2.0f)))) {
		chains.charge_exatt[pid][slot] = 0;
		exatt_add(efe_p.efe->center.x, efe_p.efe->center.y, pid);
	}
}

void near fireballs_hittest(void)
{
	int i;

	// ZUN landmine: This uninitialized variable is the cause behind the
	// infamous rare score reduction and extend glitches. The collision branch
	// below doesn't set this slot if a fireball is destroyed by anything that
	// isn't an explosion, but still passes it to chain_fire_charged_exatt(),
	// where any value ≥ [CHAIN_RING_SIZE] causes an out-of-bounds array
	// access.
	// In ZUN's binary, [score_lebcd] and [extends_gained] happen to be placed
	// 6 and 30 bytes after the end of [chains.charge_exatt], respectively.
	// Hence, if this uninitialized variable ever happens to be
	//
	// 	≥ (([CHAIN_RING_SIZE] × ([PLAYER_COUNT] - <fireball PID>)) + 6) and
	// 	< that number plus ([SCORE_DIGITS] × [PLAYER_COUNT]),
	//
	// the game will interpret a score digit as an Extra Attack charge value,
	// resetting it to 0 if the charge condition is met. These constants
	// translate to slot IDs ≥38 and <54 for P1, and to ID ≥22 and <38 for P2.
	//
	// Similarly, the game will access [extends_gained] if the slot ID happens
	// to be 62 for P1 and 46 for P2. Due to [ROUND_SPEED_MAX] being 7.9375f,
	// the smallest possible Extra Attack chain value would be 3, which would
	// be impossible to reach due to [EXTENDS_MAX] being 2. However, ZUN sets
	// [extends_gained] to 0xFF once P1's score is ≥20 million, thus ensuring
	// that the condition in chain_fire_charged_exatt() will always be true in
	// that case.
	//
	// But how likely is it for this specific stack byte to fall within these
	// ranges? If we trace the flow of code in ZUN's original binary, we almost
	// always see a value of 15 – which just happens to be the highest valid
	// slot number, ([CHAIN_RING_SIZE] - 1). This value is written by the
	// `ENTER` instruction at the start of enemy_explosion_put() and
	// enemy_put(), and represents the top 8 bits of `SP`. This value is as
	// safe and deterministic as it gets, for two reasons:
	//
	// 1) Turbo C++ 4.0J allocates a 4,096-byte stack with `SP` starting at
	//    0x1000 and growing towards 0x0000. Since these blitting functions are
	//    only ever called from a single place two functions above main(), `SP`
	//    is guaranteed to be somewhere within 0x0F00 and 0x0FFF whenever they
	//    get called, ensuring the consistent high byte of 0x0F.
	// 2) Since TH03 immediately spawns the next formation once all active
	//    enemies have exploded or left the playfield, it will always at least
	//    try to render one enemy or enemy-originating explosion on every frame
	//    of gameplay. Even bombs merely cause enemies to explode immediately,
	//    rather than removing them outright.
	//
	// Thus, the glitch can only happen if the system receives an interrupt
	// (from either the keyboard, VSync, or PMD's background task) within the
	// very specific window of CPU instructions between
	//
	// 1) after the end of the final enemy_explosion_put() or enemy_put() call
	//    for a frame, and
	// 2) the beginning of this function.
	//
	// In that case, the CPU must save the current CS:IP pair to the current
	// stack to service the interrupt, which will overwrite the 0x0F value with
	// the high byte of the segment containing the currently active function,
	// most likely enemies_render(). (Note that the interrupt must indeed
	// happen *outside* the two blitting functions for this glitch to occur, as
	// `SP` will already be too low once execution has moved inside.)
	// Due to the required timing, this glitch is very rare even on systems
	// where it *can* happen as a result of enemies_render()'s segment falling
	// into the ranges described above.
	//
	// Thankfully, just initializing this variable to 15 is the correct fix
	// here, and will remove this highly system-specific landmine by locking
	// down the effect of normal code flow. In fact, this *must* be fixed for
	// any build that supports netplay:
	//
	// • Gameplay would desync if one of the peers runs on a glitch-prone
	//   configuration and spawns an additional Extra Attack onto the other
	//   player's field. They won't be able to see and dodge that attack unless
	//   they are running the exact same system configuration.
	// • We'd like to skip rendering during rollback, but that would also skip
	//   the call to enemies_render(), which is the whole reason why this
	//   glitch only happens rarely instead of happening all the time.
	//
	// See https://rec98.nmlgc.net/blog/2026-03-16#glitches for a more in-depth
	// documentation of this glitch and the system configurations that are most
	// likely to cause it.
	uint8_t chain_slot;

	hitbox.radius.set(12, 10);
	p = &fireballs[FIREBALL_COUNT - 1];

	// ZUN quirk: explosions_hittest() will also spawn fireballs as a result of
	// sufficiently high chain charges. This assignment ensures that those
	// fireballs will also be red, contradicting Section 10 of 夢時空.TXT which
	// claims that any red fireball must have been transferred. Quite a
	// significant error in the manual if we consider the vast gameplay
	// differences between blue and red fireballs...
	variant = FV_RED;

	// ZUN bloat: [FIREBALL_COUNT] exists.
	for(i = (EFE_COUNT - 1); i >= (EFE_COUNT - FIREBALL_COUNT); (i--, p--)) {
		if(p->flag != FF_FALL) {
			continue;
		}
		explosion_hittest_against = p->variant_as_eha();
		pid_t pid = p->pid;
		hitbox.origin.center.x.v = p->center.x.v;
		hitbox.origin.center.y.v = (p->center.y.v + to_sp(3.0f));
		hitbox.pid = pid;

		/* TODO: Replace with the decompiled condition
		 * 	if(!hitbox_hittest()) {
		 * once the segmentation allows us to, if ever */
		asm { nop; push cs; call near ptr hitbox_hittest; }
		if(_AL == 0) {
			continue;
		}

		// Checking HP *before* decrementing means that fireballs still live at
		// 0 HP, and are only destroyed if their HP would reach -1, just like
		// enemies.
		if((p->hp == 0) || explosion_collision_in_last_hittest || ef_onehit) {
			generation_prev = p->generation;
			if(explosion_collision_in_last_hittest) {
				// Fireballs only turn into explosions when destroyed by an
				// existing explosion...
				p->flag = EFF_EXPLOSION_IGNORING_ENEMIES;
				chain_slot = explosion_collision_chain_slot;
				p->chain_slot = chain_slot;
				if(explosion_hittest_against == EHA_FIREBALL_RED) {
					chains.charge_exatt[pid][chain_slot]++;
				}
				if(
					chains.charge_exatt[pid][chain_slot] >=
					(7 - (round_speed / to_sp8(2.0f)))
				) {
					chains.charge_exatt[pid][chain_slot] = 0;
					exatt_add(p->center.x, p->center.y, pid);
				}
				if(generation_prev < 4) {
					fireballs_add();
				}
			} else {
				// …and are simply transferred to the other playfield
				// otherwise, without the 4-transfer limit.
				// ZUN quirk: Except that they still contribute to a probably
				// inactive chain?
				chains.charge_exatt[pid][chain_ring_p[pid]] += (
					explosion_hittest_against - 1
				);
				p->flag = EFF_FREE;
				chain_fire_charged_exatt(pid, chain_ring_p[pid]);
				gauge_avail_add(pid, 16);
				score_add(50, pid);
				fireballs_add();
			}

			// See the landmine above.
			chain_fire_charged_exatt(pid, chain_slot);
		} else {
			p->hp--;
		}
		fireball_collision_in_previous_hittest = true;

		// Yup, doing this unconditionally resets the animation cycle on every
		// collision. Too minor to be classified as a quirk though, and maybe
		// even intentional.
		p->frame = 0;
	}
	variant = FV_BLUE;
}

void fireballs_hittest_and_render(void)
{
	fireballs_hittest();
	sprite16_clip.reset();

	p = fireballs;
	for(int i = 0; i < FIREBALL_COUNT; (i++, p++)) {
		if(p->flag == EFF_FREE) {
			continue;
		}
		if(p->flag < EFF_EXPLOSION_IGNORING_ENEMIES) {
			fireball_put();
		} else {
			fireball_explosion_put();
		}
	}
}

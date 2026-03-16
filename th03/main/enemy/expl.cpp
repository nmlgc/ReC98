#include "th03/main/enemy/expl.hpp"
#include "th03/main/enemy/efe.hpp"
#include "th03/main/player/chain.hpp"
#include "th03/main/player/combo.hpp"
#include "th03/main/player/gauge.hpp"
#include "th03/main/difficul.hpp"
#include "th03/main/hitbox.hpp"
#include "th03/main/score.hpp"

uint8_t explosions_hittest(void)
{
	efe_t near *expl_p;
	uint8_t near *charge_fireball_p;
	int i;
	PlayfieldSubpixel x;
	PlayfieldSubpixel y;
	union {
		Subpixel radius;
		Subpixel size;
	} u1;
	int16_t bonus;
	unsigned int collision_count = 0;
	uint8_t hits;

	// • 0 (for [EHA_ENEMY])
	// • 1 (for [EHA_PELLET])
	// • 6 (for [EHA_FIREBALL_BLUE])
	// • 9 (for [EHA_FIREBALL_RED])
	// ZUN bloat: All uses of the [against2] field can be replaced with
	// comparisons against [explosion_hittest_against].
	enum against2_t {
		EHA2_ENEMY = (3 * EHA_ENEMY),
		EHA2_PELLET = EHA_PELLET,
		EHA2_FIREBALL_BLUE = (3 * EHA_FIREBALL_BLUE),
		EHA2_FIREBALL_RED = (3 * EHA_FIREBALL_RED),

		_against2_FORCE_UINT8 = 0xFF
	};
	union {
		against2_t against2;
		uint8_t value;
	} ehm;
	if(explosion_hittest_against == EHA_PELLET) {
		ehm.value = 1;
	} else {
		ehm.value = (3 * explosion_hittest_against);
	}

	expl_p = efes;
	explosion_collision_in_last_hittest = false;

	for(i = 0; i < EFE_COUNT; (i++, expl_p++)) {
		if(expl_p->flag < EFF_EXPLOSION_IGNORING_ENEMIES) {
			continue;
		}

		// Given that the formation scripts always send more than one enemy
		// along the same path, there doesn't seem to be much of a point in
		// restricting the amount of hits they can deal to enemies. Explosions
		// from earlier enemies will cause subsequent enemies to create new
		// explosions right next to existing ones, which come with a fresh hit
		// counter.
		// But since explosions only deal hits every 4 frames, this condition
		// *will* make it less likely for older explosions to hit enemies
		// further along the formation's path, especially if we consider
		// enemies with more then 1 HP. Hence, such enemies will then either
		// explode at slightly different places, or outright require a separate
		// explosion chain in order to get destroyed at all.
		if((explosion_hittest_against == EHA_ENEMY) && (
			(expl_p->flag == EFF_EXPLOSION_IGNORING_ENEMIES) ||
			(expl_p->flag >= (
				EFF_EXPLOSION_HITTING_ENEMIES +
				(expl_p->explosion_max_enemy_hits_half * 2)
			))
		)) {
			continue;
		}

		if(expl_p->pid != hitbox.pid) {
			continue;
		}
		if((expl_p->frame & 3) != 0) {
			continue;
		}
		u1.radius.v = (expl_p->size_pixels * to_sp(0.375f));
		x.v = (expl_p->center.x.v - u1.radius.v);
		y.v = (expl_p->center.y.v - u1.radius.v);
		if((hitbox.right.v < x.v) || (hitbox.bottom.v < y.v)) {
			continue;
		}

		// Necessary for soundness, but Turbo C++ 4.0J only optimizes this away
		// for registers.
		// u1.size.v = u1.radius.v;

		u1.size.v <<= 1;

		x.v += u1.size.v;
		y.v += u1.size.v;
		if((hitbox.origin.topleft.x > x.v) || (hitbox.origin.topleft.y > y.v)) {
			continue;
		}
		explosion_collision_chain_slot = expl_p->chain_slot;
		if(explosion_hittest_against == EHA_ENEMY) {
			// Enemies can live through an explosion.
			expl_p->flag++;
		} else {
			// ZUN quirk: Pellets and fireballs can't. Their combo code is
			// somewhat similar, so we process it here… but this also means
			// that the game awards these chain and score bonuses once for each
			// explosion that hits a pellet or fireball within the same frame.
			hits = chain_hits_inc_and_clamp(
				hits, hitbox.pid, explosion_collision_chain_slot
			);
			if(ehm.against2 == EHA2_PELLET) {
				bonus = (hits * 2);
				score_add(1, hitbox.pid);
			} else if(ehm.against2 == EHA2_FIREBALL_BLUE) {
				bonus = (100 + (hits * 16));
				score_add(40, hitbox.pid);
			} else if(ehm.against2 == EHA2_FIREBALL_RED) {
				bonus = (444 + (hits * 16));
				score_add(80, hitbox.pid);
			}
			bonus += round_speed;
			if(round_speed <= to_sp8(3.0f)) {
				bonus >>= 1;
			} else if(round_speed >= to_sp8(6.0f)) {
				bonus += bonus;
			}

			#define pellet_and_fireball_val hits

			// Yeah, wouldn't it be better if `chains_t` was AoS?
			// (Already counted as bloat in the header.)
			#define pellet_and_fireball_value_p charge_fireball_p
			pellet_and_fireball_value_p = (
				&chains.pellet_and_fireball_value[hitbox.pid][
					explosion_collision_chain_slot
				]
			);
			*pellet_and_fireball_value_p += ehm.value;
			pellet_and_fireball_val = *pellet_and_fireball_value_p;
			#undef pellet_and_fireball_value_p

			charge_fireball_p = &chains.charge_fireball[hitbox.pid][
				explosion_collision_chain_slot
			];
			if(ehm.against2 == EHA2_PELLET) {
				gauge_avail_add(hitbox.pid, 4);
			} else {
				// 18 for blue fireballs, 27 for red fireballs.
				// We don't get here in any other case.
				gauge_avail_add(hitbox.pid, (ehm.value * 3));
			}
			if(pellet_and_fireball_val < 4) {
				*charge_fireball_p += 2;
			} else if(pellet_and_fireball_val < 10) {
				*charge_fireball_p += 5;
			} else if(pellet_and_fireball_val < 20) {
				*charge_fireball_p += 2;
				chains.charge_exatt[hitbox.pid][
					explosion_collision_chain_slot
				]++;
			} else {
				chains.charge_exatt[hitbox.pid][
					explosion_collision_chain_slot
				] += 2;
			}
			bonus = combo_add(
				hitbox.pid, explosion_collision_chain_slot, bonus
			);
			fire_point_based_boss_attack_or_panic(bonus, hitbox.pid);
			explosion_collision_chain_slot_fire_charged_fireball(
				hitbox.pid, expl_p
			);
			#undef pellet_and_fireball_val
		}
		collision_count++;
		explosion_collision_in_last_hittest = true;
	}
	return collision_count;
}

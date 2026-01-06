/// Explosion chain data
/// --------------------

#include "th03/common.h"

// Number of simultaneous, separate explosion chains tracked per player. *Not*
// related to the number of explosions on screen; rather, each explosion is
// assigned one of these slots when it spawns. All further explosions spawned
// from that first explosion will then continue the same chain, adding to its
// hit counter and charge values.
static const int CHAIN_RING_SIZE = 16;

extern uint8_t chain_ring_p[PLAYER_COUNT];

// ZUN bloat: AoS would be much more appropriate for how the game uses these.
struct chains_t {
	uint8_t hits[PLAYER_COUNT][CHAIN_RING_SIZE];

	// Increases by destroying pellets (+1), blue fireballs (+6) and red
	// fireballs (+9), which in turn causes [charge_fireball] and
	// [charge_exatt] to increase relative to this value.
	uint8_t pellet_and_fireball_value[PLAYER_COUNT][CHAIN_RING_SIZE];

	uint8_t charge_fireball[PLAYER_COUNT][CHAIN_RING_SIZE];
	uint8_t charge_exatt[PLAYER_COUNT][CHAIN_RING_SIZE];
};

extern chains_t chains;

// ZUN bloat: One-line wrapper around combo_add_raw().
uint16_t pascal near combo_add(pid_t pid, uint8_t chain_slot, uint16_t bonus);

#pragma codeseg ENEMY_PUT // ZUN bloat

struct efe_t;

// Fires a blue fireball if [pid]'s [charge_fireball] in
// [explosion_collision_chain_slot] exceeds a difficulty-specific threshold
// value, then resets the charge.
// ZUN bloat: Should be generic and take a slot parameter.
void pascal near explosion_collision_chain_slot_fire_charged_fireball(
	pid_t pid, efe_t near *efe
);

#pragma codeseg

// Fires an Extra Attack if [pid]'s [charge_exatt] in the given chain [slot]
// exceeds a difficulty-specific threshold value, then resets the charge.
// ZUN bloat: Reads [efe_p.efe.center]. Should just take a `PlayfieldPoint`
// parameter.
void pascal near chain_fire_charged_exatt(pid_t pid, unsigned int slot);
/// --------------------

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

struct chains_t {
	uint8_t hits[PLAYER_COUNT][CHAIN_RING_SIZE];
};

extern chains_t chains;

// ZUN bloat: One-line wrapper around combo_add_raw().
uint16_t pascal near combo_add(pid_t pid, uint8_t chain_slot, uint16_t bonus);
/// --------------------

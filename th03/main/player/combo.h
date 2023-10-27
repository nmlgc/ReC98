typedef struct {
	unsigned char time;
	unsigned char hits;
	unsigned int bonus;
} combo_t;

#define COMBO_FRAMES 80
#define COMBO_HIT_RESET_FRAMES 32
// Combos aren't started if less than this number of targets were hit at once
#define COMBO_HIT_MIN 2
#define COMBO_HIT_CAP 99
#define COMBO_BONUS_CAP 65535

extern combo_t combos[PLAYER_COUNT];

// Adds the given amount of [bonus] points to [pid]'s combo, if the current
// amount of [hits] is enough to continue the combo. Returns the new total
// bonus value.
unsigned int pascal combo_add(
	unsigned char hits, pid_t pid, unsigned int bonus
);

void combo_update_and_render(void);

/// Hit combo slots
/// ---------------

// Number of simultaneous, separate hit combos tracked per player. *Not*
// related to the number of explosions on screen; rather, each explosion is
// assigned one of these slots when it spawns. All consecutive explosions
// spawned from that one will then add to the combo in that slot, which is
// what builds up the actual hit combo.
#define HITCOMBO_RING_SIZE 16

extern unsigned char hitcombo_ring_p[PLAYER_COUNT];
extern unsigned char hitcombo_ring[PLAYER_COUNT][HITCOMBO_RING_SIZE];

// Tries to update [pid]'s combo with the current hit combo value in the given
// [slot], adding the given amount of bonus points. Returns the new total
// bonus value.
unsigned int pascal hitcombo_commit(
	pid_t pid, unsigned char slot, unsigned int bonus_to_add
);
/// ----------------

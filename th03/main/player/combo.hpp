/// Displayed combo/bonus values
/// ----------------------------

#include "th03/common.h"

struct combo_t {
	unsigned char time;
	uint8_t hits_highest; // from the single highest-hitting active chain
	uint16_t bonus_total; // among all chains with ≥2 hits
};

#define COMBO_FRAMES 80
#define COMBO_HIT_RESET_FRAMES 32
#define COMBO_HIT_CAP 99
#define COMBO_BONUS_CAP 65535

// The first player to reach this amount of combo points will fire or reverse a
// Boss Attack as soon as the other blocking conditions are no longer met.
// (Also known as the Spell Point Requirement among the Western gameplay
// community.)
extern uint16_t combo_points_for_boss_attack;

extern combo_t combos[PLAYER_COUNT];

// Updates [pid]'s combo with the given amount of [bonus] points coming from an
// explosion chain with the given number of [hits]. Returns the new total bonus
// value.
uint16_t pascal combo_add_raw(uint8_t hits, pid_t pid, uint16_t bonus);

// ZUN bloat: Should be merged into combos_add(), since it's always called
// immediately afterward.
void pascal near fire_point_based_boss_attack_or_panic(
	uint16_t points, pid_t pid
);

void combos_update_and_render(void);

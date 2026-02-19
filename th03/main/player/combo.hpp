/// Displayed combo/bonus values
/// ----------------------------

#include "th03/common.h"

struct combo_t {
	unsigned char time;
	unsigned char hits;
	unsigned int bonus;
};

#define COMBO_FRAMES 80
#define COMBO_HIT_RESET_FRAMES 32
// Combos aren't started if less than this number of targets were hit at once
#define COMBO_HIT_MIN 2
#define COMBO_HIT_CAP 99
#define COMBO_BONUS_CAP 65535

extern combo_t combos[PLAYER_COUNT];

// Updates [pid]'s combo with the given amount of [bonus] points coming from an
// explosion chain with the given number of [hits]. Returns the new total bonus
// value.
uint16_t pascal combo_add_raw(uint8_t hits, pid_t pid, uint16_t bonus);

void combos_update_and_render(void);

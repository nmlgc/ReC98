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
	unsigned char hits, unsigned char pid, unsigned int bonus
);

void combo_update_and_render(void);

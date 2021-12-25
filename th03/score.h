#include "th02/score.h"

typedef struct {
	// Not including the amount of continues used.
	unsigned char digits[SCORE_DIGITS];
} score_lebcd_t;

extern score_lebcd_t score_lebcd[PLAYER_COUNT];

// Adds the given amount of [score] points to the given player's [score_lebcd].
void pascal score_add(uint16_t score, bool pid);

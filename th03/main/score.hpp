#include "th03/score.hpp"

extern score_lebcd_t score_lebcd[PLAYER_COUNT];

// Adds the given amount of [score] points to the given player's [score_lebcd].
void pascal score_add(uint16_t score, bool pid);

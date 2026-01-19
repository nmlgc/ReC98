#include "th03/score.hpp"

// Stops giving out extends at every 10 million points once [extends_gained]
// has reached this value.
static const uint8_t EXTENDS_MAX = 2;

// ZUN bloat: Setting [extends_gained] to this value once it reaches
// [EXTENDS_MAX] is not only a rather confusing way of preventing scores >
// (10,000,000 × [EXTENDS_MAX]) from awarding extends, but the entire reason
// why the fireballs_hittest() landmine can cause the infamous extend glitch
// regardless of [round_speed] once P1's score has reached 20 million.
static const uint8_t EXTENDS_DISABLE = 255;

extern score_lebcd_t score_lebcd[PLAYER_COUNT];

// Compared against the current P1 score on every frame. Can be set to 0 to
// cheat additional extends once P1 has reached the necessary score.
extern uint8_t extends_gained;

// Adds the given amount of [score] points to the given player's [score_lebcd].
void pascal score_add(uint16_t score, bool pid);

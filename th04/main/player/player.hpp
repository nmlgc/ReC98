#include "th02/main/player/player.hpp"

extern PlayfieldMotion player_pos;

void near player_pos_update_and_clamp(void);

// Shots
// -----

static const uint8_t POWER_MAX = 128;

#define SHOT_W 16
#define SHOT_H 16
// -----

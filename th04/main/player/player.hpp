#include "th02/main/player/player.h"

#define PLAYER_OPTION_W 16
#define PLAYER_OPTION_H 16
#define PLAYER_OPTION_DISTANCE ((PLAYER_W / 2) + (PLAYER_OPTION_W / 2))

extern PlayfieldMotion player_pos;

void near player_pos_update_and_clamp(void);

// Shots
// -----
#define SHOT_W 16
#define SHOT_H 16
// -----

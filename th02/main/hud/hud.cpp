#include "platform.h"
#include "th02/main/player/player.hpp"

static const uint8_t SHOT_LEVEL_INTERVAL_BITS = 2;

extern uint8_t POWER_TO_SHOT_LEVEL[POWER_MAX >> SHOT_LEVEL_INTERVAL_BITS];

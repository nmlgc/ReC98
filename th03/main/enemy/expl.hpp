#include "platform.h"
#include "th03/main/enemy/fireball.hpp"

enum explosion_hittest_mode_t {
	EHM_ENEMY = 0,
	EHM_PELLET = 1,
	EHM_FIREBALL = 2,
	EHM_FIREBALL_BLUE = (EHM_FIREBALL + FV_BLUE),
	EHM_FIREBALL_RED = (EHM_FIREBALL + FV_RED),

	_explosion_hittest_mode_t_FORCE_UINT8 = 0xFF
};

extern explosion_hittest_mode_t explosion_hittest_mode;

uint8_t explosions_hittest(void);

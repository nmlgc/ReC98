#include "platform.h"
#include "th03/main/enemy/fireball.hpp"

enum explosion_hittest_against_t {
	EHA_ENEMY = 0,
	EHA_PELLET = 1,
	EHA_FIREBALL = 2,
	EHA_FIREBALL_BLUE = (EHA_FIREBALL + FV_BLUE),
	EHA_FIREBALL_RED = (EHA_FIREBALL + FV_RED),

	_explosion_hittest_against_t_FORCE_UINT8 = 0xFF
};

// explosions_hittest() processes collision of *all* explosions that originated
// from both enemies and fireballs against the [hitbox] that represents a
// single one of this type of entity.
extern explosion_hittest_against_t explosion_hittest_against;

uint8_t explosions_hittest(void);

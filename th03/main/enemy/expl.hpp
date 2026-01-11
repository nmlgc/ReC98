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

// Stores whether the last return value of explosions_hittest() was nonzero.
extern bool explosion_collision_in_last_hittest;

// If [explosion_collision_in_last_hittest] is true, this holds the chain slot
// ID of the last explosion that collided with the hitbox tested by the last
// call to explosions_hittest().
// ZUN bloat: Could have been merged with that flag.
extern uint8_t explosion_collision_chain_slot;

// Processes collisions of all explosions against the hitbox specified in
// [hitbox.pid], [hitbox.origin.topleft], [hitbox.right], and [hitbox.bottom].
// Returns the number of explosions the hitbox collides with, and updates
// [explosion_collision_in_last_hittest] accordingly.
// ZUN bloat: This is called twice, and both call sites construct the hitbox
// in the same function. Parameters would be cleaner.
uint8_t explosions_hittest(void);

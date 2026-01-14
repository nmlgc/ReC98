// Enemy/fireball/explosion structure
// ----------------------------------
// Enemies and fireballs share the same overall structure layout, but are
// stored in different parts of the [efes] array and updated and rendered
// independently. They are only linked through [efe_p], whose pointed-to type
// differs depending on the context. Explosions are rendered and updated
// separately by enemies and fireballs, but share a collision detection
// function that only uses the common fields of the `efe_t` structure.

#ifndef TH03_MAIN_ENEMY_EFE_HPP
#define TH03_MAIN_ENEMY_EFE_HPP

#include "th03/main/playfld.hpp"
#include <stddef.h>

// Flags
// -----

typedef uint8_t efe_flag_t;

static const efe_flag_t EFF_FREE = 0;

// Every explosion starts out in this state.
static const efe_flag_t EFF_EXPLOSION_IGNORING_ENEMIES = 9;

// Every hit dealt to an enemy is added on top of this flag. (This is why these
// constants can't be an `enum`.)
static const efe_flag_t EFF_EXPLOSION_HITTING_ENEMIES = 10;

// Every usage of the explosion flags relies on this assertion.
inline void eff_explosion_flags_verify(void) {
	static_assert(
		EFF_EXPLOSION_HITTING_ENEMIES > EFF_EXPLOSION_IGNORING_ENEMIES
	);
}
// -----

struct efe_t {
	efe_flag_t flag;
	uint8_t frame; // Resets on hits and when turning into an explosion.
	PlayfieldPoint center;
	uint8_t explosion_max_enemy_hits_half;
	int8_t val1;
	pid_t pid;

	// Relates to the size of the explosion hitbox.
	pixel_length_8_t size_pixels;

	int8_t val2[18];
	uint8_t chain_slot;
	int8_t val3[5];
	int8_t padding[14]; // ZUN bloat
};

template <class T> inline void efe_subclass_verify(T *n) {
	efe_t *efe_n = reinterpret_cast<efe_t *>(n);
	static_assert(sizeof(T) == sizeof(efe_t));
	static_assert(offsetof(T, flag) == offsetof(efe_t, flag));
	static_assert(offsetof(T, frame) == offsetof(efe_t, frame));
	static_assert(offsetof(T, center) == offsetof(efe_t, center));
	static_assert(
		offsetof(T, explosion_max_enemy_hits_half) ==
		offsetof(efe_t, explosion_max_enemy_hits_half)
	);
	static_assert(offsetof(T, pid) == offsetof(efe_t, pid));
	static_assert(offsetof(T, size_pixels) == offsetof(efe_t, size_pixels));
	static_assert(offsetof(T, chain_slot) == offsetof(efe_t, chain_slot));
	static_assert(sizeof(n->flag) == sizeof(efe_n->flag));
	static_assert(sizeof(n->frame) == sizeof(efe_n->frame));
	static_assert(sizeof(n->center) == sizeof(efe_n->center));
	static_assert(
		sizeof(n->explosion_max_enemy_hits_half) ==
		sizeof(efe_n->explosion_max_enemy_hits_half)
	);
	static_assert(sizeof(n->pid) == sizeof(efe_n->pid));
	static_assert(sizeof(n->size_pixels) == sizeof(efe_n->size_pixels));
	static_assert(sizeof(n->chain_slot) == sizeof(efe_n->chain_slot));
}

static const int EFE_COUNT = 64;

extern efe_t efes[EFE_COUNT];

struct enemy_t;
struct fireball_t;

// Currently iterated enemy, explosion, or fireball. Using a `union` to allow
// potential undefined behavior checks in case the code accesses an inactive
// type, with tools that support it.
// ZUN bloat: Should be replaced with local variables and function parameters.
extern union {
	efe_t near *efe;
	enemy_t near *enemy;
	fireball_t near *fireball;
} efe_p;

#endif /* TH03_MAIN_ENEMY_EFE_HPP */

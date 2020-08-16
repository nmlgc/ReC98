#include "th04/main/boss/boss.hpp"

// Callbacks
extern nearfunc_t_near boss_custombullets_render;

extern unsigned int boss_sprite_left;
extern unsigned int boss_sprite_right;
extern unsigned int boss_sprite_stay;

extern boss_stuff_t boss2;

/// Movement
/// --------
/// Call these on subsequent frames for a smooth flying movement.

// Steps the [boss] from its current position towards the target point, moving
// it by a hardcoded fraction of the distance. Returns true once the [boss]
// has reached the target point.
bool pascal near boss_flystep_towards(subpixel_t target_x, subpixel_t target_y);
/// --------

/// Explosions
/// ----------
// No longer using a type parameter in TH05.
void pascal near boss_explode_big(void);

void pascal near boss2_explode_small(unsigned int type);
void pascal near boss2_explode_big(void);
/// ----------

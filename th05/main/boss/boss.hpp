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

typedef enum {
	Y_ANY,
	Y_UP,
	Y_DOWN,
} y_direction_t;

extern area_t<Subpixel, Subpixel> boss_flystep_random_clamp;
static const subpixel_t BOSS_FLYSTEP_RANDOM_FIELD_LEFT = TO_SP(
	(PLAYFIELD_W / 2) - (PLAYFIELD_W / 8)
);
static const subpixel_t BOSS_FLYSTEP_RANDOM_FIELD_RIGHT = TO_SP(
	(PLAYFIELD_W / 2) + (PLAYFIELD_W / 8)
);

static const int BOSS_FLYSTEP_RANDOM_FRAMES = 28;

// Decides a random [boss.angle] on [frame] 0, based on the current position
// within the playfield and clamping areas declared above. Then, steps the
// [boss] into this direction with a hardcoded, [frame]-dependent speed for
// all [frame]s between 0 and [BOSS_FLYSTEP_RANDOM_FRAMES], after which the
// function returns true.
// Does nothing for [frame]s < 0 (and the game relies on that).
bool pascal near boss_flystep_random(int frame);

// Steps the [boss] from its current position towards the target point, moving
// it by a hardcoded fraction of the distance. Returns true once the [boss]
// has reached the target point.
bool pascal near boss_flystep_towards(subpixel_t target_x, subpixel_t target_y);
/// --------

/// Explosions
/// ----------

void pascal near boss2_explode_small(unsigned int type);
void near boss2_explode_big_circle(void);
/// ----------

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

extern area_t<Subpixel> boss_flystep_random_clamp;
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
bool pascal near boss_flystep_random(int frame);

#define flystep_random_for( \
	boss, \
	next_y_direction, \
	speed, \
	frames, \
	clamp_left, \
	clamp_right, \
	clamp_top, \
	clamp_bottom, \
	sprite_left, \
	sprite_right, \
	sprite_still, \
	frame \
) \
	if(frame == 0) { \
		if(boss.pos.cur.x.v < BOSS_FLYSTEP_RANDOM_FIELD_LEFT) { \
			boss.angle = (randring2_next16_mod(0x60) - 0x30); \
		} else if(boss.pos.cur.x.v > BOSS_FLYSTEP_RANDOM_FIELD_RIGHT) { \
			boss.angle = (randring2_next16_and(0x60) + 0x30); \
		} else { \
			boss.angle = randring2_next16(); \
		} \
		if( \
			(next_y_direction == Y_UP  ) && (boss.angle <  0x80) || \
			(next_y_direction == Y_DOWN) && (boss.angle >= 0x80) \
		) { \
			boss.angle = -boss.angle; \
		} \
		next_y_direction = Y_ANY; \
	} \
	if(frame >= 0) { \
		vector2_near( \
			boss.pos.velocity, boss.angle, (to_sp(speed) - (frame * 2)) \
		); \
		boss.pos.cur.x.v += boss.pos.velocity.x.v; \
		boss.pos.cur.y.v += boss.pos.velocity.y.v; \
		if(boss.pos.velocity.x.v < 0) { \
			boss.sprite = sprite_left; \
		} else { \
			boss.sprite = sprite_right; \
		} \
		if(boss.pos.cur.y.v < clamp_top) { \
			boss.pos.cur.y.v = clamp_top; \
			next_y_direction = Y_DOWN; \
		} else if(boss.pos.cur.y.v > clamp_bottom) { \
			boss.pos.cur.y.v = clamp_bottom; \
			next_y_direction = Y_UP; \
		} \
		if(boss.pos.cur.x.v < clamp_left) { \
			boss.pos.cur.x.v = clamp_left; \
		} else if(boss.pos.cur.x.v > clamp_right) { \
			boss.pos.cur.x.v = clamp_right; \
		} \
		if(frame >= frames) { \
			boss.sprite = sprite_still; \
			return true; \
		} \
	} \
	return false;

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

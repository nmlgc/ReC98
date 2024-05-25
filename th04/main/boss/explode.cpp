#include "platform.h"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/hardware/grcg.hpp"
#include "th02/main/hud/hud.hpp"
#include "th03/math/polar.hpp"
#include "th03/hardware/palette.hpp"
#include "th04/hardware/grcg.hpp"
#include "th04/formats/super.h"
#include "th04/main/boss/boss.hpp"
#if (GAME == 5)
	#include "th05/sprites/main_pat.h"
#else
	#include "th04/sprites/main_pat.h"
#endif

// Structures
// ----------

#define EXPLOSION_SMALL_COUNT 2

struct Explosion {
	bool alive;
	unsigned char age;
	SPPoint center;
	SPPoint radius_cur;
	SPPoint radius_delta;
	int8_t unused; // ZUN bloat

	// Offset to add to the angle for the Y coordinate, turning the circle
	// into a slanted ellipse. See https://www.desmos.com/calculator/faeefi6w1u
	// for a plot of the effect.
	unsigned char angle_offset;

	// A method is the most idiomatic way for this to compile into ZUN's
	// original three instructions, believe it or not.
	unsigned char angle_y(const unsigned char& angle_base) {
		return (angle_offset + angle_base);
	}
};

#define explosion_update(p) { \
	(p).radius_cur.x.v += (p).radius_delta.x.v; \
	(p).radius_cur.y.v += (p).radius_delta.y.v; \
	(p).age++; \
	if((p).age >= 32) { \
		(p).alive = false; \
	} \
}

extern Explosion explosions_small[EXPLOSION_SMALL_COUNT];
extern Explosion explosions_big;
// ----------

void near explosions_small_update_and_render(void)
{
	enum {
		SPRITE_W = 16,
		SPRITE_H = 16,
		SPRITES = 64,
	};

	_ES = SEG_PLANE_B;
	grcg_setmode_rmw();

	Explosion near* p;
	int sprite;
	Subpixel center_x;
	Subpixel center_y;
	int i;

	for((p = explosions_small, i = 0); i < EXPLOSION_SMALL_COUNT; (i++, p++)) {
		if(!p->alive) {
			continue;
		}
		sprite = 0;
		unsigned char angle = 0x00;
		while(sprite < SPRITES) {
			#define left	_AX
			#define top 	_DX

			center_x.v = polar_x(p->center.x, p->radius_cur.x, angle);
			center_y.v = polar_y(
				p->center.y, p->radius_cur.y, p->angle_y(angle)
			);
			top = playfield_to_screen_top(center_y, SPRITE_H);
			left = playfield_to_screen_left(center_x, SPRITE_W);
			if(!playfield_clip_topleft_small(left, top, SPRITE_W, SPRITE_H)) {
				z_super_roll_put_tiny_16x16(left, top, PAT_EXPLOSION_SMALL);
			}

			sprite++;
			angle += (0x100 / SPRITES);

			#undef top
			#undef left
		}
		explosion_update(*p);
	}

	grcg_off();
}

void near explosions_big_update_and_render(void)
{
	enum {
		// ZUN bug: The sprite from MIKOD.BFT is actually 48×48 pixels large;
		// assuming 64×64 will misalign the transformation to screen space and
		// the clipping condition.
		SPRITE_W = 64,
		SPRITE_H = 64,

		SPRITES = 16,
	};

	#define frame explosion_big_frame

	extern int frame;

	Explosion near& p = explosions_big;
	int sprite;

	// ZUN bloat: Should be a separate PlayfieldPoint and screen_point_t.
	subpixel_t x;
	#define x_center	x
	#define x_left  	static_cast<screen_x_t>(x)
	union { Subpixel center; screen_y_t top; } y;

	if(p.alive) {
		sprite = 0;
		unsigned char angle = 0x00;
		while(sprite < SPRITES) {
			x_center = polar_x(p.center.x, p.radius_cur.x, angle);
			x_left = playfield_to_screen_left(x_center, SPRITE_W);
			y.center.v = polar_y(p.center.y, p.radius_cur.y, p.angle_y(angle));
			y.top = playfield_to_screen_top(y.center, SPRITE_H);
			if(!playfield_clip_topleft_large(
				x_left, y.top, SPRITE_W, SPRITE_H
			)) {
				super_put(x_left, y.top, PAT_EXPLOSION_BIG);
			}

			sprite++;
			angle += (0x100 / SPRITES);
		}
		explosion_update(p);

		frame++;
		if((frame < 8) && (frame & 1)) {
			palette_settone_deferred(150);
		} else if((frame >= 8) && (frame < 16)) {
			palette_settone_deferred(100 + (16 * 6) - (frame * 6));
		} else {
			palette_settone_deferred(100);
		}
	} else {
		frame = 0;
	}

	#undef frame
}

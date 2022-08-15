#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/math/vector.hpp"
#include "th04/math/randring.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/frames.h"
#include "th04/main/circle.hpp"
#include "th05/sprites/main_pat.h"
#include "th05/main/player/bomb.hpp"

// Structures
// ----------
static const int REIMU_STAR_TRAILS = 6;
static const int REIMU_STAR_NODE_COUNT = 8;
static const int MARISA_LASER_COUNT = 8;
static const int MIMA_CIRCLE_COUNT = 8;

static const pixel_t REIMU_STAR_W = 64;
static const pixel_t REIMU_STAR_H = 64;

// Generic type
struct bomb_anim_t {
	point_t pos;
	int16_t val1;
	int16_t val2;
	unsigned char angle;
	int8_t padding;
};

struct reimu_star_t {
	struct {
		Subpixel screen_x;
		Subpixel screen_y;
	} topleft;
	SPPoint velocity;
	unsigned char angle;
	int8_t padding;
};

struct marisa_laser_t {
	SPPoint center;
	int16_t unused;
	pixel_t radius;
	int16_t padding;
};

struct mima_circle_t {
	screen_point_t center;
	int16_t unused;
	pixel_t distance;
	unsigned char angle;
	int8_t padding;
};

struct yuuka_heart_t {
	screen_point_t topleft;
	int16_t unused;
	pixel_t distance;
	unsigned char angle;
	int8_t padding;
};

extern union {
	reimu_star_t reimu[REIMU_STAR_TRAILS][REIMU_STAR_NODE_COUNT];
	marisa_laser_t marisa[MARISA_LASER_COUNT];
	mima_circle_t mima[MIMA_CIRCLE_COUNT];
	yuuka_heart_t yuuka;
} bomb_anim;
// ----------

#define reimu_star_put(star, col) \
	super_roll_put_1plane( \
		star->topleft.screen_x.to_pixel_slow(), \
		star->topleft.screen_y.to_pixel_slow(), \
		PAT_PLAYCHAR_BOMB, \
		0, \
		(PLANE_ERASE | ((COLOR_COUNT - 1) - col)) \
	);

void pascal near reimu_stars_update_and_render(void)
{
	reimu_star_t near *head;
	reimu_star_t near *trail;
	Subpixel speed;
	int i;
	unsigned char angle;

	if(bomb_frame == BOMB_CIRCLE_FRAMES) {
		head = &bomb_anim.reimu[0][0];
		trail = &bomb_anim.reimu[0][REIMU_STAR_NODE_COUNT - 1];
		i = 0;
		while(i < REIMU_STAR_TRAILS) {
			//  head == [0 |  8 | 16 | 24 | 30 | 36]
			// trail == [7 | 11 | 15 | 19 | 23 | 27]
			head->topleft.screen_x.v = randring1_next16_mod_ge_lt_sp(
				PLAYFIELD_LEFT, (PLAYFIELD_LEFT + 320.0f)
			);
			head->topleft.screen_y.v = randring1_next16_mod_ge_lt_sp(
				0.0f, (RES_Y - (REIMU_STAR_H / 2))
			);

			// MODDERS: REIMU_STAR_NODE_COUNT times
			/*    */	trail->topleft = head->topleft;
			trail--;	trail->topleft = head->topleft;
			trail--;	trail->topleft = head->topleft;
			trail--;	trail->topleft = head->topleft;
			trail--;	trail->topleft = head->topleft;
			trail--;	trail->topleft = head->topleft;
			trail--;	trail->topleft = head->topleft;
			trail += 10; // ZUN quirk

			speed.v = randring1_next16_and_ge_lt_sp(10.0f, 18.0f);
			angle = (0x40 + randring1_next8_mod_ge_lt(-0x18, +0x18));

			vector2(head->velocity.x.v, head->velocity.y.v, angle, speed);

			i++;
			head += REIMU_STAR_NODE_COUNT;
		}
	}
	head = &bomb_anim.reimu[0][REIMU_STAR_NODE_COUNT - 2];
	trail = &bomb_anim.reimu[0][REIMU_STAR_NODE_COUNT - 1];
	for(i = 0; i < REIMU_STAR_TRAILS; i++) {
		//  head == [6 | 14 | 22 | 30 | 38 | 46]
		// trail == [7 | 15 | 23 | 31 | 39 | 47]

		// MODDERS: (REIMU_STAR_NODE_COUNT - 1) times
		/*            */	trail->topleft = head->topleft;
		head--; trail--;	trail->topleft = head->topleft;
		head--; trail--;	trail->topleft = head->topleft;
		head--; trail--;	trail->topleft = head->topleft;
		head--; trail--;	trail->topleft = head->topleft;
		head--; trail--;	trail->topleft = head->topleft;
		head--; trail--;	trail->topleft = head->topleft;
		//  head == [0 |  8 | 16 | 24 | 32 | 40]
		// trail == [1 |  9 | 17 | 25 | 33 | 41]

		head->topleft.screen_x.v += head->velocity.x.v;
		head->topleft.screen_y.v += head->velocity.y.v;

		if(
			head->topleft.screen_x.v <= to_sp(PLAYFIELD_LEFT) ||
			head->topleft.screen_x.v >= to_sp(PLAYFIELD_RIGHT - REIMU_STAR_W)
		) {
			head->velocity.x.v = -head->velocity.x.v;
		}
		if(head->topleft.screen_y.v >= to_sp(RES_Y)) {
			head->topleft.screen_y.v -= to_sp(RES_Y);
		}

		trail += ((REIMU_STAR_NODE_COUNT - 1) - 2);
		// trail == [6 | 14 | 22 | 30 | 38 | 46]

		/*       */	reimu_star_put(trail, 6);
		trail -= 2;	reimu_star_put(trail, 6);
		trail -= 2;	reimu_star_put(trail, 6);
		/*       */	reimu_star_put(head, 7);

		// trail == [2 | 10 | 18 | 26 | 34 | 42]

		// ZUN bug: Should perhaps be done after the conditional branch below,
		// to avoid the out-of-bounds memory access on the last iteration of
		// this loop...
		trail += (((REIMU_STAR_NODE_COUNT * 2) - 2) - 1);
		head += ((REIMU_STAR_NODE_COUNT * 2) - 2);

		if((bomb_frame <= 112) && (stage_frame_mod8 == i)) {
			/* TODO: Replace with the decompiled call
			 * 	circles_add_growing(
			 * 		head->topleft.screen_x,
			 * 		(head->topleft.screen_y + PLAYFIELD_TOP)
			 * 	);
			 * once that function is part of this translation unit */
			_asm {
				db	0xFF, 0x34;
				db	0x8B, 0x44, 0x02;
				add 	ax, (PLAYFIELD_TOP * 16);
				push	ax;
				nop;
				push	cs;
				call	near ptr circles_add_growing;
			}
		}
	}
}

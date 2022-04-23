/// Stage 1 midboss
/// ---------------

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/math/randring.hpp"
#include "th04/math/vector.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/bullet/bullet.hpp"
}
#include "th04/main/midboss/midboss.hpp"
#include "th04/main/boss/boss.hpp"
#include "th05/sprites/main_pat.h"

// Constants
// ---------

static const subpixel_t MIDBOSS1_W = TO_SP(32);
static const subpixel_t MIDBOSS1_H = TO_SP(32);
// ---------

// State
// -----

// Using a boss_statebyte would have been nicer than repurposing *that*...
#define bullet_angle boss.angle

#define distance_from_center midboss.pos.velocity.x
// -----

void near midboss1_move(void)
{
	midboss.pos.prev.x = midboss.pos.cur.x;
	midboss.pos.prev.y = midboss.pos.cur.y;

	midboss.pos.cur.x.v = vector1_at(
		to_sp(playfield_fraction_x(1 / 2.0f)),
		distance_from_center,
		CosTable8[midboss.angle]
	);
	midboss.pos.cur.y.v = vector1_at(
		to_sp(playfield_fraction_y(6 / 23.0f)),
		distance_from_center,
		SinTable8[midboss.angle]
	);
	midboss.angle -= 0x02;
}

void near midboss1_pattern(void)
{
	int interval = 16;
	if(midboss.hp <= 200) {
		interval = 12;
	}

	if((midboss.phase_frame % interval) == 0) {
		bullet_template.spawn_type = BST_NORMAL;
		bullet_template.patnum = 0;
		bullet_template.speed.set(2.0f);
		bullet_template.group = BG_SPREAD;
		bullet_template.special_motion = BSM_EXACT_LINEAR;
		bullet_template.set_spread(4, 0x02);
		bullet_template.angle = bullet_angle;
		bullet_angle += 0x14;
		bullet_template_tune();
		bullets_add_special();

		bullet_template.group = BG_SINGLE;
		bullet_template.spawn_type = BST_CLOUD_FORWARDS;
		bullet_template.speed.set(1.5f);
		bullet_template.patnum = PAT_BULLET16_N_BLUE;
		bullet_template_tune();
		bullet_template.angle = randring2_next16();
		bullet_template.origin.x.v = vector1_at(
			midboss.pos.cur.x, MIDBOSS1_W, CosTable8[bullet_template.angle]
		);
		bullet_template.origin.y.v = vector1_at(
			midboss.pos.cur.y, MIDBOSS1_H, SinTable8[bullet_template.angle]
		);
		bullets_add_regular();
	}
}

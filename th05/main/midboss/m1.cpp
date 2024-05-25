/// Stage 1 midboss
/// ---------------

#pragma option -zPmain_03

#include "platform.h"
#include "pc98.h"
#include "libs/master.lib/master.hpp"
#include "th03/math/polar.hpp"
#include "th04/math/randring.hpp"
#include "th04/snd/snd.h"
#include "th04/main/homing.hpp"
#include "th04/main/bullet/bullet.hpp"
#include "th04/main/spark.hpp"
#include "th04/main/bullet/clearzap.hpp"
#include "th04/main/item/item.hpp"
#include "th04/main/midboss/midboss.hpp"
#include "th04/main/boss/boss.hpp"
#include "th04/main/hud/hud.hpp"
#include "th05/sprites/main_pat.h"

// Constants
// ---------

static const subpixel_t MIDBOSS1_W = TO_SP(32);
static const subpixel_t MIDBOSS1_H = TO_SP(32);
static const int HP_TOTAL = 1000;
// ---------

// State
// -----

// Using a boss_statebyte would have been nicer than repurposing *that*...
#define bullet_angle boss.angle

// MODDERS: Turn into a parameter of midboss1_move().
#define distance_from_center midboss.pos.velocity.x
// -----

void near midboss1_move(void)
{
	midboss.pos.prev.x = midboss.pos.cur.x;
	midboss.pos.prev.y = midboss.pos.cur.y;

	midboss.pos.cur.x.v = polar_x(
		to_sp(playfield_fraction_x(1 / 2.0f)),
		distance_from_center.v,
		midboss.angle
	);
	midboss.pos.cur.y.v = polar_y(
		to_sp(playfield_fraction_y(6 / 23.0f)),
		distance_from_center.v,
		midboss.angle
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
		bullet_template.patnum = PAT_BULLET16_N_BALL_BLUE;
		bullet_template_tune();
		bullet_template.angle = randring2_next16();
		bullet_template.origin.x.v = polar_x(
			midboss.pos.cur.x, MIDBOSS1_W, bullet_template.angle
		);
		bullet_template.origin.y.v = polar_y(
			midboss.pos.cur.y, MIDBOSS1_H, bullet_template.angle
		);
		bullets_add_regular();
	}
}

#pragma option -a2

void pascal midboss1_update(void)
{
	bullet_template.origin = midboss.pos.cur;

	midboss.phase_frame++;

	switch(midboss.phase) {
	case 0:
		// Timeout condition
		if(midboss.phase_frame >= (HUD_HP_FILL_FRAMES + 128)) {
			midboss.phase++;
			midboss.phase_frame = 0;
			midboss.sprite = PAT_MIDBOSS1;
		}
		break;

	case 1:
	case 2:
		midboss_hittest_shots_invincible(
			((MIDBOSS1_W / 2) - (MIDBOSS1_W / 8)),
			((MIDBOSS1_H / 2) - (MIDBOSS1_H / 8))
		);
		// Timeout condition
		if(midboss.phase_frame >= 64) {
			midboss.phase++;
			midboss.phase_frame = 0;
			distance_from_center.set(0.0f);
			bullet_angle = -0x20;
		}
		break;

	case 3:
		midboss1_pattern();
		midboss_hittest_shots(
			(MIDBOSS1_W - (MIDBOSS1_W / 4)), (MIDBOSS1_H - (MIDBOSS1_H / 4))
		);

		// Or, alternatively, (((HP_TOTAL - midboss.hp) / HP_TOTAL) * 64.0f).
		distance_from_center.v = (
			((HP_TOTAL - midboss.hp) * 64lu * SUBPIXEL_FACTOR) / HP_TOTAL
		);
		midboss1_move();

		// Timeout condition
		if(midboss.phase_frame < 1500) {
			if(midboss.hp > 0) {
				break;
			}
			bullet_zap.active = true;
			midboss_score_bonus(5);
			items_add(midboss.pos.cur.x, midboss.pos.cur.y, IT_BIGPOWER);
		}
		midboss.phase = PHASE_EXPLODE_BIG;
		midboss.sprite = PAT_ENEMY_KILL;
		midboss.phase_frame = 0;
		sparks_add_circle(
			midboss.pos.cur.x, midboss.pos.cur.y, (MIDBOSS1_W / 4), 48
		);
		snd_se_play(12);
		break;

	default:
		midboss_defeat_update();
		hud_hp_update_and_render(midboss.hp, HP_TOTAL);
		return;
	}

	hud_hp_update_and_render(midboss.hp, HP_TOTAL);
	homing_target.x = midboss.pos.cur.x;
	homing_target.y = midboss.pos.cur.y;
}

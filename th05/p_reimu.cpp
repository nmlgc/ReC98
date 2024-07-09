/* ReC98
 * -----
 * Reimu's shot control functions
 */

#pragma option -zCmain_01_TEXT -zPmain_01

#include "th05/main/player/shot.hpp"
#define cycle _AL

extern "C" {

#define reimu_forward(shot, sai, dmg, i_left, angle_left, angle_add) \
	if(sai.i == i_left) { \
		sai.angle = angle_left; \
	} \
	shot->damage = dmg; \
	sai.angle += angle_add;

#define reimu_sub_spread_constant(shot, sai, i_left) \
	if(sai.i == i_left)  { shot->from_option_l(); sai.angle = -0x48; } \
	else/*i == i_right*/ { shot->from_option_r(); sai.angle = -0x38; }

#define reimu_sub_spread_random(shot, sai, i_left) \
	if(sai.i == i_left) { \
		shot->from_option_l(); \
		sai.set_random_angle(-0x4A, -0x46); \
	} else /* i == i_right */ { \
		shot->from_option_r(); \
		sai.set_random_angle(-0x3A, -0x36); \
		if(option_only == 0) { \
			sai.i = 1; \
		} \
	}

#define set_homing(shot, dmg) \
	shot->set_option_sprite_and_damage(dmg); \
	shot->type = ST_HOMING;

void pascal near shot_reimu_l2(void)
{
	shot_func_init(shot, sai, cycle, 1, SC_3X, SC_1X, i += 2);

	while(( shot = shots_add() ) != nullptr) {
		if(sai.i == 1) {
			shot->set_random_angle_forwards();
			shot->damage = 10;
		} else {
			reimu_sub_spread_constant(shot, sai, 3);
			shot_velocity_set(&shot->pos.velocity, sai.angle);
			set_homing(shot, 4);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_reimu_l3(void)
{
	shot_func_init(shot, sai, cycle, 2, SC_3X, SC_1X, i += 2);

	while(( shot = shots_add() ) != nullptr) {
		if(sai.i <= 2) {
			if(sai.i == 2) { shot->pos.cur.x -= 8; }
			else/*i == 1*/ { shot->pos.cur.x += 8; }
			shot->damage = 9;
		} else {
			reimu_sub_spread_constant(shot, sai, 4);
			shot_velocity_set(&shot->pos.velocity, sai.angle);
			set_homing(shot, 4);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_reimu_l4(void)
{
	shot_func_init(shot, sai, cycle, 3, SC_3X, SC_1X, i += 2);

	while(( shot = shots_add() ) != nullptr) {
		if(sai.i <= 3) {
			reimu_forward(shot, sai, 9, 3, -0x4C, +0x06);
		} else {
			reimu_sub_spread_constant(shot, sai, 5);
			set_homing(shot, 3);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

#define REIMU_L5 \
	shot_func_init(shot, sai, cycle, 3, SC_3X, SC_2X, add_secondary(2)); \
	char option_only = cycle & SC_3X; \
	\
	while(( shot = shots_add() ) != nullptr) { \
		if(sai.i <= 3) { \
			shot->damage = 9; \
			if(sai.i == 3) { \
				sai.angle = -0x4E; \
			} \
			sai.angle += 0x07; \
		} else { \
			reimu_sub_spread_random(shot, sai, 5); \
			shot->set_option_sprite_and_damage(3); \
			shot->type = ST_HOMING; \
		} \
		shot_velocity_set(&shot->pos.velocity, sai.angle); \
		if(sai.next() <= 0) { \
			break; \
		} \
	} \

void pascal near shot_reimu_l5(void)
{
	REIMU_L5;
}

void pascal near shot_reimu_l6(void)
{
	REIMU_L5;
}

void pascal near shot_reimu_l7(void)
{
	shot_func_init(shot, sai, cycle, 5, SC_3X, SC_2X, add_secondary(2));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != nullptr) {
		if(sai.i <= 5) {
			reimu_forward(shot, sai, 9, 5, -0x4F, +0x05);
		} else {
			reimu_sub_spread_random(shot, sai, 7);
			set_homing(shot, 3);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_reimu_l8(void)
{
	Shot near *shot;
	ShotAddIterator sai(7);
	if( (shot_cycle_init() & SC_3X) == 0) {
		return;
	}
	while(( shot = shots_add() ) != nullptr) {
		if(sai.i <= 5) {
			reimu_forward(shot, sai, 9, 5, -0x4F, +0x05);
		} else {
			if(sai.i == 7) {
				shot->from_option_l(); sai.set_random_angle(-0x4A, -0x46);
			} else/*i == 6*/ {
				shot->from_option_r(); sai.set_random_angle(-0x3A, -0x36);
			}
			set_homing(shot, 3);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_reimu_l9(void)
{
	shot_func_init(shot, sai, cycle, 7, SC_3X, SC_2X, add_secondary(2));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != nullptr) {
		if(sai.i <= 5) {
			reimu_forward(shot, sai, 9, 5, -0x4F, +0x05);
		} else {
			if(sai.i <= 7) {
				reimu_sub_spread_constant(shot, sai, 7);
			} else {
				if(sai.i == 9) {
					shot->from_option_l();
					sai.angle = -0x56;
				} else /* i == 8 */ {
					shot->from_option_r();
					sai.angle = -0x2A;
					if(option_only == 0) {
						sai.i = 1;
					}
				}
			}
			set_homing(shot, 2);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

}

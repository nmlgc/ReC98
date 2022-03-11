/* ReC98
 * -----
 * Yuuka's shot control functions
 */

#pragma option -zCmain_01_TEXT -zPmain_01

extern "C" {
#include "th05/i_shot.hpp"
#define cycle _AL

#pragma option -a2

#define YUUKA_INNER_L4 \
	switch(sai.i - 1) { \
	case 0:	sai.angle = -0x46;	break; \
	case 1:	sai.angle = -0x40;	shot->pos.cur.x -= 8;	break; \
	case 2:	sai.angle = -0x40;	shot->pos.cur.x += 8;	break; \
	case 3:	sai.angle = -0x3A;	break; \
	} \
	shot->damage = 7;

#define YUUKA_INNER_L5 \
	switch(sai.i - 1) { \
	case 0:	sai.angle = -0x4C; break; \
	case 1:	sai.angle = -0x46; break; \
	case 2:	sai.angle = -0x40; break; \
	case 3:	sai.angle = -0x3A; break; \
	case 4:	sai.angle = -0x34; break; \
	} \
	shot->damage = 7;

void pascal near shot_yuuka_l2(void)
{
	shot_func_init(shot, sai, cycle, 1, SC_3X, SC_1X, i += 2);
	while(( shot = shots_add() ) != NULL) {
		if(sai.i == 1) {
			sai.set_random_angle(0x0F, -0x48);
			shot->damage = 9;
		} else {
			if(sai.i == 3) { shot->from_option_l(); sai.angle = -0x48; }
			else/*i == 2*/ { shot->from_option_r(); sai.angle = -0x38; }
			shot->set_option_sprite_and_damage(6);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_yuuka_l3(void)
{
	shot_func_init(shot, sai, cycle, 2, SC_3X, SC_2X, add_secondary(2));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 2) {
			if(sai.i == 2) { shot->pos.cur.x -= 8.0f; }
			else/*i == 1*/ { shot->pos.cur.x += 8.0f; }
			shot->damage = 8;
		} else {
			if(sai.i == 4) {
				shot->from_option_l();
				sai.angle = -0x48;
			} else {
				shot->from_option_r();
				sai.angle = -0x38;
				if(option_only == 0) {
					sai.i = 1;
				}
			}
			shot->set_option_sprite_and_damage(6);
			shot_velocity_set(&shot->pos.velocity, sai.angle);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_yuuka_l4(void)
{
	shot_func_init(shot, sai, cycle, 3, SC_3X, SC_2X, add_secondary(2));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 3) {
			if(sai.i == 3) {
				sai.angle = -0x4C;
			}
			shot->damage = 7;
			sai.angle += 0x06;
		} else {
			if(sai.i == 5) {
				shot->from_option_l();
				sai.set_random_angle(0x07, -0x4C);
			} else {
				shot->from_option_r();
				sai.set_random_angle(0x07, -0x3C);
				if(option_only == 0) {
					sai.i = 1;
				}
			}
			shot->pos.velocity.y.set(2.0f);
			shot->set_option_sprite_and_damage(6);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_yuuka_l5(void)
{
	shot_func_init(shot, sai, cycle, 3, SC_3X, SC_2X, add_secondary(4));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 3) {
			shot->damage = 7;
			if(sai.i == 3) {
				sai.angle = -0x4C;
			}
			sai.angle += 0x06;
		} else {
			switch(sai.i - 4u) {
			case 0:
				if(option_only == 0) {
					sai.i = 1;
				}
			/*  */	shot->from_option_l();	sai.angle = -0x4E;	break;
			case 1:	shot->from_option_r();	sai.angle = -0x32;	break;
			case 2:	shot->from_option_l();	sai.angle = -0x46;	break;
			case 3:	shot->from_option_r();	sai.angle = -0x3A;	break;
			}
			shot->set_option_sprite_and_damage(6);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_yuuka_l6(void)
{
	shot_func_init(shot, sai, cycle, 4, SC_3X, SC_2X, add_secondary(4));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 4) {
			YUUKA_INNER_L4;
		} else {
			switch(sai.i - 5u) {
			case 0:	shot->from_option_l();	sai.angle = -0x50;
				if(option_only == 0) {
					sai.i = 1;
				}
				break;
			case 1:	shot->from_option_r();	sai.angle = -0x30;	break;
			case 2:	shot->from_option_l();	sai.angle = -0x48;	break;
			case 3:	shot->from_option_r();	sai.angle = -0x38;	break;
			}
			shot->set_option_sprite_and_damage(6);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_yuuka_l7(void)
{
	shot_func_init(shot, sai, cycle, 4, SC_3X, SC_2X, add_secondary(6));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 4) {
			YUUKA_INNER_L4;
		} else {
			switch(sai.i - 5u) {
			case 0:	shot->from_option_l();	sai.angle = -0x50;
				if(option_only == 0) {
					sai.i = 1;
				}
				break;
			case 1:	shot->from_option_r();	sai.angle = -0x30;	break;
			case 2:	shot->from_option_l();	sai.angle = -0x49;	break;
			case 3:	shot->from_option_r();	sai.angle = -0x37;	break;
			case 4:	shot->from_option_l();	sai.angle = -0x42;	break;
			case 5:	shot->from_option_r();	sai.angle = -0x3E;	break;
			}
			shot->set_option_sprite_and_damage(6);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_yuuka_l8(void)
{
	shot_func_init(shot, sai, cycle, 5, SC_3X, SC_2X, add_secondary(6));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 5) {
			YUUKA_INNER_L5;
		} else {
			switch(sai.i - 6u) {
			case 0:	shot->from_option_l();	sai.angle = -0x50;
				if(option_only == 0) {
					sai.i = 1;
				}
				break;
			case 1:	shot->from_option_r();	sai.angle = -0x30;	break;
			case 2:	shot->from_option_l();	sai.angle = -0x49;	break;
			case 3:	shot->from_option_r();	sai.angle = -0x37;	break;
			case 4:	shot->from_option_l();	sai.angle = -0x42;	break;
			case 5:	shot->from_option_r();	sai.angle = -0x3E;	break;
			}
			shot->set_option_sprite_and_damage(6);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_yuuka_l9(void)
{
	shot_func_init(shot, sai, cycle, 5, SC_3X, SC_2X, add_secondary(8));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 5) {
			YUUKA_INNER_L5;
		} else {
			switch(sai.i - 6u) {
			case 0:	shot->from_option_l();	sai.angle = -0x58;
				if(option_only == 0) {
					sai.i = 1;
				}
				break;
			case 1:	shot->from_option_r();	sai.angle = -0x28;	break;
			case 2:	shot->from_option_l();	sai.angle = -0x50;	break;
			case 3:	shot->from_option_r();	sai.angle = -0x30;	break;
			case 4:	shot->from_option_l();	sai.angle = -0x48;	break;
			case 5:	shot->from_option_r();	sai.angle = -0x38;	break;
			case 6:	shot->from_option_l();	sai.angle = -0x3F;	break;
			case 7:	shot->from_option_r();	sai.angle = -0x41;	break;
			}
			shot->set_option_sprite_and_damage(6);
		}
		shot_velocity_set(&shot->pos.velocity, sai.angle);
		if(sai.next() <= 0) {
			break;
		}
	}
}

}

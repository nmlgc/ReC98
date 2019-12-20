/* ReC98
 * -----
 * Yuuka's shot control functions
 */

#pragma codeseg main_01_TEXT

extern "C" {
#include "th05/i_shot.hpp"
#define cycle _AL

#define YUUKA_INNER_L4 \
	switch(sai.i - 1) { \
	case 0:	sai.angle = 186;	break; \
	case 1:	sai.angle = 192;	shot->pos.cur.x -= 8;	break; \
	case 2:	sai.angle = 192;	shot->pos.cur.x += 8;	break; \
	case 3:	sai.angle = 198;	break; \
	} \
	shot->damage = 7;

#define YUUKA_INNER_L5 \
	switch(sai.i - 1) { \
	case 0:	sai.angle = 180; break; \
	case 1:	sai.angle = 186; break; \
	case 2:	sai.angle = 192; break; \
	case 3:	sai.angle = 198; break; \
	case 4:	sai.angle = 204; break; \
	} \
	shot->damage = 7;

void pascal near shot_yuuka_l2(void)
{
	SHOT_FUNC_INIT(1, SC_3X, SC_1X, i += 2);
	while(( shot = shots_add() ) != NULL) {
		if(sai.i == 1) {
			sai.angle = randring_angle(15, 184);
			shot->damage = 9;
		} else {
			if(sai.i == 3) { shot->from_option_l(); sai.angle = 184; }
			else/*i == 2*/ { shot->from_option_r(); sai.angle = 200; }
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
	SHOT_FUNC_INIT(2, SC_3X, SC_2X, add_secondary(2));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 2) {
			if(sai.i == 2) { shot->pos.cur.x -= 8; }
			else/*i == 1*/ { shot->pos.cur.x += 8; }
			shot->damage = 8;
		} else {
			if(sai.i == 4) {
				shot->from_option_l();
				sai.angle = 184;
			} else {
				shot->from_option_r();
				sai.angle = 200;
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
	SHOT_FUNC_INIT(3, SC_3X, SC_2X, add_secondary(2));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 3) {
			if(sai.i == 3) {
				sai.angle = 180;
			}
			shot->damage = 7;
			sai.angle += 6;
		} else {
			if(sai.i == 5) {
				shot->from_option_l();
				sai.angle = randring_angle(7, 180);
			} else {
				shot->from_option_r();
				sai.angle = randring_angle(7, 196);
				if(option_only == 0) {
					sai.i = 1;
				}
			}
			shot->pos.velocity.y = 2;
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
	SHOT_FUNC_INIT(3, SC_3X, SC_2X, add_secondary(4));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 3) {
			shot->damage = 7;
			if(sai.i == 3) {
				sai.angle = 180;
			}
			sai.angle += 6;
		} else {
			switch(sai.i - 4u) {
			case 0:
				if(option_only == 0) {
					sai.i = 1;
				}
			       	shot->from_option_l();	sai.angle = 178;	break;
			case 1:	shot->from_option_r();	sai.angle = 206;	break;
			case 2:	shot->from_option_l();	sai.angle = 186;	break;
			case 3:	shot->from_option_r();	sai.angle = 198;	break;
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
	SHOT_FUNC_INIT(4, SC_3X, SC_2X, add_secondary(4));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 4) {
			YUUKA_INNER_L4;
		} else {
			switch(sai.i - 5u) {
			case 0:	shot->from_option_l();	sai.angle = 176;
				if(option_only == 0) {
					sai.i = 1;
				}
				break;
			case 1:	shot->from_option_r();	sai.angle = 208;	break;
			case 2:	shot->from_option_l();	sai.angle = 184;	break;
			case 3:	shot->from_option_r();	sai.angle = 200;	break;
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
	SHOT_FUNC_INIT(4, SC_3X, SC_2X, add_secondary(6));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 4) {
			YUUKA_INNER_L4;
		} else {
			switch(sai.i - 5u) {
			case 0:	shot->from_option_l();	sai.angle = 176;
				if(option_only == 0) {
					sai.i = 1;
				}
				break;
			case 1:	shot->from_option_r();	sai.angle = 208;	break;
			case 2:	shot->from_option_l();	sai.angle = 183;	break;
			case 3:	shot->from_option_r();	sai.angle = 201;	break;
			case 4:	shot->from_option_l();	sai.angle = 190;	break;
			case 5:	shot->from_option_r();	sai.angle = 194;	break;
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
	SHOT_FUNC_INIT(5, SC_3X, SC_2X, add_secondary(6));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 5) {
			YUUKA_INNER_L5;
		} else {
			switch(sai.i - 6u) {
			case 0:	shot->from_option_l();	sai.angle = 176;
				if(option_only == 0) {
					sai.i = 1;
				}
				break;
			case 1:	shot->from_option_r();	sai.angle = 208;	break;
			case 2:	shot->from_option_l();	sai.angle = 183;	break;
			case 3:	shot->from_option_r();	sai.angle = 201;	break;
			case 4:	shot->from_option_l();	sai.angle = 190;	break;
			case 5:	shot->from_option_r();	sai.angle = 194;	break;
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
	SHOT_FUNC_INIT(5, SC_3X, SC_2X, add_secondary(8));
	char option_only = cycle & SC_3X;

	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 5) {
			YUUKA_INNER_L5;
		} else {
			switch(sai.i - 6u) {
			case 0:	shot->from_option_l();	sai.angle = 168;
				if(option_only == 0) {
					sai.i = 1;
				}
				break;
			case 1:	shot->from_option_r();	sai.angle = 216;	break;
			case 2:	shot->from_option_l();	sai.angle = 176;	break;
			case 3:	shot->from_option_r();	sai.angle = 208;	break;
			case 4:	shot->from_option_l();	sai.angle = 184;	break;
			case 5:	shot->from_option_r();	sai.angle = 200;	break;
			case 6:	shot->from_option_l();	sai.angle = 193;	break;
			case 7:	shot->from_option_r();	sai.angle = 191;	break;
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

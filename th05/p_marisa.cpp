/* ReC98
 * -----
 * Marisa's shot control functions
 */

#pragma codeseg main_01_TEXT

extern "C" {
#include "th05/th05.hpp"
#include "th05/player/shot.h"
#define cycle _AL

#define STAR_DISTANCE      (16)
#define STAR_OFFSET(count) (8 - ((count / 2) * STAR_DISTANCE))

#define MARISA_STARS(dmg) \
	shot->pos.cur.x.v += star_distance; \
	shot->damage = dmg; \
	VELOCITY_Y(-12); \
	star_distance += to_sp(STAR_DISTANCE);

void pascal near shot_marisa_l2(void)
{
#undef STAR_COUNT
#define STAR_COUNT 1
	SHOT_FUNC_INIT(STAR_COUNT, SC_3X, SC_1X, i += 2);
	while(( shot = shots_add() ) != NULL) {
		if(sai.i == STAR_COUNT) {
			shot->set_random_angle_forwards();
			shot->damage = 8;
		} else {
			if(sai.i == 3) { OPT_L;	MISSILE_L;	VELOCITY_X(-1.625f); }
			else/*i == 2*/ { OPT_R;	MISSILE_R;	VELOCITY_X( 1.625f); }
			VELOCITY_Y(2);
			shot->set_option_sprite_and_damage(16);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_marisa_l3(void)
{
#undef STAR_COUNT
#define STAR_COUNT 2
	SHOT_FUNC_INIT(STAR_COUNT, SC_3X, SC_1X, i += 4);
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= STAR_COUNT) {
			if(sai.i == STAR_COUNT) { shot->pos.cur.x -= STAR_OFFSET(0); }
			else /* sai_i == 1 */   { shot->pos.cur.x += STAR_OFFSET(0); }
			shot->damage = 7;
		} else {
			switch(sai.i - 3u) {
			case 0:	OPT_L;	MISSILE_L;	VELOCITY_XY(-1.375f, 2.25f);	break;
			case 1:	OPT_R;	MISSILE_R;	VELOCITY_XY( 1.375f, 2.25f);	break;
			case 2:	OPT_L;	MISSILE_S;	VELOCITY_Y(-3);	break;
			case 3:	OPT_R;	MISSILE_S;	VELOCITY_Y(-3);	break;
			}
			shot->set_option_sprite_and_damage(13);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_marisa_l4(void)
{
#undef STAR_COUNT
#define STAR_COUNT 3
	SHOT_FUNC_INIT(STAR_COUNT, SC_3X, SC_1X, i += 6);
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= STAR_COUNT) {
			if(sai.i == STAR_COUNT) {
				sai.angle = 180;
			}
			shot->damage = 6;
			sai.angle += 6;
			shot_velocity_set(&shot->pos.velocity, sai.angle);
		} else {
			switch(sai.i - 4u) {
			case 0: OPT_L;	MISSILE_L;	VELOCITY_XY(-1.375f, 2.25f);	break;
			case 1: OPT_R;	MISSILE_R;	VELOCITY_XY( 1.375f, 2.25f);	break;
			case 2: OPT_L;	MISSILE_S;	VELOCITY_XY(-1, -3);	break;
			case 3: OPT_R;	MISSILE_S;	VELOCITY_XY( 1, -3);	break;
			case 4:	OPT_L;	MISSILE_S;	VELOCITY_XY(0, -4);	break;
			case 5: OPT_R;	MISSILE_S;	VELOCITY_XY(0, -4);	break;
			}
			shot->set_option_sprite_and_damage(12);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_marisa_l5(void)
{
#undef STAR_COUNT
#define STAR_COUNT 3
	SHOT_FUNC_INIT(STAR_COUNT, SC_3X, SC_1X, i += 6);
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= STAR_COUNT) {
			shot->damage = 6;
			if(sai.i == STAR_COUNT) {
				sai.angle = 178;
			}
			sai.angle += 7;
			shot_velocity_set(&shot->pos.velocity, sai.angle);
		} else {
			switch(sai.i - 4u) {
			case 0: OPT_L;	MISSILE_L;	VELOCITY_XY(-1.375f, 2.25f);	break;
			case 1: OPT_R;	MISSILE_R;	VELOCITY_XY( 1.375f, 2.25f);	break;
			case 2: OPT_L;	MISSILE_S;	VELOCITY_XY(-1, -3);	break;
			case 3: OPT_R;	MISSILE_S;	VELOCITY_XY( 1, -3);	break;
			case 4:	OPT_L;	MISSILE_S;	VELOCITY_XY( 0.5f, -4);	break;
			case 5:	OPT_R;	MISSILE_S;	VELOCITY_XY(-0.5f, -4);	break;
			}
			shot->set_option_sprite_and_damage(11);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_marisa_l6(void)
{
#undef STAR_COUNT
#define STAR_COUNT 4
	SHOT_FUNC_INIT(STAR_COUNT, SC_3X, SC_1X, i += 8);
	subpixel_t star_distance = to_sp(STAR_OFFSET(STAR_COUNT));
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= STAR_COUNT) {
			MARISA_STARS(5);
		} else {
			switch(sai.i - 5u) {
			case 0:	OPT_L;	MISSILE_L;	VELOCITY_XY(-1.375f, 2.25f);	break;
			case 1:	OPT_R;	MISSILE_R;	VELOCITY_XY( 1.375f, 2.25f);	break;
			case 2:	OPT_L;	MISSILE_S;	VELOCITY_XY(-1, -3);	break;
			case 3:	OPT_R;	MISSILE_S;	VELOCITY_XY( 1, -3);	break;
			case 4:	OPT_L;	MISSILE_S;	VELOCITY_Y(-5);	break;
			case 5:	OPT_R;	MISSILE_S;	VELOCITY_Y(-5);	break;
			case 6:	OPT_L;	MISSILE_S;	VELOCITY_Y(-2);	break;
			case 7:	OPT_R;	MISSILE_S;	VELOCITY_Y(-2);	break;
			}
			shot->set_option_sprite_and_damage(11);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

#define MARISA_L7(star_count, star_damage, missile_count, missile_damage) \
	SHOT_FUNC_INIT(star_count, SC_3X, SC_1X, i += missile_count); \
	subpixel_t star_distance = to_sp(STAR_OFFSET(star_count)); \
	while(( shot = shots_add() ) != NULL) { \
		if(sai.i <= star_count) { \
			MARISA_STARS(star_damage); \
		} else { \
			switch(sai.i - 5u) { \
			case 0:	OPT_L;	MISSILE_L;	VELOCITY_XY(-1.75f, 2.25f);	break; \
			case 1:	OPT_R;	MISSILE_R;	VELOCITY_XY( 1.75f, 2.25f);	break; \
			case 2:	OPT_L;	MISSILE_R;	VELOCITY_XY( 2,  2);	break; \
			case 3:	OPT_R;	MISSILE_L;	VELOCITY_XY(-2,  2);	break; \
			case 4:	OPT_L;	MISSILE_S;	VELOCITY_YX( 3, -1);	break; \
			case 5:	OPT_R;	MISSILE_S;	VELOCITY_YX( 3,  1);	break; \
			case 6:	OPT_L;	MISSILE_S;	VELOCITY_Y(-5);	break; \
			case 7:	OPT_R;	MISSILE_S;	VELOCITY_Y(-5);	break; \
			case 8:	OPT_L;	MISSILE_S;	VELOCITY_Y(-2);	break; \
			case 9:	OPT_R;	MISSILE_S;	VELOCITY_Y(-2);	break; \
			} \
			shot->set_option_sprite_and_damage(missile_damage); \
		} \
		if(sai.next() <= 0) { \
			break; \
		} \
	}

void pascal near shot_marisa_l7(void)
{
	MARISA_L7(4, 5, 10, 11);
}

void pascal near shot_marisa_l8(void)
{
	MARISA_L7(4, 4, 10, 10);
}

void pascal near shot_marisa_l9(void)
{
#undef STAR_COUNT
#define STAR_COUNT 6

	SHOT_FUNC_INIT(STAR_COUNT, SC_3X, SC_1X, i += 12);
	subpixel_t star_distance = to_sp(STAR_OFFSET(STAR_COUNT));
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= STAR_COUNT) {
			MARISA_STARS(4);
		} else {
			switch(sai.i - 7u) {
			case  0:	OPT_L;	MISSILE_L;	VELOCITY_XY(-2, 2.25f);	break;
			case  1:	OPT_R;	MISSILE_R;	VELOCITY_XY( 2, 2.25f);	break;
			case  2:	OPT_L;	MISSILE_R;	VELOCITY_XY( 2, 2);	break;
			case  3:	OPT_R;	MISSILE_L;	VELOCITY_XY(-2, 2);	break;
			case  4:	OPT_L;	MISSILE_S;	VELOCITY_Y(3);	break;
			case  5:	OPT_R;	MISSILE_S;	VELOCITY_Y(3);	break;
			case  6:	OPT_L;	MISSILE_S;	VELOCITY_YX( 0, -1);	break;
			case  7:	OPT_R;	MISSILE_S;	VELOCITY_YX( 0,  1);	break;
			case  8:	OPT_L;	MISSILE_S;	VELOCITY_Y(-8);	break;
			case  9:	OPT_R;	MISSILE_S;	VELOCITY_Y(-8);	break;
			case 10:	OPT_L;	MISSILE_S;	VELOCITY_Y(-4);	break;
			case 11:	OPT_R;	MISSILE_S;	VELOCITY_Y(-4);	break;
			case 12:	OPT_L;	MISSILE_S;	VELOCITY_Y(-1);	break;
			case 13:	OPT_R;	MISSILE_S;	VELOCITY_Y(-1);	break;
			}
			shot->set_option_sprite_and_damage(9);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

}

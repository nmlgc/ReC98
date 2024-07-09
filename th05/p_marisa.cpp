/* ReC98
 * -----
 * Marisa's shot control functions
 */

#pragma option -zCmain_01_TEXT -zPmain_01

#include "th05/main/player/shot.hpp"
#define cycle _AL

extern "C" {

#pragma option -a2

static const subpixel_t STAR_DISTANCE = TO_SP(16);
inline subpixel_t star_offset(int count) {
	return (to_sp(8.0f) - ((count / 2) * STAR_DISTANCE));
}

#define marisa_stars(shot, dmg) \
	shot->pos.cur.x.v += star_distance; \
	shot->damage = dmg; \
	shot->pos.velocity.y.set(-12.0f); \
	star_distance += STAR_DISTANCE;

void pascal near shot_marisa_l2(void)
{
#undef STAR_COUNT
#define STAR_COUNT 1
	shot_func_init(shot, sai, cycle, STAR_COUNT, SC_3X, SC_1X, i += 2);
	while(( shot = shots_add() ) != nullptr) {
		if(sai.i == STAR_COUNT) {
			shot->set_random_angle_forwards();
			shot->damage = 8;
		} else {
			if(sai.i == 3) { OPT_L;	MISSILE_L;	VELOCITY_X(-1.625f); }
			else/*i == 2*/ { OPT_R;	MISSILE_R;	VELOCITY_X( 1.625f); }
			VELOCITY_Y(2.0f);
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
	shot_func_init(shot, sai, cycle, STAR_COUNT, SC_3X, SC_1X, i += 4);
	while(( shot = shots_add() ) != nullptr) {
		if(sai.i <= STAR_COUNT) {
			if(sai.i == STAR_COUNT) { shot->pos.cur.x.v -= star_offset(0); }
			else /* sai_i == 1 */   { shot->pos.cur.x.v += star_offset(0); }
			shot->damage = 7;
		} else {
			switch(sai.i - 3u) {
			case 0:	OPT_L;	MISSILE_L;	VELOCITY_XY(-1.375f, 2.25f);	break;
			case 1:	OPT_R;	MISSILE_R;	VELOCITY_XY( 1.375f, 2.25f);	break;
			case 2:	OPT_L;	MISSILE_S;	VELOCITY_Y(-3.0f);	break;
			case 3:	OPT_R;	MISSILE_S;	VELOCITY_Y(-3.0f);	break;
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
	shot_func_init(shot, sai, cycle, STAR_COUNT, SC_3X, SC_1X, i += 6);
	while(( shot = shots_add() ) != nullptr) {
		if(sai.i <= STAR_COUNT) {
			if(sai.i == STAR_COUNT) {
				sai.angle = -0x4C;
			}
			shot->damage = 6;
			sai.angle += 0x06;
			shot_velocity_set(&shot->pos.velocity, sai.angle);
		} else {
			switch(sai.i - 4u) {
			case 0: OPT_L;	MISSILE_L;	VELOCITY_XY(-1.375f, 2.25f);	break;
			case 1: OPT_R;	MISSILE_R;	VELOCITY_XY( 1.375f, 2.25f);	break;
			case 2: OPT_L;	MISSILE_S;	VELOCITY_XY(-1.0f, -3.0f);	break;
			case 3: OPT_R;	MISSILE_S;	VELOCITY_XY( 1.0f, -3.0f);	break;
			case 4:	OPT_L;	MISSILE_S;	VELOCITY_XY( 0.0f, -4.0f);	break;
			case 5: OPT_R;	MISSILE_S;	VELOCITY_XY( 0.0f, -4.0f);	break;
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
	shot_func_init(shot, sai, cycle, STAR_COUNT, SC_3X, SC_1X, i += 6);
	while(( shot = shots_add() ) != nullptr) {
		if(sai.i <= STAR_COUNT) {
			shot->damage = 6;
			if(sai.i == STAR_COUNT) {
				sai.angle = -0x4E;
			}
			sai.angle += 0x07;
			shot_velocity_set(&shot->pos.velocity, sai.angle);
		} else {
			switch(sai.i - 4u) {
			case 0: OPT_L;	MISSILE_L;	VELOCITY_XY(-1.375f, 2.25f);	break;
			case 1: OPT_R;	MISSILE_R;	VELOCITY_XY( 1.375f, 2.25f);	break;
			case 2: OPT_L;	MISSILE_S;	VELOCITY_XY(-1.0f, -3.0f);	break;
			case 3: OPT_R;	MISSILE_S;	VELOCITY_XY( 1.0f, -3.0f);	break;
			case 4:	OPT_L;	MISSILE_S;	VELOCITY_XY( 0.5f, -4.0f);	break;
			case 5:	OPT_R;	MISSILE_S;	VELOCITY_XY(-0.5f, -4.0f);	break;
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
	shot_func_init(shot, sai, cycle, STAR_COUNT, SC_3X, SC_1X, i += 8);
	subpixel_t star_distance = star_offset(STAR_COUNT);
	while(( shot = shots_add() ) != nullptr) {
		if(sai.i <= STAR_COUNT) {
			marisa_stars(shot, 5);
		} else {
			switch(sai.i - 5u) {
			case 0:	OPT_L;	MISSILE_L;	VELOCITY_XY(-1.375f, 2.25f);	break;
			case 1:	OPT_R;	MISSILE_R;	VELOCITY_XY( 1.375f, 2.25f);	break;
			case 2:	OPT_L;	MISSILE_S;	VELOCITY_XY(-1.0f, -3.0f);	break;
			case 3:	OPT_R;	MISSILE_S;	VELOCITY_XY( 1.0f, -3.0f);	break;
			case 4:	OPT_L;	MISSILE_S;	VELOCITY_Y(-5.0f);	break;
			case 5:	OPT_R;	MISSILE_S;	VELOCITY_Y(-5.0f);	break;
			case 6:	OPT_L;	MISSILE_S;	VELOCITY_Y(-2.0f);	break;
			case 7:	OPT_R;	MISSILE_S;	VELOCITY_Y(-2.0f);	break;
			}
			shot->set_option_sprite_and_damage(11);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

#define MARISA_L7(star_count, star_damage, missile_count, missile_damage) \
	shot_func_init( \
		shot, sai, cycle, star_count, SC_3X, SC_1X, i += missile_count \
	); \
	subpixel_t star_distance = star_offset(star_count); \
	while(( shot = shots_add() ) != nullptr) { \
		if(sai.i <= star_count) { \
			marisa_stars(shot, star_damage); \
		} else { \
			switch(sai.i - 5u) { \
			case 0:	OPT_L;	MISSILE_L;	VELOCITY_XY(-1.75f, 2.25f);	break; \
			case 1:	OPT_R;	MISSILE_R;	VELOCITY_XY( 1.75f, 2.25f);	break; \
			case 2:	OPT_L;	MISSILE_R;	VELOCITY_XY( 2.0f,  2.0f);	break; \
			case 3:	OPT_R;	MISSILE_L;	VELOCITY_XY(-2.0f,  2.0f);	break; \
			case 4:	OPT_L;	MISSILE_S;	VELOCITY_YX( 3.0f, -1.0f);	break; \
			case 5:	OPT_R;	MISSILE_S;	VELOCITY_YX( 3.0f,  1.0f);	break; \
			case 6:	OPT_L;	MISSILE_S;	VELOCITY_Y(-5.0f);	break; \
			case 7:	OPT_R;	MISSILE_S;	VELOCITY_Y(-5.0f);	break; \
			case 8:	OPT_L;	MISSILE_S;	VELOCITY_Y(-2.0f);	break; \
			case 9:	OPT_R;	MISSILE_S;	VELOCITY_Y(-2.0f);	break; \
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

	shot_func_init(shot, sai, cycle, STAR_COUNT, SC_3X, SC_1X, i += 12);
	subpixel_t star_distance = star_offset(STAR_COUNT);
	while(( shot = shots_add() ) != nullptr) {
		if(sai.i <= STAR_COUNT) {
			marisa_stars(shot, 4);
		} else {
			switch(sai.i - 7u) {
			case  0:	OPT_L;	MISSILE_L;	VELOCITY_XY(-2.0f, 2.25f);	break;
			case  1:	OPT_R;	MISSILE_R;	VELOCITY_XY( 2.0f, 2.25f);	break;
			case  2:	OPT_L;	MISSILE_R;	VELOCITY_XY( 2.0f, 2.0f);	break;
			case  3:	OPT_R;	MISSILE_L;	VELOCITY_XY(-2.0f, 2.0f);	break;
			case  4:	OPT_L;	MISSILE_S;	VELOCITY_Y(3.0f);	break;
			case  5:	OPT_R;	MISSILE_S;	VELOCITY_Y(3.0f);	break;
			case  6:	OPT_L;	MISSILE_S;	VELOCITY_YX( 0.0f, -1.0f);	break;
			case  7:	OPT_R;	MISSILE_S;	VELOCITY_YX( 0.0f,  1.0f);	break;
			case  8:	OPT_L;	MISSILE_S;	VELOCITY_Y(-8.0f);	break;
			case  9:	OPT_R;	MISSILE_S;	VELOCITY_Y(-8.0f);	break;
			case 10:	OPT_L;	MISSILE_S;	VELOCITY_Y(-4.0f);	break;
			case 11:	OPT_R;	MISSILE_S;	VELOCITY_Y(-4.0f);	break;
			case 12:	OPT_L;	MISSILE_S;	VELOCITY_Y(-1.0f);	break;
			case 13:	OPT_R;	MISSILE_S;	VELOCITY_Y(-1.0f);	break;
			}
			shot->set_option_sprite_and_damage(9);
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

}

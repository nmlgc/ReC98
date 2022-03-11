/* ReC98
 * -----
 * Mima's shot control functions
 */

#pragma option -zCmain_01_TEXT -zPmain_01

extern "C" {
#include "th05/i_shot.hpp"
#define cycle _AL

#pragma option -a2

void pascal near shot_mima_l2(void)
{
	shot_func_init(shot, sai, cycle, 2, SC_6X, SC_3X, i++);
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 2) {
			if(sai.i == 2) { shot->from_option_l(); }
			else/*i == 1*/ { shot->from_option_r(); }
			shot->pos.velocity.y.set(-20.0f);
			shot->set_option_sprite_and_damage(5);
		} else {
			shot->set_random_angle_forwards();
			shot->damage = 8;
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_mima_l3(void)
{
	shot_func_init(shot, sai, cycle, 2, SC_6X, SC_3X, i += 2);
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 2) {
			if(sai.i == 2) { shot->from_option_l(); }
			else/*i == 1*/ { shot->from_option_r(); }
			shot->pos.velocity.y.set(-20.0f);
			shot->set_option_sprite_and_damage(5);
		} else {
			if(sai.i == 4) { shot->pos.cur.x -= 8.0f; }
			else/*i == 3*/ { shot->pos.cur.x += 8.0f; }
			shot->pos.velocity.y.set(-12.0f);
			shot->damage = 7;
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_mima_l4(void)
{
	shot_func_init(shot, sai, cycle, 4, SC_6X, SC_3X, i += 2);
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 4) {
			switch(sai.i - 1) {
			// Beware, non-sequential case order!
			case 1:	VELOCITY_X(-1.0f);	shot->from_option_l();	break;
			case 0:	VELOCITY_X( 1.0f);	shot->from_option_r();	break;
			case 3:	                  	shot->from_option_l();	break;
			case 2:	                  	shot->from_option_r();	break;
			}
			shot->pos.velocity.y.set(-20.0f);
			shot->set_option_sprite_and_damage(4);
		} else {
			if(sai.i == 6) { shot->pos.cur.x -= 8.0f; }
			else/* i== 5*/ { shot->pos.cur.x += 8.0f; }
			shot->pos.velocity.y.set(-12.0f);
			shot->damage = 7;
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_mima_l5(void)
{
	shot_func_init(shot, sai, cycle, 4, SC_6X, SC_3X, i += 3);
	sai.angle = -0x46;
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 4) {
			switch(sai.i - 1) {
			// Beware, non-sequential case order!
			case 0:	VELOCITY_X( 1.0f);	shot->from_option_l();	break;
			case 3:	                  	shot->from_option_l();	break;
			case 1:	VELOCITY_X(-1.0f);	shot->from_option_r();	break;
			case 2:	                  	shot->from_option_r();	break;
			}
			shot->pos.velocity.y.set(-20.0f);
			shot->set_option_sprite_and_damage(4);
		} else {
			shot_velocity_set(&shot->pos.velocity, sai.angle);
			sai.angle += 0x06;
			shot->damage = 7;
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_mima_l6(void)
{
	shot_func_init(shot, sai, cycle, 4, SC_6X, SC_3X, i += 3);
	sai.angle = -0x46;
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 4) {
			switch(sai.i - 1) {
			case 0:	VELOCITY_X( 1.0f);	shot->from_option_r();	break;
			case 1:	VELOCITY_X(-1.0f);	shot->from_option_l();	break;
			case 2:	VELOCITY_X(-0.5f);	shot->from_option_r();	break;
			case 3:	VELOCITY_X( 0.5f);	shot->from_option_l();	break;
			}
			shot->pos.velocity.y.set(-20.0f);
			shot->set_option_sprite_and_damage(4);
		} else {
			shot_velocity_set(&shot->pos.velocity, sai.angle);
			sai.angle += 0x06;
			shot->damage = 7;
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_mima_l7(void)
{
	shot_func_init(shot, sai, cycle, 6, SC_6X, SC_3X, i += 3);
	sai.angle = -0x46;
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 6) {
			switch(sai.i - 1) {
			// Beware, non-sequential case order!
			case 0:	VELOCITY_X( 1.0f);	shot->from_option_r(4.0f);	break;
			case 1:	VELOCITY_X(-1.0f);	shot->from_option_l(4.0f);	break;
			case 2:	VELOCITY_X(-0.5f);	shot->from_option_r();	break;
			case 4:	                 	shot->from_option_r();	break;
			case 3:	VELOCITY_X( 0.5f);	shot->from_option_l();	break;
			case 5:	                	shot->from_option_l();	break;
			}
			shot->pos.velocity.y.set(-20.0f);
			shot->set_option_sprite_and_damage(4);
		} else {
			shot_velocity_set(&shot->pos.velocity, sai.angle);
			sai.angle += 0x06;
			shot->damage = 7;
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_mima_l8(void)
{
	shot_func_init(shot, sai, cycle, 6, SC_6X, SC_3X, i += 3);
	sai.angle = -0x46;
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 6) {
			shot->pos.velocity.y.set(-20.0f);
			switch(sai.i - 1) {
			// Beware, non-sequential case order!
			case 0:	VELOCITY_XY( 1.75f, -18.0f); shot->from_option_r(8.0f);	break;
			case 1:	VELOCITY_XY(-1.75f, -18.0f); shot->from_option_l(8.0f);	break;
			case 2:	VELOCITY_X (-0.5f);          shot->from_option_r();	break;
			case 4:	                             shot->from_option_r();	break;
			case 3:	VELOCITY_X ( 0.5f);          shot->from_option_l();	break;
			case 5:                              shot->from_option_l();	break;
			}
			shot->pos.velocity.y.set(-20.0f);
			shot->set_option_sprite_and_damage(4);
		} else {
			shot_velocity_set(&shot->pos.velocity, sai.angle);
			sai.angle += 0x06;
			shot->damage = 7;
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

void pascal near shot_mima_l9(void)
{
	shot_func_init(shot, sai, cycle, 6, SC_6X, SC_3X, i += 4);
	while(( shot = shots_add() ) != NULL) {
		if(sai.i <= 6) {
			shot->pos.velocity.y.set(-20.0f);
			switch(sai.i - 1) {
			case 0:	VELOCITY_XY( 2.625f, -18.0f); shot->from_option_r(8.0f); break;
			case 1:	VELOCITY_XY(-2.625f, -18.0f); shot->from_option_l(8.0f); break;
			case 2:	VELOCITY_X (-0.5f);       	shot->from_option_r();	break;
			case 3:	VELOCITY_X ( 0.5f);       	shot->from_option_l();	break;
			case 4:	VELOCITY_X ( 0.5f);       	shot->from_option_r();	break;
			case 5:	VELOCITY_X (-0.5f);       	shot->from_option_l();	break;
			}
			shot->set_option_sprite_and_damage(4);
		} else {
			switch(sai.i - 7u) {
			case 0:	sai.angle = -0x48;	                        	break;
			case 1:	sai.angle = -0x40;	shot->pos.cur.x -= 8.0f;	break;
			case 2:	sai.angle = -0x40;	shot->pos.cur.x += 8.0f;	break;
			case 3:	sai.angle = -0x38;	                         	break;
			}
			shot_velocity_set(&shot->pos.velocity, sai.angle);
			shot->damage = 7;
		}
		if(sai.next() <= 0) {
			break;
		}
	}
}

}

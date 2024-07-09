/* ReC98
 * -----
 * Generic shot control functions
 */

#pragma option -zCmain_01_TEXT -zPmain_01

#include "th05/main/player/shot.hpp"
#include "th02/snd/snd.h"

#pragma option -a2

char near shot_cycle_init(void)
{
	char cycle_flag = 0;
	switch(shot_time) {
	case 18:
		cycle_flag = SC_6X | SC_3X | SC_2X | SC_1X;
		snd_se_play(1);
		break;
	case 15:
		cycle_flag = SC_6X;
		break;
	case 12:
		cycle_flag = SC_6X | SC_3X;
		snd_se_play(1);
		break;
	case  9:
		cycle_flag = SC_6X | SC_2X;
		break;
	case  6:
		cycle_flag = SC_6X | SC_3X;
		snd_se_play(1);
		break;
	case  3:
		cycle_flag = SC_6X;
		break;
	default:
		return 0;
	}
	shot_ptr = shots;
	shot_last_id = 0;
	return cycle_flag;
}

void pascal near shot_l0(void)
{
	if( (shot_cycle_init() & SC_3X) == 0) {
		return;
	}
	Shot near *shot;
	if(( shot = shots_add() ) != nullptr) {
		shot->damage = 10;
	}
}

void pascal near shot_l1(void)
{
	if( (shot_cycle_init() & SC_3X) == 0) {
		return;
	}
	Shot near *shot;
	if(( shot = shots_add() ) != nullptr) {
		shot_velocity_set(
			&shot->pos.velocity, randring1_next8_and_ge_lt(-0x44, -0x3C)
		);
		shot->damage = 10;
	}
}


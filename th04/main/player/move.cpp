#pragma option -zPmain_01

#include "th04/main/player/player.hpp"
#include "th04/main/player/move.hpp"

inline void move(int direction_x, int direction_y) {
	if((direction_x != 0) && (direction_y != 0)) {
		player_pos.velocity.x.v = (direction_x * playchar_speed_diagonal);
		player_pos.velocity.y.v = (direction_y * playchar_speed_diagonal);
	} else if(direction_x != 0) {
		player_pos.velocity.x.v = (direction_x * playchar_speed_aligned);
	} else if(direction_y != 0) {
		player_pos.velocity.y.v = (direction_y * playchar_speed_aligned);
	}
}

move_ret_t pascal near player_move(input_t input)
{
	move_ret_t ret = MOVE_VALID;
	switch(input) {
	case INPUT_NONE:                	ret = MOVE_NOINPUT;	break;
	case INPUT_LEFT:                	move(-1,  0);      	break;
	case (INPUT_DOWN | INPUT_LEFT):
	case INPUT_DOWN_LEFT:           	move(-1, +1);      	break;
	case INPUT_DOWN:                	move( 0, +1);      	break;
	case (INPUT_DOWN | INPUT_RIGHT):
	case INPUT_DOWN_RIGHT:          	move(+1, +1);      	break;
	case INPUT_RIGHT:               	move(+1,  0);      	break;
	case (INPUT_UP | INPUT_RIGHT):
	case INPUT_UP_RIGHT:            	move(+1, -1);      	break;
	case INPUT_UP:                  	move( 0, -1);      	break;
	case (INPUT_UP | INPUT_LEFT):
	case INPUT_UP_LEFT:             	move(-1, -1);      	break;
	default:                        	ret = MOVE_INVALID;	break;
	}
	return ret;
}

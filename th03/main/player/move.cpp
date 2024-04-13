#pragma option -zPmain_01 -G

#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th03/hardware/input.h"
#include "th03/playchar.hpp"
#include "th03/main/chars/speed.hpp"
#include "th03/main/player/move.hpp"

#pragma option -a2

inline void move(Subpixel8& dim, const Subpixel8& speed, int8_t direction) {
	if(direction == -1) {
		dim.v = -speed;
	} else {
		dim.v = +speed;
	}
}

inline void move(int8_t direction_x, int8_t direction_y) {
	if((direction_x != 0) && (direction_y != 0)) {
		move(player_velocity.x, player_speed_base.diagonal.x, direction_x);
		move(player_velocity.y, player_speed_base.diagonal.y, direction_y);
	} else if(direction_x != 0) {
		move(player_velocity.x, player_speed_base.aligned.x, direction_x);
	} else if(direction_y != 0) {
		move(player_velocity.y, player_speed_base.aligned.y, direction_y);
	}
}

move_ret_t pascal near player_move(input_t input)
{
	player_velocity.set(0, 0);
	switch(input) {
	case INPUT_LEFT:               	move(-1,  0);	goto valid;
	case (INPUT_DOWN | INPUT_LEFT):
	case INPUT_DOWN_LEFT:          	move(-1, +1);	goto valid;
	case INPUT_DOWN:               	move( 0, +1);	goto valid;
	case (INPUT_DOWN | INPUT_RIGHT):
	case INPUT_DOWN_RIGHT:         	move(+1, +1);	goto valid;
	case INPUT_RIGHT:              	move(+1,  0);	goto valid;
	case (INPUT_UP | INPUT_RIGHT):
	case INPUT_UP_RIGHT:           	move(+1, -1);	goto valid;
	case INPUT_UP:                 	move( 0, -1);	goto valid;
	case (INPUT_UP | INPUT_LEFT):
	case INPUT_UP_LEFT:            	move(-1, -1);	goto valid;

	default:        	return MOVE_INVALID;
	valid:          	return MOVE_VALID;
	case INPUT_NONE:	return MOVE_NOINPUT;
	}
}

/* ReC98
 * -----
 * Code segment #2 of TH01's FUUIN.EXE
 */

#include "platform.h"
#include "pc98.h"
#include "pc98kbd.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th01/hardware/input.hpp"

#include "th01/hardware/grppfnfx.cpp"

// Input
// -----

void input_sense(bool16 reset_repeat)
{
	static uint8_t input_prev[10];
	int group_1, group_2;

	if(reset_repeat == true) {
		input_prev[0] = 0;
		input_prev[1] = 0;
		input_prev[2] = 0;
		input_prev[3] = 0;
		input_prev[4] = 0;
		input_prev[5] = 0;
		input_prev[6] = 0;
		input_prev[7] = 0;
		input_prev[8] = 0;
		input_prev[9] = 0;
		return;
	}

	group_1 = key_sense(7);
	group_2 = key_sense(5);
	group_1 |= key_sense(7);
	group_2 |= key_sense(5);

	input_onchange_bool(0, input_up, (group_1 & K7_ARROW_UP));
	input_onchange_bool(1, input_down, (group_1 & K7_ARROW_DOWN));
	input_onchange_flag(2, input_lr, INPUT_LEFT, (group_1 & K7_ARROW_LEFT));
	input_onchange_flag(3, input_lr, INPUT_RIGHT, (group_1 & K7_ARROW_RIGHT));
	input_onchange_bool(4, input_shot, (group_2 & K5_Z));
	input_onchange_bool(5, input_strike, (group_2 & K5_X));

	input_pause_ok_sense(6, 7, group_1, group_2);
}

#include "th01/hardware/input_rs.cpp"
// -----

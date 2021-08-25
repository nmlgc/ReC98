/* ReC98
 * -----
 * 1st part of code segment #1 of TH01's REIIDEN.EXE
 */

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "master.hpp"
#include "pc98kbd.h"
#include "twobyte.h"
#include "th01/hardware/input.hpp"
#include "th01/main/bomb.hpp"
#include "th01/main/debug.hpp"

inline void bomb_doubletap_update(uint8_t& pressed, uint8_t& other)
{
	if(bomb_doubletap_frames < BOMB_DOUBLETAP_WINDOW) {
		pressed++;
	} else {
		bomb_doubletap_frames = 0;
		pressed = 1;
		other = 0;
	}
}

void input_sense(bool16 reset_repeat)
{
	extern uint8_t input_prev[16];
	int group_1, group_2, group_3, group_4;

	if(reset_repeat == true) {
		input_prev[0] = 0;
		input_prev[1] = 0;
		input_prev[2] = 0;
		input_prev[3] = 0;
		input_prev[8] = 0;
		input_prev[9] = 0;
		input_prev[10] = 0;
		input_prev[11] = 0;
		input_prev[4] = 0;
		input_prev[5] = 0;
		input_prev[6] = 0;
		input_prev[7] = 0;
		input_prev[12] = 0;
		input_prev[13] = 0;
		// Yup, no reset for 14 or 15.
		input_bomb = 0;
		return;
	}
	#define bomb_doubletap_shot input_prev[12]
	#define bomb_doubletap_strike input_prev[13]

	group_1 = key_sense(7);
	group_2 = key_sense(5);
	group_3 = key_sense(8);
	group_4 = key_sense(9);
	group_1 |= key_sense(7);
	group_2 |= key_sense(5);
	group_3 |= key_sense(8);
	group_4 |= key_sense(9);

	input_onchange_bool_2(0, 8,
		input_up, (group_1 & K7_ARROW_UP), (group_3 & K8_NUM_8)
	);
	input_onchange_bool_2(1, 9,
		input_down, (group_1 & K7_ARROW_DOWN), (group_4 & K9_NUM_2)
	);
	input_onchange_flag_2(2, 10,
		input_lr, INPUT_LEFT, (group_1 & K7_ARROW_LEFT), (group_3 & K8_NUM_4)
	);
	input_onchange_flag_2(3, 11,
		input_lr, INPUT_RIGHT, (group_1 & K7_ARROW_RIGHT), (group_4 & K9_NUM_6)
	);
	input_onchange(4, (group_2 & K5_Z), {
		input_shot = true;
		bomb_doubletap_update(bomb_doubletap_shot, bomb_doubletap_strike);
	} else {
		input_shot = false;
	});
	input_onchange(5, (group_2 & K5_X), {
		input_strike = true;
		bomb_doubletap_update(bomb_doubletap_strike, bomb_doubletap_shot);
	} else {
		input_strike = false;
	});

	input_pause_ok_sense(6, 7, group_1, group_2);

	if(
		(bomb_doubletap_strike >= 2 && bomb_doubletap_shot >= 2) ||
		(input_lr == (INPUT_LEFT | INPUT_RIGHT) && input_shot)
	) {
		input_bomb = true;
		bomb_doubletap_strike = 0;
		bomb_doubletap_shot = 0;
	}

	if(mode_test == true) {
		group_1 = key_sense(6);
		group_1 |= key_sense(6);

		// Hilarious bug: test_mem() itself renders a sub-screen in a blocking
		// way, and senses input after a 3-frame delay, thus recursing back
		// into this function. Therefore, test_mem() will also be recursively
		// called for every 3 frames you're holding this key.
		// [input_prev[14]], which is supposed to prevent that, isn't set
		// until test_mem() returns, making this variable entirely pointless.
		input_onchange(14, (group_1 & K6_ROLL_UP), {
			input_mem_enter = true;
			/* TODO: Replace with the decompiled call
			 * 	test_mem();
			 * once that function is part of this translation unit */
			__asm { nop; push cs; call near ptr test_mem; }
		} else {
			input_mem_enter = false;
		});
		// And since this works as intended and only sets [input_mem_leave] to
		// true on the first non-repeated key down event, you need to actually
		// press and release this key once for every call to test_mem() to get
		// back into the game - even though test_show_game() will make it
		// appear as if you're already back in the game.
		input_onchange(15, (group_1 & K6_ROLL_DOWN), {
			input_mem_leave = true;
			/* TODO: Replace with the decompiled call
			 * 	test_show_game();
			 * once that function is part of this translation unit */
			__asm { nop; push cs; call near ptr test_show_game; }
		} else {
			input_mem_leave = false;
		});
	}
}

#include "th01/hardware/input_rs.cpp"
#include "th01/hardware/tram_x16.cpp"

}

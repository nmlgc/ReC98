#include "th01/resident.hpp"
#include "th01/hardware/input.hpp"
#include "th01/main/debug.hpp"
#include "th01/main/player/bomb.hpp"
#include "platform/x86real/pc98/keyboard.hpp"

// State
// -----

uint8_t input_lr = INPUT_NONE;
bool input_mem_enter = false;
bool input_mem_leave = false;
bool input_shot = false;
bool player_is_hit = false;
bool input_bomb = false;
bool paused = false;
bool input_ok = false;
bool input_strike = false;
bool input_up = false;
bool input_down = false;
// -----

inline void bomb_doubletap_update(uint8_t& pressed, uint8_t& other) {
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
	static uint8_t input_prev[16];
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
	if(end_flag != ES_NONE) {
		group_3 = 0;
		group_4 = 0;
	} else {
		group_3 = key_sense(8);
		group_4 = key_sense(9);
	}
	group_1 |= key_sense(7);
	group_2 |= key_sense(5);
	if(end_flag == ES_NONE) {
		group_3 |= key_sense(8);
		group_4 |= key_sense(9);
	}

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
		((input_lr == INPUT_LEFT_RIGHT) && input_shot)
	) {
		input_bomb = true;
		bomb_doubletap_strike = 0;
		bomb_doubletap_shot = 0;
	}

	if((end_flag == ES_NONE) && mode_test) {
		group_1 = key_sense(6);
		group_1 |= key_sense(6);

		// ZUN bug: debug_mem() itself renders a sub-screen in a blocking way,
		// and senses input after a 3-frame delay, thus recursing back into
		// this function. Therefore, debug_mem() will also be recursively
		// called for every 3 frames you're holding this key.
		// [input_prev[14]], which is supposed to prevent that, isn't set
		// until debug_mem() returns, making this variable entirely pointless.
		input_onchange(14, (group_1 & K6_ROLL_UP), {
			input_mem_enter = true;
			debug_mem();
		} else {
			input_mem_enter = false;
		});
		// And since this works as intended and only sets [input_mem_leave] to
		// true on the first non-repeated key down event, you need to actually
		// press and release this key once for every call to debug_mem() to get
		// back into the game - even though debug_show_game() will make it
		// appear as if you're already back in the game.
		input_onchange(15, (group_1 & K6_ROLL_DOWN), {
			input_mem_leave = true;
			debug_show_game();
		} else {
			input_mem_leave = false;
		});
	}
}

void input_reset_sense(void)
{
	input_lr = false;
	input_up = false;
	input_down = false;
	input_ok = false;
	paused = false;
	input_shot = false;
	input_strike = false;
	input_mem_enter = false;
	input_mem_leave = false;

	input_sense(true);
}

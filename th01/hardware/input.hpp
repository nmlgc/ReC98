/// Shared input macros
extern bool input_shot;
extern bool input_ok;

#define input_func_bool(var) { var = true; } else { var = false; }

// REIIDEN.EXE and FUUIN.EXE
// -------------------------
// Hey, at least two inputs merged into a single variable! It's a start.
enum input_lr_t {
	INPUT_NONE = 0,
	INPUT_RIGHT = 1,
	INPUT_LEFT = 2,
	INPUT_RIGHT_LEFT = 3,
	INPUT_LEFT_RIGHT = 3,
};

extern bool input_up;
extern bool input_down;
extern uint8_t input_lr; // input_lr_t
extern bool input_strike;
extern bool input_mem_enter;
extern bool input_mem_leave;
extern bool paused;
extern bool done;
extern bool input_bomb;

// Updates all input-related variables if the held state of their associated
// keys changed compared to the last input.
void input_sense(bool16 reset_repeat);

// Resets all input-related variables, then updates them according to the
// keyboard state.
void input_reset_sense(void);

#define input_func_flag(var, flag) { var |= flag; } else { var &= ~flag; }

#define input_onchange(prev_slot, cur_sensed, if_pressed) \
	if(input_prev[prev_slot] != (cur_sensed)) { \
		if(cur_sensed) if_pressed \
	} \
	input_prev[prev_slot] = (cur_sensed);

#define input_onchange_bool(prev_slot, var, cur_sensed) \
	input_onchange(prev_slot, cur_sensed, input_func_bool(var))

#define input_onchange_flag(prev_slot, var, flag, cur_sensed) \
	input_onchange(prev_slot, cur_sensed, input_func_flag(var, flag))

#define input_onchange_2( \
	prev_slot_1, prev_slot_2, cur_sensed_1, cur_sensed_2, if_pressed \
) \
	if( \
		input_prev[prev_slot_1] != (cur_sensed_1) || \
		input_prev[prev_slot_2] != (cur_sensed_2) \
	) { \
		if(cur_sensed_1 || (cur_sensed_2)) if_pressed \
	} \
	input_prev[prev_slot_1] = (cur_sensed_1); \
	input_prev[prev_slot_2] = (cur_sensed_2);

#define input_onchange_bool_2( \
	prev_slot_1, prev_slot_2, var, cur_sensed_1, cur_sensed_2 \
) \
	input_onchange_2(prev_slot_1, prev_slot_2, \
		cur_sensed_1, cur_sensed_2, input_func_bool(var) \
	)

#define input_onchange_flag_2( \
	prev_slot_1, prev_slot_2, var, flag, cur_sensed_1, cur_sensed_2 \
) \
	input_onchange_2(prev_slot_1, prev_slot_2,  \
		cur_sensed_1, cur_sensed_2, input_func_flag(var, flag) \
	)

#define input_pause_ok_sense(prev_slot_esc, prev_slot_ok, group0, group3) \
	group0 = key_sense(0); \
	group3 = key_sense(3); \
	group0 |= key_sense(0); \
	group3 |= key_sense(3); \
	input_onchange(prev_slot_esc, (group0 & K0_ESC), { \
		paused = (1 - paused); \
	}) \
	input_onchange(prev_slot_ok, (group3 & K3_RETURN), { \
		if((paused == true) && (input_shot == true)) { \
			done = true; \
		} \
		input_ok = true; \
	} else { \
		input_ok = false; \
	});
// -------------------------

#pragma option -zCSHARED

#include "platform.h"
#include "libs/master.lib/master.hpp"
#include "th02/hardware/frmdelay.h"
#include "th03/hardware/input.h"

/// Modes
/// -----
#define js_input_merge_into(input) \
	if(js_bexist) { \
		js_sense(); \
		input |= js_stat[0]; \
	}

void pascal input_mode_interface()
{
	input_reset_sense_key_held();
	js_input_merge_into(input_sp);
	input_sp |= input_mp_p1;
}

void pascal input_mode_key_vs_key()
{
	input_reset_sense_key_held();
}

void pascal input_mode_joy_vs_key()
{
	input_reset_sense_key_held();
	if(js_bexist) {
		js_sense();
		input_mp_p1 = js_stat[0];
		input_mp_p2 = input_sp;
	}
}

void pascal input_mode_key_vs_joy()
{
	input_reset_sense_key_held();
	if(js_bexist) {
		js_sense();
		input_mp_p2 = js_stat[0];
		input_mp_p1 = input_sp;
	}
}

void pascal input_mode_1p_vs_cpu()
{
	input_reset_sense_key_held();
	input_mp_p1 |= input_sp;
	js_input_merge_into(input_mp_p1);
	input_mp_p2 = INPUT_NONE;
}

void pascal input_mode_cpu_vs_1p()
{
	input_reset_sense_key_held();
	input_mp_p2 = (input_sp | input_mp_p1);
	js_input_merge_into(input_mp_p2);
	input_mp_p1 = INPUT_NONE;
}

void pascal input_mode_cpu_vs_cpu()
{
	input_reset_sense_key_held();
	if((input_sp & INPUT_CANCEL) || (input_sp & INPUT_OK)) {
		input_sp = INPUT_CANCEL;
	}
	input_mp_p1 = INPUT_NONE;
	input_mp_p2 = INPUT_NONE;
}

void pascal input_mode_attract()
{
	input_reset_sense_key_held();
	js_input_merge_into(input_sp);
	input_sp |= input_mp_p1;
	input_mp_p1 = INPUT_NONE;
	input_mp_p2 = INPUT_NONE;
}
/// -----

void pascal input_wait_for_change(int frames_to_wait)
{
	int frames_waited = 0;

	// Wait for release
	while(1) {
		input_mode_interface();
		if(input_sp == INPUT_NONE) {
			break;
		}
		frame_delay(1);
	}

	if(!frames_to_wait) {
		frames_to_wait = 9999;
	}

	// Wait for press
	while(frames_waited < frames_to_wait) {
		input_mode_interface();
		if(input_sp != INPUT_NONE) {
			break;
		}
		frames_waited++;
		frame_delay(1);
		if(frames_to_wait == 9999) {
			frames_waited = 0;
		}
	}
}

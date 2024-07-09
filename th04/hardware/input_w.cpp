#pragma option -zCSHARED

#include "th02/hardware/frmdelay.h"
#include "th04/hardware/input.h"

void pascal input_wait_for_change(int frames_to_wait)
{
	int frames_waited = 0;

	// Wait for release
	do {
		input_reset_sense();
		frame_delay(1);
		input_sense();
	} while(key_det != INPUT_NONE);

	if(!frames_to_wait) {
		frames_to_wait = 9999;
	}

	// Wait for press
	while(frames_waited < frames_to_wait) {
		input_reset_sense();
		frame_delay(1);
		input_sense();
		if(key_det != INPUT_NONE) {
			break;
		}
		frames_waited++;
		if(frames_to_wait == 9999) {
			frames_waited = 0;
		}
	}
}

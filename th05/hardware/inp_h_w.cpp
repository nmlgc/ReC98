#pragma option -zCSHARED

#include "platform.h"
#include "master.hpp"
#include "platform/x86real/flags.hpp"
#include "th05/hardware/input.h"

#pragma option -k-

// The key state is checked twice, 614.4 µs apart, to ignore the momentary
// "key released" events sent by PC-98 keyboards at the typematic rate if a
// key is held down. This ensures that the game consistently sees that
// specific input being pressed. See the HOLDKEY example in the `Research/`
// subdirectory for more explanation and sample code showing off this effect.
int16_t input_reset_sense_held()
{
	/* TODO: Replace with the decompiled call
	 * 	input_reset_sense();
	 * once the segmentation allows us to, if ever */
	_asm { push cs; call near ptr input_reset_sense; }
	_CX = 1024; // * 0.6 µs
	delay_loop: asm {
		out 	0x5F, al;
		loop	delay_loop;
	}
	/* TODO: Replace with the decompiled call
	 * 	return input_sense();
	 * once the segmentation allows us to, if ever */
	_asm { push cs; call near ptr input_sense; }
	return _AX;
}

#pragma option -k

int16_t pascal input_wait_for_change(int frames)
{
	#define frames_left	_BP

	while(input_reset_sense_held()) {
	}
	frames_left = frames;
	do {
		if(input_reset_sense_held()) {
			return _AX;
		}
		_AX = vsync_Count1;
		while(_AX == vsync_Count1) {
		}
		if(frames_left) {
			frames_left--;
			if(FLAGS_ZERO) {
				break;
			}
		}
	} while(1);
	return _AX;

	#undef frames_left
}

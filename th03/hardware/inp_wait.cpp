#pragma option -zCSHARED

#include "platform.h"
#include "x86real.h"
#include "master.hpp"
#include "libs/kaja/kaja.h"
#include "th03/hardware/input.h"
#include "th03/snd/snd.h"
#include "th02/snd/measure.hpp"

bool16 pascal input_wait_for_ok_or_measure(int measure, unsigned int frames)
{
	if(!snd_active) {
		return input_wait_for_ok(frames);
	}
	do {
		_AX = snd_get_song_measure();
		input_mode_interface();
		if((input_sp & INPUT_SHOT) || (input_sp & INPUT_OK)) {
			return true;
		}
	} while(_AX < measure);
	return false;
}

bool16 pascal input_wait_for_ok(unsigned int frames)
{
	vsync_Count1 = 0;
	do {
		input_mode_interface();
		if((input_sp & INPUT_SHOT) || (input_sp & INPUT_OK)) {
			return true;
		}
	} while(vsync_Count1 < frames);
	return false;
}

#pragma option -zCSHARED

#include "th02/hardware/frmdelay.h"
#include "th02/snd/measure.hpp"

void pascal snd_delay_until_measure(int measure, unsigned int frames_if_no_bgm)
{
	if(!snd_bgm_active()) {
		frame_delay(frames_if_no_bgm);
		return;
	}
	while(snd_get_song_measure() < measure) {
	}
}

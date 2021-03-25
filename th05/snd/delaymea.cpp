#pragma option -zCSHARED_

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "libs/kaja/kaja.h"
#include "th02/hardware/frmdelay.h"
#include "th05/snd/snd.h"
#include "th02/snd/measure.hpp"
}

int snd_bgm_measure(void)
{
	if(!snd_bgm_active()) {
		return -1;
	}
	return snd_get_song_measure();
}

void pascal snd_delay_until_measure(int measure, unsigned int frames_if_no_bgm)
{
	int measure_cur;
	do {
		measure_cur = snd_bgm_measure();
		if(measure_cur < 0) {
			/* TODO: Replace with the decompiled call
			 * 	frame_delay(frames_if_no_bgm);
			 * once the segmentation allows us to, if ever */
			__asm {
				push frames_if_no_bgm; nop; push cs; call near ptr frame_delay;
			}
			return;
		}
	} while(measure_cur < measure);
}

#pragma codestring "\x00"

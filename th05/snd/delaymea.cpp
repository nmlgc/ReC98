#pragma option -zCSHARED

#include "platform.h"
#include "x86real.h"
#include "libs/kaja/kaja.h"
#include "th02/hardware/frmdelay.h"
#include "th05/snd/snd.h"
#include "th02/snd/measure.hpp"

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
			frame_delay(frames_if_no_bgm);
			return;
		}
	} while(measure_cur < measure);
}

#pragma codestring "\x00"

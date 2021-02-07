#pragma codeseg SHARED

extern "C" {
#include "platform.h"
#include "x86real.h"
#include "libs/kaja/kaja.h"
#include "th02/hardware/frmdelay.h"
#if (GAME >= 4)
	#include "th04/snd/snd.h"
#else
	#include "th03/snd/snd.h"
#endif
#include "th02/snd/measure.hpp"

void pascal snd_delay_until_measure(int measure, unsigned int frames_if_no_bgm)
{
	if(!snd_is_active()) {
		frame_delay(frames_if_no_bgm);
		return;
	}
	while(snd_get_song_measure() < measure) {
	}
}

}

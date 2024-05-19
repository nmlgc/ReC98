#pragma option -zCSHARED

#include "platform.h"
#include "x86real.h"
#include "th02/hardware/frmdelay.h"
#include "th02/snd/snd.h"
#include "th02/snd/measure.hpp"

void snd_delay_until_measure(int measure)
{
	if(!snd_active) {
		frame_delay(SND_FALLBACK_DELAY_FRAMES);
		return;
	}
	do {
		frame_delay(1);
	} while(snd_get_song_measure() < measure);
}

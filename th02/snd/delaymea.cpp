#pragma codeseg SHARED

extern "C" {
#include <dos.h>
#include "platform.h"
#include "libs/kaja/kaja.h"
#include "th02/hardware/frmdelay.h"
#include "th02/snd/snd.h"
#include "th02/snd/measure.hpp"

void snd_delay_until_measure(int measure)
{
	if(!snd_active) {
		frame_delay(100);
		return;
	}
	do {
		frame_delay(1);
	} while(snd_get_song_measure() < measure);
}

}

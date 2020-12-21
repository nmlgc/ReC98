#pragma codeseg SHARED

extern "C" {
#include <dos.h>
#include "platform.h"
#include "libs/kaja/kaja.h"
#include "th02/hardware/frmdelay.h"
#include "th02/snd/snd.h"

void snd_delay_until_measure(int measure)
{
	if(!snd_active) {
		frame_delay(100);
		return;
	}
	do {
		frame_delay(1);
		_AH = KAJA_GET_SONG_MEASURE;
		if(snd_midi_active != 1) {
			geninterrupt(PMD);
		} else {
			_DX = (MMD_TICKS_PER_QUARTER_NOTE * 4);	// yes, hardcoded to 4/4
			geninterrupt(MMD);
		}
	} while(_AX < measure);
}

}

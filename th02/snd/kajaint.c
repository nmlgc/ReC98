#pragma option -zCSHARED

#include "platform.h"
#include "x86real.h"
#include "libs/kaja/kaja.h"
#include "th02/snd/snd.h"

int16_t DEFCONV snd_kaja_interrupt(int16_t ax)
{
	if(snd_active) {
		_AX = ax;
		if(snd_midi_active != true) {
			geninterrupt(PMD);
		} else {
			geninterrupt(MMD);
		}
	}
	return _AX;
}

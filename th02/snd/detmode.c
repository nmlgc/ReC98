#pragma codeseg SHARED
#pragma option -k-

#include "platform.h"
#include "x86real.h"
#include "libs/kaja/kaja.h"
#include "th02/snd/snd.h"

bool16 snd_determine_mode(void)
{
	_AH = PMD_GET_DRIVER_VERSION;
	geninterrupt(PMD);
	_BX = false;
	if(_AL != 0xFF) {
		_BX++;
		snd_fm_possible = true;
	} else {
		_BL = snd_midi_active;
	}
	snd_active = _BL;
	return _BX;
}

#pragma codestring "\x90"

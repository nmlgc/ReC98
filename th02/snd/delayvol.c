#pragma option -zCSHARED

#include "x86real.h"
#include "th02/snd/snd.h"

void snd_delay_until_volume(uint8_t volume)
{
	while(1) {
		_AH = KAJA_GET_VOLUME;
		if(snd_midi_active != true) {
			geninterrupt(PMD);
		} else {
			geninterrupt(MMD);
		}
		_asm { cmp	al, volume; }
		_asm { jz 	end; }
	}
end:
}
#pragma codestring "\x90"

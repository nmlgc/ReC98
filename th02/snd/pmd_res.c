#pragma option -zCSHARED -k-

#include "platform.h"
#include "x86real.h"
#include "libs/kaja/kaja.h"
#include "th02/snd/snd.h"

bool16 snd_pmd_resident(void)
{
	snd_interrupt_if_midi = PMD;
	snd_midi_active = false;
	snd_fm_possible = false;
	snd_midi_possible = false;

	_ES = 0;
	__asm { les bx, dword ptr es:[PMD * 4] };
	if(kaja_isr_magic_matches(MK_FP(_ES, _BX), 'P', 'M', 'D')) {
		return true;
	}
	return false;
}
#pragma codestring "\x90"

#pragma option -zCSHARED -k-

#include "x86real.h"
#include "th04/snd/snd.h"

bool16 snd_pmd_resident(void)
{
	_AX = 0;
	snd_interrupt_if_midi = PMD;
	snd_midi_possible = _AX;
	snd_bgm_mode = _AX; // SND_BGM_OFF
	snd_se_mode = _AX; // SND_SE_OFF

	_ES = _AX;
	_asm { les bx, dword ptr es:[PMD * 4]; }
	if(kaja_isr_magic_matches(MK_FP(_ES, _BX), 'P', 'M', 'D')) {
		_AX++;
	}
	return _AX;
}

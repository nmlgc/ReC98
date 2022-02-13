#pragma option -WX -zCSHARED -k-

#include "platform.h"
#include "x86real.h"
#include "libs/kaja/kaja.h"
#include "th02/snd/snd.h"

bool16 snd_mmd_resident(void)
{
	_ES = 0;
	_asm { les bx, dword ptr es:[MMD * 4]; }
	if(kaja_isr_magic_matches(MK_FP(_ES, _BX), 'M', 'M', 'D')) {
		snd_interrupt_if_midi = MMD;
		#if (GAME <= 3)
			snd_midi_active = true;
		#endif
		snd_midi_possible = true;
		// Enforced by the -WX code generation. Just replace these two lines
		// with `return true`.
		_AX = true;
		_asm { retf; }
	}
	#if (GAME <= 3)
		snd_midi_possible = false;
	#endif
	return false;
}
#pragma codestring "\x90"

#pragma option -zCSHARED -k-

#include "platform.h"
#include "libs/kaja/kaja.h"
#include "th02/snd/snd.h"

bool16 snd_pmd_resident(void)
{
	snd_interrupt_if_midi = PMD;
	snd_midi_active = false;
	snd_fm_possible = false;
	snd_midi_possible = false;

	_ES = 0;
	__asm	les bx, dword ptr es:[PMD * 4];
	__asm	cmp byte ptr es:[bx+2], 'P';
	__asm	jnz nope;
	__asm	cmp byte ptr es:[bx+3], 'M';
	__asm	jnz nope;
	__asm	cmp byte ptr es:[bx+4], 'D';
	__asm	jnz nope;
	return true;
nope:
	return false;
}

#pragma codestring "\x90"

#pragma option -WX -zCSHARED -k-

#include "platform.h"
#include "libs/kaja/kaja.h"
#include "th02/snd/snd.h"

bool16 snd_mmd_resident(void)
{
	_ES = 0;
	__asm	les bx, dword ptr es:[MMD * 4];
	__asm	cmp byte ptr es:[bx+2], 'M';
	__asm	jnz nope;
	__asm	cmp byte ptr es:[bx+3], 'M';
	__asm	jnz nope;
	__asm	cmp byte ptr es:[bx+4], 'D';
	__asm	jnz nope;
	snd_interrupt_if_midi = MMD;
	snd_midi_active = true;
	snd_midi_possible = true;
	// Enforced by the -WX code generation. Just replace these two lines with
	// `return true`.
	_AX = true;
	__asm	retf;
nope:
	snd_midi_possible = false;
	return false;
}
#pragma codestring "\x90"

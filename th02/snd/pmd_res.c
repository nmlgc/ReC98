int snd_pmd_resident(void)
{
	snd_interrupt_if_midi = PMD;
	snd_midi_active = 0;
	snd_fm_possible = 0;
	snd_midi_possible = 0;

	_AX = 0;
	__asm	mov es, ax;
	__asm	les bx, dword ptr es:[PMD * 4];
	__asm	cmp byte ptr es:[bx+2], 'P';
	__asm	jnz nope;
	__asm	cmp byte ptr es:[bx+3], 'M';
	__asm	jnz nope;
	__asm	cmp byte ptr es:[bx+4], 'D';
	__asm	jnz nope;
	return 1;
nope:
	return 0;
}

#pragma codestring "\x90"

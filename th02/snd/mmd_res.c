int snd_mmd_resident(void)
{
	_AX = 0;
__asm	mov es, ax;
__asm	les bx, dword ptr es:[MMD * 4];
__asm	cmp byte ptr es:[bx+2], 'M';
__asm	jnz nope;
__asm	cmp byte ptr es:[bx+3], 'M';
__asm	jnz nope;
__asm	cmp byte ptr es:[bx+4], 'D';
__asm	jnz nope;
	snd_interrupt_if_midi = MMD;
	snd_midi_active = 1;
	snd_midi_possible = 1;
	return 1;
nope:
	snd_midi_possible = 0;
	return 0;
}

#pragma codestring "\x90"

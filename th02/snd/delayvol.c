void snd_delay_until_volume(char volume)
{
loop:
	_AH = KAJA_GET_VOLUME;
	if(snd_midi_active != 1) {
		geninterrupt(PMD);
	} else {
		geninterrupt(MMD);
	}
__asm	cmp al, volume
__asm	jz end
__asm	jmp loop
end:
}
#pragma codestring "\x90"

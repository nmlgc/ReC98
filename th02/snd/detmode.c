int snd_determine_mode(void)
{
	__asm	mov ah, PMD_GET_DRIVER_VERSION;
	__asm	int PMD;
	_BX = 0;
	if(_AL != 0xFF) {
		__asm	inc bx;
		snd_fm_possible = 1;
	} else {
		__asm	mov bl, snd_midi_active;
	}
		__asm	mov snd_active, bl;
	return _BX;
}

#pragma codestring "\x90"

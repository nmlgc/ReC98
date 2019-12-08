void snd_delay_until_measure(int measure)
{
	if(!snd_active) {
		frame_delay_2(100);
		return;
	}
	do {
		frame_delay_2(1);
		_AH = KAJA_GET_SONG_MEASURE;
		if(snd_midi_active != 1) {
			geninterrupt(PMD);
		} else {
			_DX = MMD_TICKS_PER_QUARTER_NOTE * 4;	// yes, hardcoded to 4/4
			geninterrupt(MMD);
		}
	} while(_AX < measure);
}

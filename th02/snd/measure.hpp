// Wrapper around KAJA_GET_SONG_MEASURE, using PMD or MMD depending on which
// driver is active.
static inline uint16_t snd_get_song_measure(void) {
	_AH = KAJA_GET_SONG_MEASURE;
	if(snd_bgm_is_fm()) {
		geninterrupt(PMD);
	} else {
		_DX = (MMD_TICKS_PER_QUARTER_NOTE * 4);	// yes, hardcoded to 4/4
		geninterrupt(MMD);
	}
	return _AX;
}

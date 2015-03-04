int snd_kaja_func(kaja_func_t ax)
{
	if(snd_active) {
		_AX = ax;
		if(snd_midi_active != 1) {
			geninterrupt(PMD);
		} else {
			geninterrupt(MMD);
		}
	}
	return _AX;
}

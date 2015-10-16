; enum BGM_MODE
SND_BGM_OFF = 0
SND_BGM_FM = 1
SND_BGM_MIDI = 2

public _snd_fm_possible
_snd_fm_possible	db ?
public _snd_midi_active
_snd_midi_active	db ?
public _snd_interrupt_if_midi
_snd_interrupt_if_midi db ? ; has no effect
public _snd_midi_possible
_snd_midi_possible db ?

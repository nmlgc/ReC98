; enum BGM_MODE
SND_BGM_OFF = 0
SND_BGM_FM = 1
SND_BGM_MIDI = 2

snd_fm_possible	db ?
snd_midi_active	db ?
snd_interrupt_if_midi db ? ; has no effect
snd_midi_possible db ?

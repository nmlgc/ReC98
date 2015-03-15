; enum BGM_MODE
SND_BGM_OFF = 0
SND_BGM_FM26 = 1
SND_BGM_FM86 = 2
SND_BGM_MIDI = 3 ; unsupported

; enum SE_MODE
SND_SE_OFF = 0
SND_SE_FM = 1
SND_SE_BEEP = 2

public _snd_se_mode
_snd_se_mode db SND_SE_OFF
public _snd_bgm_mode
_snd_bgm_mode db SND_BGM_OFF
public _snd_midi_possible
_snd_midi_possible db 0

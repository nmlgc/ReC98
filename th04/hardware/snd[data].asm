; enum BGM_MODE
SND_BGM_OFF = 0
SND_BGM_FM26 = 1
SND_BGM_FM86 = 2
SND_BGM_MIDI = 3 ; unsupported

; enum SE_MODE
SND_SE_OFF = 0
SND_SE_FM = 1
SND_SE_BEEP = 2

snd_se_mode db SND_SE_OFF
snd_bgm_mode db SND_BGM_OFF
snd_midi_possible db 0

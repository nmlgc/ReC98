public _snd_bgm_measure
_snd_bgm_measure	proc far
	push	bp
	mov	bp, sp
	cmp	_snd_bgm_mode, SND_BGM_OFF
	jnz	short @@BGM_is_active
	mov	ax, -1
	pop	bp
	retf

@@BGM_is_active:
	mov	ah, KAJA_GET_SONG_MEASURE
	cmp	_snd_bgm_mode, SND_BGM_MIDI
	jz	short @@MIDI_is_active
	int	PMD
	jmp	short @@ret

@@MIDI_is_active:
	mov	dx, MMD_TICKS_PER_QUARTER_NOTE * 4
	int	MMD

@@ret:
	pop	bp
	retf
_snd_bgm_measure	endp

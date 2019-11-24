public SND_DELAY_UNTIL_MEASURE
snd_delay_until_measure	proc far

@@frames_if_no_bgm	= word ptr  6
@@measure		= word ptr  8

	push	bp
	mov	bp, sp
if GAME eq 4
	cmp	_snd_bgm_mode, SND_BGM_OFF
else
	cmp	_snd_active, 0
endif
	jnz	short @@retry
	push	[bp+@@frames_if_no_bgm]
	nopcall	frame_delay
	pop	bp
	retf	4

@@retry:
	mov	ah, KAJA_GET_SONG_MEASURE
if GAME eq 4
	cmp	_snd_bgm_mode, SND_BGM_MIDI
else
	cmp	_snd_midi_active, 1
endif
	jz	short @@MIDI_is_active
	int	PMD
	jmp	short @@reached?

@@MIDI_is_active:
	mov	dx, MMD_TICKS_PER_QUARTER_NOTE * 4	; yes, hardcoded to 4/4
	int	MMD

@@reached?:
	cmp	ax, [bp+@@measure]
	jb	short @@retry
	pop	bp
	retf	4
snd_delay_until_measure	endp

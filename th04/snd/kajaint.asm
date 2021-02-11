public SND_KAJA_INTERRUPT
snd_kaja_interrupt proc
	arg @@ax:word

	push	bp
	mov	bp, sp
	cmp	_snd_bgm_mode, SND_BGM_OFF
	jz	short @@ret
	mov	ax, @@ax
	cmp	_snd_bgm_mode, SND_BGM_MIDI
	jz	short @@midi
	int	60h
	jmp	short @@ret

@@midi:
	int	61h

@@ret:
	pop	bp
	ret	2
snd_kaja_interrupt endp

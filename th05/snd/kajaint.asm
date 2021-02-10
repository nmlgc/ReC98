public SND_KAJA_INTERRUPT
snd_kaja_interrupt proc
	cmp	_snd_bgm_mode, SND_BGM_OFF
	jz	short @@ret

arg_bx	far, @ax:word

	mov	ax, @ax
	cmp	_snd_bgm_mode, SND_BGM_MIDI
	jz	short @@midi
	int	60h
	jmp	short @@ret

@@midi:
	int	61h

@@ret:
	ret_bx
snd_kaja_interrupt endp
	nop	; word alignment

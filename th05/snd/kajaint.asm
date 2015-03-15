; int __pascal snd_kaja_interrupt(int ax)
snd_kaja_interrupt	proc
@@ax	= word ptr (cPtrSize)

	cmp	_snd_bgm_mode, SND_BGM_OFF
	jz	short @@ret
	mov	bx, sp
	mov	ax, ss:[bx+@@ax]
	cmp	_snd_bgm_mode, SND_BGM_MIDI
	jz	short @@midi
	int	60h
	jmp	short @@ret

@@midi:
	int	61h

@@ret:
	ret	2
snd_kaja_interrupt	endp
	nop	; word alignment

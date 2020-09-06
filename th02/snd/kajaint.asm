proc_defconv snd_kaja_interrupt, SND_KAJA_INTERRUPT
@@ax	= word ptr (cPtrSize + 2)

	push	bp
	mov	bp, sp
	cmp	_snd_active, 0
	jz	short @@ret
	mov	ax, [bp+@@ax]
	cmp	_snd_midi_active, 1
	jz	short @@midi
	int	60h
	jmp	short @@ret

@@midi:
	int	61h

@@ret:
	pop	bp
if GAME ge 3
	ret	2
else
	ret
endif
endp_defconv

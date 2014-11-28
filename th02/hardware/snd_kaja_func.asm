; int __pascal snd_kaja_func(int ax)
snd_kaja_func	proc
@@ax	= word ptr (cPtrSize + 2)

	push	bp
	mov	bp, sp
	cmp	snd_active, 0
	jz	short @@ret
	mov	ax, [bp+@@ax]
	cmp	snd_midi_active, 1
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
snd_kaja_func	endp

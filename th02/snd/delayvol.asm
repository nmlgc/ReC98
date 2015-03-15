; int DEFCONV snd_delay_until_volume(__int8 volume)
proc_defconv snd_delay_until_volume
@@volume	= byte ptr (cPtrSize + 2)

	push	bp
	mov	bp, sp

@@loop:
	mov	ah, KAJA_GET_VOLUME
	cmp	_snd_midi_active, 1
	jz	short @@midi
	int	60h
	jmp	short @@reached?

@@midi:
	int	61h

@@reached?:
	cmp	al, [bp+@@volume]
	jz	short @@ret
	jmp	short @@loop

@@ret:
	pop	bp
	ret
endp_defconv
	nop	; word alignment

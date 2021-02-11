public _snd_delay_until_volume
_snd_delay_until_volume proc
	arg @@volume:byte

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
	cmp	al, @@volume
	jz	short @@ret
	jmp	short @@loop

@@ret:
	pop	bp
	ret
_snd_delay_until_volume endp
	nop	; word alignment

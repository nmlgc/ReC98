proc_defconv snd_load, SND_LOAD
	arg returns @@fn:ptr, @@func:word

	push	bp
	mov	bp, sp
	push	si
	push	ds
	mov	cx, SND_LOAD_FN_LEN
	xor	si, si

@@memcpy:
	les	bx, @@fn
	add	bx, si
	mov	al, es:[bx]
	mov	_snd_load_fn[si], al
	inc	si
	loop	@@memcpy
	mov	ax, @@func
	cmp	ax, SND_LOAD_SONG
	jnz	short @@load
	cmp	_snd_midi_active, 0
	jz	short @@load
	xor	bx, bx

@@strlen:
	inc	bx
	cmp	_snd_load_fn[bx], 0
	jnz	short @@strlen
	mov	_snd_load_fn[bx], 'm'
	mov	(_snd_load_fn+1)[bx], 'd'
	mov	(_snd_load_fn+2)[bx], 0

@@load:
	mov	dx, offset _snd_load_fn
	mov	ax, 3D00h
	int	21h
	mov	bx, ax
	mov	ax, @@func
	cmp	ax, SND_LOAD_SONG
	jnz	short @@PMD
	cmp	_snd_midi_active, 0
	jz	short @@PMD
	int	61h
	jmp	short @@read

@@PMD:
	int	60h

@@read:
	mov	ax, 3F00h
	mov	cx, 5000h
	int	21h
	pop	ds
	mov	ah, 3Eh
	int	21h
	pop	si
	pop	bp
	ret
endp_defconv

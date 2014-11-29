; Loads a song in .M format ([func] = SND_LOAD_SONG) or a sound effect bank in
; .EFC format ([func] = SND_LOAD_SE) into the respective work buffer of the
; sound driver. If MIDI is used, 'md' is appended to the file name.

; void __cdecl snd_load(const char *fn, int func)
snd_load	proc
@@fn	= DPTR_ (cPtrSize + 2)
@@func	= word ptr (cPtrSize + 2 + dPtrSize)

	push	bp
	mov	bp, sp
	push	si
	push	ds
	mov	cx, SND_LOAD_FN_LEN
	xor	si, si

@@memcpy:
	les	bx, [bp+@@fn]
	add	bx, si
	mov	al, es:[bx]
	mov	snd_load_fn[si], al
	inc	si
	loop	@@memcpy
	mov	ax, [bp+@@func]
	cmp	ax, SND_LOAD_SONG
	jnz	short @@load
	cmp	snd_midi_active, 0
	jz	short @@load
	xor	bx, bx

@@strlen:
	inc	bx
	cmp	snd_load_fn[bx], 0
	jnz	short @@strlen
	mov	snd_load_fn[bx], 'm'
	mov	(snd_load_fn+1)[bx], 'd'
	mov	(snd_load_fn+2)[bx], 0

@@load:
	mov	dx, offset snd_load_fn
	mov	ax, 3D00h
	int	21h
	mov	bx, ax
	mov	ax, [bp+@@func]
	cmp	ax, SND_LOAD_SONG
	jnz	short @@PMD
	cmp	snd_midi_active, 0
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
snd_load	endp

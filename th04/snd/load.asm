; Loads a song ([func] = SND_LOAD_SONG) or a sound effect bank ([func] =
; SND_LOAD_SE) into the respective work buffer of the sound driver. [fn] must
; not have any extension. Depending on snd_bgm_mode and snd_se_mode, the
; following file is loaded:
; • '[fn].m26' if SND_BGM_FM26
; • '[fn].m86' if SND_BGM_FM86
; • '[fn].mmd' if SND_BGM_MIDI
; • '[fn].efc' if SND_SE_FM
; • '[fn].efs' if SND_SE_BEEP (using master.lib's BGM driver)

; void __stdcall snd_load(int func, const char *fn)
snd_load	proc
@@func	= word ptr (cPtrSize + 2)
@@fn	= DPTR_ (cPtrSize + 2 + 2)

	push	bp
	mov	bp, sp
	push	si
	xor	si, si
	jmp	short @@memcpy_cond

@@memcpy_loop:
	les	bx, [bp+@@fn]
	add	bx, si
	mov	al, es:[bx]
	mov	_snd_load_fn[si], al
	inc	si

@@memcpy_cond:
	cmp	si, SND_LOAD_FN_LEN
	jl	short @@memcpy_loop
	xor	si, si

@@strlen:
	inc	si
	cmp	_snd_load_fn[si], 0
	jnz	short @@strlen
	mov	(_snd_load_fn+4)[si], 0
	mov	_snd_load_fn[si], '.'
	inc	si
	cmp	[bp+@@func], SND_LOAD_SE
	jnz	short @@song
	mov	_snd_load_fn[si], 'e'
	mov	(_snd_load_fn+1)[si], 'f'
	cmp	_snd_se_mode, SND_SE_OFF
	jz	@@ret
	cmp	_snd_se_mode, SND_SE_BEEP
	jnz	short @@FM_SE
	mov	(_snd_load_fn+2)[si], 's'
	call	bgm_read_sdata pascal, ds, offset _snd_load_fn
	jmp	@@ret

@@FM_SE:
	mov	(_snd_load_fn+2)[si], 'c'
	jmp	short @@open

@@song:
	cmp	_snd_bgm_mode, SND_BGM_OFF
	jz	short @@ret
	push	(KAJA_SONG_STOP shl 8)
	nopcall	snd_kaja_interrupt
	mov	al, _snd_bgm_mode
	mov	ah, 0
	shl	ax, 2
	mov	bx, ax
	les	bx, SND_LOAD_EXT[bx]
	mov	al, es:[bx]
	mov	_snd_load_fn[si], al
	mov	al, _snd_bgm_mode
	mov	ah, 0
	shl	ax, 2
	mov	bx, ax
	les	bx, SND_LOAD_EXT[bx]
	mov	al, es:[bx+1]
	mov	(_snd_load_fn+1)[si], al
	mov	al, _snd_bgm_mode
	mov	ah, 0
	shl	ax, 2
	mov	bx, ax
	les	bx, SND_LOAD_EXT[bx]
	mov	al, es:[bx+2]
	mov	(_snd_load_fn+2)[si], al

@@open:
	push	ds
	mov	dx, offset _snd_load_fn
	mov	ax, 3D00h
	int	21h
	mov	bx, ax
	mov	ax, [bp+@@func]
	cmp	ah, KAJA_GET_SONG_ADDRESS
	jnz	short @@PMD
	cmp	_snd_bgm_mode, SND_BGM_MIDI
	jnz	short @@PMD
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

@@ret:
	pop	si
	pop	bp
	ret	6
snd_load	endp

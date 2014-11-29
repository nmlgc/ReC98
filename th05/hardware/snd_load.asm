; Loads a song ([func] = SND_LOAD_SONG) or a sound effect bank ([func] =
; SND_LOAD_SE) into the respective work buffer of the sound driver. [fn] must
; not have any extension. Depending on snd_bgm_mode and snd_se_mode, the
; following file is loaded:
; • '[fn].m' if SND_BGM_FM26
; • '[fn].m2' if SND_BGM_FM86
; • '[fn].md' if SND_BGM_MIDI (yes, see this game's snd_load[data].asm)
; • '[fn].efc' if SND_SE_FM
; • '[fn].efs' if SND_SE_BEEP (using master.lib's BGM driver)
; Note that the TH05 version will infinitely loop if neither the file for the
; current snd_bgm_mode nor '[fn].m' exist.

; void __stdcall snd_load(int func, const char *fn)
snd_load	proc
@@func	= word ptr (cPtrSize + 2)
@@fn	= DPTR_ (cPtrSize + 2 + 2)

	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	dx, ds
	mov	es, dx
	assume es:dseg
	mov	di, offset snd_load_fn
	lds	si, [bp+@@fn]
	mov	bp, [bp+@@func]
	mov	cx, SND_LOAD_FN_LEN
	rep movsb
	mov	ds, dx
	mov	di, offset snd_load_fn
	dec	cx
	xor	ax, ax
	repne scasb
	dec	di
	mov	byte ptr [di], '.'
	inc	di
	cmp	bp, SND_LOAD_SE
	jnz	short @@song
	cmp	snd_se_mode, SND_SE_OFF
	jz	short @@ret
	xor	bx, bx
	cmp	snd_se_mode, SND_SE_BEEP
	jnz	short @@set_ext
	mov	dword ptr [di], 'sfe'
	call	bgm_finish
	call	bgm_init pascal, 2048
	call	bgm_read_sdata pascal, ds, offset snd_load_fn
	jmp	short @@ret

@@song:
	cmp	snd_bgm_mode, SND_BGM_OFF
	jz	short @@ret
	kajacall	KAJA_SONG_STOP
	movzx	bx, snd_bgm_mode
	shl	bx, 2

@@set_ext:
	mov	eax, dword ptr aSND_LOAD_EXT[bx]

@@open:
	mov	[di], eax
	mov	dx, offset snd_load_fn
	mov	ax, 3D00h
	int	21h
	jnb	short @@which_driver?
	cmp	ax, ENOFILE
	jnz	short @@ret
	mov	eax, dword ptr aSND_LOAD_EXT_FM26
	jmp	short @@open

@@which_driver?:
	mov	bx, ax
	mov	ax, bp
	cmp	ah, KAJA_GET_SONG_ADDRESS
	jnz	short @@PMD
	cmp	snd_bgm_mode, SND_BGM_MIDI
	jnz	short @@PMD
	int	61h
	jmp	short @@read

@@PMD:
	int	60h

@@read:
	mov	ax, 3F00h
	mov	cx, 0FFFFh
	int	21h
	mov	ah, 3Eh
	int	21h
	push	es
	pop	ds

@@ret:
	pop	di
	pop	si
	pop	bp
	ret	6
snd_load	endp

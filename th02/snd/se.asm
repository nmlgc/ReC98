; void snd_se_reset(void)
proc_defconv snd_se_reset
	mov	_snd_se_frame, 0
	mov	_snd_se_playing, -1
	ret
endp_defconv
	even

; void DEFCONV snd_se_play(unsigned char se)
retfunc macro
	if GAME ge 3
		ret 2
	else
		ret
	endif
endm
proc_defconv snd_se_play
@@se	= [bp+6]

	push	bp
	mov	bp, sp
	mov	dx, @@se
	cmp	_snd_fm_possible, 0
	jz	short @@ret
	cmp	_snd_se_playing, -1
	jnz	short @@priority?
	mov	_snd_se_playing, dl
	pop	bp
	retfunc

@@priority?:
	mov	al, _snd_se_playing
	mov	ah, 0
	mov	bx, ax
	mov	al, _snd_se_priorities[bx]
	mov	bx, dx
	cmp	al, _snd_se_priorities[bx]
	ja	short @@ret
	mov	_snd_se_playing, dl
	mov	_snd_se_frame, 0

@@ret:
	pop	bp
	retfunc
endp_defconv
	even

; void snd_se_update(void)
proc_defconv snd_se_update
	cmp	_snd_fm_possible, 0
	jz	short @@ret
	cmp	_snd_se_playing, -1
	jz	short @@ret
	cmp	_snd_se_frame, 0
	jnz	short @@unlock?
	mov	ah, PMD_SE_PLAY
	mov	al, _snd_se_playing
	int	60h

@@unlock?:
	inc	_snd_se_frame
	mov	al, _snd_se_playing
	mov	ah, 0
	mov	bx, ax
	mov	al, _snd_se_priority_frames[bx]
	cmp	al, _snd_se_frame
	jnb	short @@ret
	mov	_snd_se_frame, 0
	mov	_snd_se_playing, -1

@@ret:
	ret
endp_defconv
	even

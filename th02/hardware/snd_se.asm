; void snd_se_reset(void)
func _snd_se_reset
	mov	snd_se_frame, 0
	mov	snd_se_playing, -1
	ret
endfunc


; void DEFCONV snd_se_play(unsigned char se)
retfunc macro
	if GAME ge 3
		ret 2
	else
		ret
	endif
endm
func _snd_se_play
@@se	= [bp+6]

	push	bp
	mov	bp, sp
	mov	dx, @@se
	cmp	snd_fm_possible, 0
	jz	short @@ret
	cmp	snd_se_playing, -1
	jnz	short @@priority?
	mov	snd_se_playing, dl
	pop	bp
	retfunc

@@priority?:
	mov	al, snd_se_playing
	mov	ah, 0
	mov	bx, ax
	mov	al, snd_se_priorities[bx]
	mov	bx, dx
	cmp	al, snd_se_priorities[bx]
	ja	short @@ret
	mov	snd_se_playing, dl
	mov	snd_se_frame, 0

@@ret:
	pop	bp
	retfunc
endfunc


; void snd_se_update(void)
func _snd_se_update
	cmp	snd_fm_possible, 0
	jz	short @@ret
	cmp	snd_se_playing, -1
	jz	short @@ret
	cmp	snd_se_frame, 0
	jnz	short @@unlock?
	mov	ah, PMD_SE_PLAY
	mov	al, snd_se_playing
	int	60h

@@unlock?:
	inc	snd_se_frame
	mov	al, snd_se_playing
	mov	ah, 0
	mov	bx, ax
	mov	al, snd_se_priority_frames[bx]
	cmp	al, snd_se_frame
	jnb	short @@ret
	mov	snd_se_frame, 0
	mov	snd_se_playing, -1

@@ret:
	ret
endfunc

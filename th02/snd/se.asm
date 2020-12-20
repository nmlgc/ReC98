public _snd_se_reset
_snd_se_reset proc far
	mov	_snd_se_frame, 0
	mov	_snd_se_playing, -1
	ret
_snd_se_reset endp
	even

retfunc macro
	if GAME ge 3
		retf 2
	else
		retf
	endif
endm
proc_defconv snd_se_play, SND_SE_PLAY
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

public _snd_se_update
_snd_se_update proc far
	cmp	_snd_fm_possible, 0
	jz	short @@ret
	cmp	_snd_se_playing, -1
	jz	short @@ret
	cmp	_snd_se_frame, 0
	jnz	short @@unlock?
	mov	ah, PMD_SE_PLAY
	mov	al, _snd_se_playing
	int	PMD

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
_snd_se_update endp
	even

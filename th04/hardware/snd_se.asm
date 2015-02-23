; void snd_se_reset(void)
func snd_se_reset
	mov	_snd_se_frame, 0
	mov	_snd_se_playing, -1
	ret
endfunc


; void DEFCONV snd_se_play(unsigned char se)
func snd_se_play
	mov	bx, sp
	mov	dx, ss:[bx+4]
	cmp	_snd_se_mode, SND_SE_OFF
	jz	short @@ret
	cmp	_snd_se_playing, -1
	jnz	short @@priority?
	mov	_snd_se_playing, dl
	ret	2

@@priority?:
	mov	bl, _snd_se_playing
	xor	bh, bh
	mov	al, _snd_se_priorities[bx]
	mov	bx, dx
	cmp	al, _snd_se_priorities[bx]
	ja	short @@ret
	mov	_snd_se_playing, dl
	mov	_snd_se_frame, 0

@@ret:
	ret	2
endfunc


; void snd_se_update(void)
func snd_se_update
	cmp	_snd_se_mode, SND_SE_OFF
	jz	short @@ret
	cmp	_snd_se_playing, -1
	jz	short @@ret
	cmp	_snd_se_frame, 0
	jnz	short @@unlock?
	mov	al, _snd_se_playing
	cmp	_snd_se_mode, SND_SE_BEEP
	jz	short @@beep
	mov	ah, PMD_SE_PLAY
	int	60h
	jmp	short @@unlock?

@@beep:
	xor	ah, ah
	push	ax
	call	bgm_sound

@@unlock?:
	inc	_snd_se_frame
	mov	bl, _snd_se_playing
	xor	bh, bh
	mov	al, _snd_se_priority_frames[bx]
	cmp	al, _snd_se_frame
	jnb	short @@ret
	mov	_snd_se_frame, 0
	mov	_snd_se_playing, -1

@@ret:
	ret
endfunc

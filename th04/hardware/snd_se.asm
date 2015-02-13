; void snd_se_reset(void)
func snd_se_reset
	mov	snd_se_frame, 0
	mov	snd_se_playing, -1
	ret
endfunc


; void DEFCONV snd_se_play(unsigned char se)
func snd_se_play
	mov	bx, sp
	mov	dx, ss:[bx+4]
	cmp	snd_se_mode, SND_SE_OFF
	jz	short @@ret
	cmp	snd_se_playing, -1
	jnz	short @@priority?
	mov	snd_se_playing, dl
	ret	2

@@priority?:
	mov	bl, snd_se_playing
	xor	bh, bh
	mov	al, snd_se_priorities[bx]
	mov	bx, dx
	cmp	al, snd_se_priorities[bx]
	ja	short @@ret
	mov	snd_se_playing, dl
	mov	snd_se_frame, 0

@@ret:
	ret	2
endfunc


; void snd_se_update(void)
func snd_se_update
	cmp	snd_se_mode, SND_SE_OFF
	jz	short @@ret
	cmp	snd_se_playing, -1
	jz	short @@ret
	cmp	snd_se_frame, 0
	jnz	short @@unlock?
	mov	al, snd_se_playing
	cmp	snd_se_mode, SND_SE_BEEP
	jz	short @@beep
	mov	ah, PMD_SE_PLAY
	int	60h
	jmp	short @@unlock?

@@beep:
	xor	ah, ah
	push	ax
	call	bgm_sound

@@unlock?:
	inc	snd_se_frame
	mov	bl, snd_se_playing
	xor	bh, bh
	mov	al, snd_se_priority_frames[bx]
	cmp	al, snd_se_frame
	jnb	short @@ret
	mov	snd_se_frame, 0
	mov	snd_se_playing, -1

@@ret:
	ret
endfunc

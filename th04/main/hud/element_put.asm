HUD_HP_CAPTION_TRAM_Y = 8
HUD_HP_BAR_TRAM_Y = 9

public @HUD_HP_PUT$QI
@hud_hp_put$qi proc far

@@bar_colors	= word ptr -10h
@@blank	= word ptr -0Ah

@@bar_value	= word ptr  6

	push	bp
	mov	bp, sp
	sub	sp, 10h
	push	si
	mov	si, [bp+@@bar_value]
	mov	ax, word ptr _gHUD_HP_BLANK+0
	mov	word ptr [bp+@@blank], ax
	mov	ax, word ptr _gHUD_HP_BLANK+2
	mov	word ptr [bp+@@blank+2], ax
	mov	ax, word ptr _gHUD_HP_BLANK+4
	mov	word ptr [bp+@@blank+4], ax
	mov	ax, word ptr _gHUD_HP_BLANK+6
	mov	word ptr [bp+@@blank+6], ax
	mov	al, byte ptr _gHUD_HP_BLANK+8
	mov	byte ptr [bp+@@blank+8], al

	mov	ax, word ptr _HUD_HP_COLORS
	mov	word ptr [bp+@@bar_colors+0], ax
	mov	ax, word ptr _HUD_HP_COLORS+2
	mov	word ptr [bp+@@bar_colors+2], ax
	mov	al, byte ptr _HUD_HP_COLORS+4
	mov	byte ptr [bp+@@bar_colors+4], al
	or	si, si
	jz	short @@no_bar
	call	gaiji_putsa pascal, ((HUD_LEFT + 5) shl 16) + HUD_HP_CAPTION_TRAM_Y, ds, offset gsENEMY, TX_YELLOW
	push	HUD_HP_BAR_TRAM_Y
	push	si
	mov	ax, si
	mov	bx, (BAR_MAX / (HUD_HP_COLOR_COUNT - 1))
	cwd
	idiv	bx
	lea	dx, [bp+@@bar_colors]
	add	ax, dx
	mov	bx, ax
	mov	al, ss:[bx]
	mov	ah, 0
	push	ax
if GAME eq 4
	nop
endif
	call	hud_bar_put
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@no_bar:
	push	((HUD_LEFT + 5) shl 16) + HUD_HP_CAPTION_TRAM_Y
	push	ss
	lea	ax, [bp+@@blank][5]
	push	ax
	push	TX_WHITE
	call	gaiji_putsa
	push	(HUD_LEFT shl 16) + HUD_HP_BAR_TRAM_Y
	push	ss
	lea	ax, [bp+@@blank]
	push	ax
	push	TX_WHITE
	call	gaiji_putsa

@@ret:
	pop	si
	leave
	retf	2
@hud_hp_put$qi endp

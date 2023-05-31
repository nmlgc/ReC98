HUD_CONTINUES_LEFT = HUD_LEFT + ((SCORE_DIGITS - 1) * 2)

; Only prints the seven score digits, in contrast to the TH04/TH05 version!

public @HUD_SCORE_PUT$QUIL
@hud_score_put$quil proc near
@@result 	=  word ptr [bp-4]
@@digit 	=  word ptr [bp-2]
@@value 	= dword	ptr [bp+4]
@@y     	= word ptr  [bp+8]

	push	bp
	mov	bp, sp
	sub	sp, 4
	push	si
	push	di
	mov	si, offset _SEVEN_DIGIT_POWERS_OF_10
	mov	di, HUD_LEFT
	jmp	short @@more_digits?

@@put:
	mov	eax, @@value
	cdq
	idiv	dword ptr [si]
	mov	@@result, ax
	movsx	eax, @@result
	imul	eax, [si]
	sub	@@value, eax
	add	si, 4
	mov	ax, @@result
	add	ax, GB_DIGITS
	mov	@@digit, ax
	call	gaiji_putca pascal, di, @@y, ax, TX_WHITE
	add	di, 2

@@more_digits?:
	cmp	di, HUD_CONTINUES_LEFT
	jl	short @@put
	pop	di
	pop	si
	leave
	retn	6
@hud_score_put$quil endp


; void pascal near hud_continues_put(utram_y_t y, int continues_used);
public HUD_CONTINUES_PUT
hud_continues_put	proc near

@@continues_displayed = word ptr [bp-2]
@@continues_used = word ptr [bp+4]
@@y	= word ptr [bp+6]

	push	bp
	mov	bp, sp
	sub	sp, 2
	push	si
	mov	si, @@continues_used
	cmp	si, 10
	jl	short @@put
	mov	si, 9

@@put:
	lea	ax, [si+GB_DIGITS]
	mov	@@continues_displayed, ax
	call	gaiji_putca pascal, HUD_CONTINUES_LEFT, @@y, ax, TX_WHITE
	pop	si
	leave
	retn	4
hud_continues_put	endp

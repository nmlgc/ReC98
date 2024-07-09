; Prints [val] using the bold gaiji font, right-aligned at ([left+5], [y]),
; with the given attribute.
; void pascal far hud_int_put(
; 	utram_x_t left, utram_y_t y, unsigned int val, tram_atrb2 atrb
; );
public HUD_INT_PUT
hud_int_put	proc far

@@atrb		= word ptr  6
@@val		= word ptr  8

	push	bp
	mov	bp, sp
	push	di
; Avoid LEA being turned into MOV for immediate addresses
pushstate
nosmart
	lea	di, _hud_gaiji_row + (SCORE_DIGITS - 5)
	movzx	edx, [bp+@@val]
	lea	bx, _SEVEN_DIGIT_POWERS_OF_10 + (2 * 4)
popstate
	mov	ax, [bp+@@atrb]
	mov	cx, 4
	jmp	short hud_digits_put
hud_int_put	endp
	nop


public @HUD_POINTS_PUT$QUIUIUL
@hud_points_put$quiuiul proc far

@@points	= dword	ptr  6
@@y     	= word ptr  0Ah
@@left  	= word ptr  0Ch

	push	bp
	mov	bp, sp
	push	di
	mov	edx, [bp+@@points]
	mov	di, offset _hud_gaiji_row
	mov	ax, TX_WHITE
	mov	_hud_gaiji_row[SCORE_DIGITS - 1], gb_0_	; ("continues used" digit)
	mov	bx, offset _SEVEN_DIGIT_POWERS_OF_10
	mov	cx, SCORE_DIGITS - 2

hud_digits_put:
	push	[bp+@@left]
	push	[bp+@@y]
	push	ds
	push	di
	push	ax
	mov	ax, ds
	mov	es, ax

@@digit_loop:
	mov	eax, edx
	xor	edx, edx
	div	dword ptr [bx]
	or	ch, al
	jz	short @@omit_leading_zeroes
	add	al, GB_DIGITS
	jmp	short @@digit_next
; ---------------------------------------------------------------------------

@@omit_leading_zeroes:
	mov	al, g_EMPTY

@@digit_next:
	stosb
	add	bx, 4
	dec	cl
	jnz	short @@digit_loop
	add	dl, gb_0_	; (ones)
	mov	[di], dl
	call	gaiji_putsa
	pop	di
	pop	bp
	retf	8
@hud_points_put$quiuiul endp

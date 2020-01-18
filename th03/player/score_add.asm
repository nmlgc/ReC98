public SCORE_ADD
score_add	proc far

@@pid   	= byte ptr  6
@@points	= word ptr  8
@@bcd_p equ bx
@@po10_p equ si
@@score_p equ si

	push	bp
	mov	bp, sp
	push	si
	mov	@@bcd_p, offset _temp_lebcd

	; Since the delta can have at most 5 digits, we only have to work on the
	; range from _temp_lebcd[4] (highest) to _temp_lebcd[0] (lowest).
	mov	word ptr [@@bcd_p+6], 0
	mov	byte ptr [@@bcd_p+5], 0

	mov	@@po10_p, offset _FIVE_DIGIT_POWERS_OF_10
	; 4 divisions, the units place doesn't need a separate one.
	add	@@bcd_p, 4
	mov	cx, [bp+@@points]

@@points_to_bcd:
	mov	ax, cx
	xor	dx, dx
	div	word ptr [@@po10_p]
	mov	cx, dx
	mov	[@@bcd_p], al
	dec	@@bcd_p
	add	si, word
	cmp	word ptr [@@po10_p], 1
	ja	short @@points_to_bcd
	mov	[@@bcd_p], cl
	mov	@@score_p, offset _score_lebcd
	mov	ch, [bp+@@pid]
	or	ch, ch
	jz	short @@p1
	add	@@score_p, SCORE_DIGITS

@@p1:
	; The last digit doesn't need special BCD treatment
	mov	cx, SCORE_DIGITS - 1
	xor	ax, ax

@@add_next_digit_to_score:
	mov	al, [@@bcd_p]
	add	al, [@@score_p]
	aaa
	mov	[@@score_p], al
	inc	@@bcd_p
	inc	@@score_p
	add	[@@score_p], ah
	mov	ah, 0
	loop	@@add_next_digit_to_score
	mov	al, [@@bcd_p]
	add	[@@score_p], al
	pop	si
	pop	bp
	retf	4
score_add	endp

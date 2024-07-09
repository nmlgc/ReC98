public POINTNUM_DIGITS_SET
pointnum_digits_set	proc near

@@points    	= word ptr  4
@@last_digit	= word ptr  6

@@bp equ <bp>
@@ret equ <bp>

	push	bp
	mov	@@bp, sp
	mov	dx, ss:[@@bp+@@points]
	mov	bx, ss:[@@bp+@@last_digit]
	push	si
	xor	@@ret, @@ret
	mov	si, offset _FIVE_DIGIT_POWERS_OF_10 + ((5 - POINTNUM_DIGITS) * word)
	mov	cx, (POINTNUM_DIGITS - 1)

@@loop:
	mov	ax, dx
	xor	dx, dx
	div	word ptr [si]
	mov	[bx], al
	or	al, al
	jz	short @@next
	or	@@ret, @@ret
	jnz	short @@next
	mov	@@ret, cx

@@next:
	dec	bx
	add	si, word
	loop	@@loop
	mov	[bx], dl

	; +1 for the last digit written in the instruction above, +1 for the
	; trailing 0.
	add	bp, 2

	shl	bp, 3	; * NUMERAL_W
	mov	ax, bp
	pop	si
	pop	bp
	retn	4
pointnum_digits_set	endp
	nop

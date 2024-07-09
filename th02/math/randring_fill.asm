public @randring_fill$qv
@randring_fill$qv proc near
	push	bp
	mov	bp, sp
	push	si
	xor	si, si

@@loop:
	call	IRand
	mov	_randring[si], al
	inc	si
	cmp	si, RANDRING_SIZE
	jl	short @@loop
	pop	si
	pop	bp
	ret
@randring_fill$qv endp

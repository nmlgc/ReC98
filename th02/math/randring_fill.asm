; void randring_fill(void)
public _randring_fill
_randring_fill	proc near
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
_randring_fill	endp

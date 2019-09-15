; void pascal near randring_fill(void);
public RANDRING_FILL
randring_fill	proc near
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
randring_fill	endp

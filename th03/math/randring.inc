RANDRING_NEXT_DEF_NOMOD macro instance, dist
	; void pascal randring_next16(void);
	public RANDRING&instance&_NEXT16
	randring&instance&_next16	proc dist
		xor	bh, bh
		mov	bl, _randring_p
		add	bx, offset _randring
		inc	_randring_p
		mov	ax, [bx]
		ret
	randring&instance&_next16	endp
		nop

	; void pascal randring_next16_and(unsigned short mask);
	public RANDRING&instance&_NEXT16_AND
	randring&instance&_next16_and	proc dist
	arg @@mask:word

		push	bp
		mov	bp, sp
		xor	bh, bh
		mov	bl, _randring_p
		add	bx, offset _randring
		inc	_randring_p
		mov	ax, [bx]
		and	ax, @@mask
		pop	bp
		ret	2
	randring&instance&_next16_and	endp
endm

RANDRING_NEXT_DEF macro instance, dist
	RANDRING_NEXT_DEF_NOMOD instance, dist

	; void randring_next16_mod(unsigned short n)
	public RANDRING&instance&_NEXT16_MOD
	randring&instance&_next16_mod	proc dist
	arg @@n:word

		push	bp
		mov	bp, sp
		xor	bh, bh
		mov	bl, _randring_p
		add	bx, offset _randring
		inc	_randring_p
		mov	ax, [bx]
		xor	dx, dx
		div	@@n
		mov	ax, dx
		pop	bp
		ret	2
	randring&instance&_next16_mod	endp
endm

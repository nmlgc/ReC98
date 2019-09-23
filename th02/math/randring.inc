RANDRING_NEXT_DEF macro instance
	; void pascal near randring_next8(void);
	public RANDRING&instance&_NEXT8
	randring&instance&_next8	proc near
		mov	bl, _randring_p
		inc	_randring_p
		mov	bh, 0
		mov	al, _randring[bx]
		ret
	randring&instance&_next8	endp

	; void pascal near randring_next8_and(unsigned char mask);
	public RANDRING&instance&_NEXT8_AND
	randring&instance&_next8_and	proc near
	arg @@mask:byte

		push	bp
		mov	bp, sp
		mov	bl, _randring_p
		inc	_randring_p
		mov	bh, 0
		mov	al, _randring[bx]
		and	al, @@mask
		pop	bp
		ret	2
	randring&instance&_next8_and	endp

	; void pascal near randring_next16(void);
	public RANDRING&instance&_NEXT16
	randring&instance&_next16	proc near
		mov	bl, _randring_p
		inc	_randring_p
		mov	bh, 0
		mov	ax, word ptr _randring[bx]
		ret
	randring&instance&_next16	endp
endm

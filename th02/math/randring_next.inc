RANDRING_NEXT_DEF macro instance
	; void randring_next8(void)
	public _randring&instance&_next8
	_randring&instance&_next8	proc near
		mov	bl, _randring_p
		inc	_randring_p
		mov	bh, 0
		mov	al, _randring[bx]
		ret
	_randring&instance&_next8	endp

	; void randring_next8_and(unsigned char mask)
	public _randring&instance&_next8_and
	_randring&instance&_next8_and	proc near
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
	_randring&instance&_next8_and	endp

	; void randring_next16(void)
	public _randring&instance&_next16
	_randring&instance&_next16	proc near
		mov	bl, _randring_p
		inc	_randring_p
		mov	bh, 0
		mov	ax, word ptr _randring[bx]
		ret
	_randring&instance&_next16	endp
endm

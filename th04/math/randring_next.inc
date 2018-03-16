RANDRING_NEXT_DEF macro instance
	; void randring_next16(void)
	public _randring&instance&_next16
	_randring&instance&_next16	proc near
		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
		ret
	_randring&instance&_next16	endp
		nop

	; void randring_next16_and(unsigned char mask)
	public _randring&instance&_next16_and
	_randring&instance&_next16_and	proc near
	arg @@mask:byte

		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
		mov	bx, sp
		and	ax, ss:[bx+2]
		ret	2
	_randring&instance&_next16_and	endp
		nop

	; void randring_next16_mod(unsigned short n)
	public _randring&instance&_next16_mod
	_randring&instance&_next16_mod	proc near
	arg @@n:word

		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
		xor	dx, dx
		mov	bx, sp
		div	word ptr ss:[bx+2]
		mov	ax, dx
		ret	2
	_randring&instance&_next16_mod	endp
endm

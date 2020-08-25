RANDRING_NEXT_DEF macro instance
	public RANDRING&instance&_NEXT16
	randring&instance&_next16	proc near
		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
		ret
	randring&instance&_next16	endp
		nop

	public RANDRING&instance&_NEXT16_AND
	randring&instance&_next16_and	proc near
	arg @@mask:byte

		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
		mov	bx, sp
		and	ax, ss:[bx+2]
		ret	2
	randring&instance&_next16_and	endp
		nop

	public RANDRING&instance&_NEXT16_MOD
	randring&instance&_next16_mod	proc near
	arg @@n:word

		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
		xor	dx, dx
		mov	bx, sp
		div	word ptr ss:[bx+2]
		mov	ax, dx
		ret	2
	randring&instance&_next16_mod	endp
endm

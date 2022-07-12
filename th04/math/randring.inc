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
	randring&instance&_next16_and proc near
		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
	arg_bx near, @mask:byte
		and	ax, @mask
		ret_bx
	randring&instance&_next16_and endp
		nop

	public RANDRING&instance&_NEXT16_MOD
	randring&instance&_next16_mod proc near
		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
		xor	dx, dx
	arg_bx near, @n:word
		div	word ptr @mask
		mov	ax, dx
		ret_bx
	randring&instance&_next16_mod endp
endm

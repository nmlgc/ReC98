RANDRING_NEXT_DEF macro instance
	public @randring&instance&_next16$qv
	@randring&instance&_next16$qv proc near
		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
		ret
	@randring&instance&_next16$qv endp
		nop

	public @RANDRING&INSTANCE&_NEXT16_AND$QUI
	@randring&instance&_next16_and$qui proc near
		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
	arg_bx near, @mask:byte
		and	ax, @mask
		ret_bx
	@randring&instance&_next16_and$qui endp
		nop

	public @RANDRING&INSTANCE&_NEXT16_MOD$QUI
	@randring&instance&_next16_mod$qui proc near
		mov	bx, _randring_p
		mov	ax, word ptr _randring[bx]
		inc	byte ptr _randring_p
		xor	dx, dx
	arg_bx near, @n:word
		div	word ptr @mask
		mov	ax, dx
		ret_bx
	@randring&instance&_next16_mod$qui endp
endm

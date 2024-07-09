RANDRING_NEXT_DEF macro instance
	public @randring&instance&_next8$qv
	@randring&instance&_next8$qv proc near
		mov	bl, _randring_p
		inc	_randring_p
		mov	bh, 0
		mov	al, _randring[bx]
		ret
	@randring&instance&_next8$qv endp

	public @RANDRING&instance&_NEXT8_AND$QUC
	@randring&instance&_next8_and$quc proc near
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
	@randring&instance&_next8_and$quc endp

	public @randring&instance&_next16$qv
	@randring&instance&_next16$qv proc near
		mov	bl, _randring_p
		inc	_randring_p
		mov	bh, 0
		mov	ax, word ptr _randring[bx]
		ret
	@randring&instance&_next16$qv endp
endm

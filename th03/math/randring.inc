RANDRING_NEXT_DEF_NOMOD macro instance, dist
	public @randring&instance&_next16$qv
	@randring&instance&_next16$qv proc dist
		xor	bh, bh
		mov	bl, _randring_p
		add	bx, offset _randring
		inc	_randring_p
		mov	ax, [bx]
		ret
	@randring&instance&_next16$qv endp
		nop

	public @RANDRING&instance&_NEXT16_AND$QUI
	@randring&instance&_next16_and$qui proc dist
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
	@randring&instance&_next16_and$qui endp
endm

RANDRING_NEXT_DEF macro instance, dist
	RANDRING_NEXT_DEF_NOMOD instance, dist

	public @RANDRING&INSTANCE&_NEXT16_MOD$QUI
	@randring&instance&_next16_mod$qui proc dist
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
	@randring&instance&_next16_mod$qui endp
endm

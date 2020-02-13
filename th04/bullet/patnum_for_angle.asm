public BULLET_PATNUM_FOR_ANGLE
bullet_patnum_for_angle	proc near

@@angle		= byte ptr  4

	push	bp
	mov	bp, sp
	mov	al, [bp+@@angle]
	mov	ah, 0
	add	ax, 3
	and	ax, 7Fh
	mov	bx, 8
	cwd
	idiv	bx
	pop	bp
	retn	2
bullet_patnum_for_angle	endp

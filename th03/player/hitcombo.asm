public HITCOMBO_COMMIT
hitcombo_commit	proc near

@@bonus		= word ptr  4
@@slot		= byte ptr  6
@@pid		= byte ptr  8

	push	bp
	mov	bp, sp
	mov	al, [bp+@@pid]
	mov	ah, 0
	shl	ax, 4
	mov	dl, [bp+@@slot]
	mov	dh, 0
	add	ax, dx
	mov	bx, ax
	mov	al, _hitcombo_ring[bx]
	push	ax
	push	word ptr [bp+@@pid]
	push	[bp+@@bonus]
	nopcall	combo_add
	pop	bp
	retn	6
hitcombo_commit	endp

public _collmap_reset
_collmap_reset proc near
	push	di
	mov	ax, ds
	mov	es, ax
	mov	di, offset _collmap
	mov	cx, ((COLLMAP_SIZE * PLAYER_COUNT) / dword)
	xor	eax, eax
	rep stosd
	pop	di
	retn
_collmap_reset endp
	even

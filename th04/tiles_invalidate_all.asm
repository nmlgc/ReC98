public TILES_INVALIDATE_RESET, TILES_INVALIDATE_ALL

; void pascal near tiles_invalidate_reset(void);
tiles_invalidate_reset	proc near
	push	di
	mov	ax, ds
	mov	es, ax
	assume es:_DATA
	mov	di, offset _halftiles_dirty
	xor	eax, eax
	mov	cx, (TILES_MEMORY_X * TILE_FLAGS_Y) / 4
	rep stosd
	pop	di
	retn
tiles_invalidate_reset	endp
	nop


; void pascal near tiles_invalidate_all(void);
tiles_invalidate_all	proc near
	push	di
	mov	ax, ds
	mov	es, ax
	mov	di, offset _halftiles_dirty
	mov	eax, 01010101h
	mov	cx, (TILES_MEMORY_X * TILE_FLAGS_Y) / 4
	rep stosd
	pop	di
	retn
tiles_invalidate_all	endp

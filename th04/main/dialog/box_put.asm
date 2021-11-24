public DIALOG_BOX_PUT
dialog_box_put	proc near

@@tile		= word ptr  4
@@top		= word ptr  6
@@left		= word ptr  8

	push	bp
	mov	bp, sp
	push	di
	call	grcg_setcolor pascal, (GC_RMW shl 16) + 1
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	mov	ax, [bp+@@left]
	mov	dx, [bp+@@top]
	shr	ax, 3
	shl	dx, 6
	add	ax, dx
	shr	dx, 2
	add	ax, dx
	mov	di, ax
	mov	bx, [bp+@@tile]
	shl	bx, 3
	mov	dx, DIALOG_BOX_H

@@row_loop:
	mov	cx, (DIALOG_BOX_VRAM_W / 2)
	mov	ax, _DIALOG_BOX_TILES[bx]
	rep stosw
	add	bx, DIALOG_BOX_TILE_VRAM_W
	test	bx, ((DIALOG_BOX_TILE_H * DIALOG_BOX_TILE_VRAM_W) - 1)
	jnz	short @@more_rows?
	sub	bx, (DIALOG_BOX_TILE_H * DIALOG_BOX_TILE_VRAM_W)

@@more_rows?:
	add	di, (ROW_SIZE - DIALOG_BOX_VRAM_W)
	dec	dx
	jnz	short @@row_loop
	GRCG_OFF_CLOBBERING dx
	pop	di
	pop	bp
	retn	6
dialog_box_put	endp

; void pascal near tiles_redraw_invalidated(void);
public TILES_REDRAW_INVALIDATED
tiles_redraw_invalidated	proc near
	push	si
	push	di
	call	egc_start_copy_inlined_noframe
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	mov	bx, offset _halftiles_dirty[TILES_MEMORY_X * (TILE_FLAGS_Y - 1)]
	mov	di, ((RES_Y - TILE_FLAG_H) * ROW_SIZE) + PLAYFIELD_VRAM_X
	mov	dh, TILE_FLAGS_Y
	mov	si, TILES_MEMORY_X * (TILES_Y - 1) * 2

@@start_row:
	mov	dl, TILES_X

@@dirty?:
	cmp	byte ptr [bx], 0
	jz	short @@next_tile_in_row
	push	si
	mov	byte ptr [bx], 0
	mov	si, _tile_ring[si]
	test	dh, 1
	jnz	short @@redraw
	add	si, TILE_FLAG_H * ROW_SIZE

@@redraw:
	mov	cx, TILE_FLAG_H

@@blit_tile_redraw_lines:
	mov	ax, es:[si]
	mov	es:[di], ax
	add	si, ROW_SIZE
	add	di, ROW_SIZE
	loop	@@blit_tile_redraw_lines
	sub	di, TILE_FLAG_H * ROW_SIZE
	pop	si

@@next_tile_in_row:
	add	di, 2
	add	si, 2
	inc	bx
	dec	dl
	jnz	short @@dirty?
	test	dh, 1
	jnz	short @@previous_row
	add	si, (TILES_MEMORY_X * 2)

@@previous_row:
	sub	si, (TILES_MEMORY_X * 2) + (TILES_X * 2)
	dec	dh
	sub	bx, TILES_X + TILES_MEMORY_X
	sub	di, (TILES_X * 2) + (TILE_FLAG_H * ROW_SIZE)
	jge	short @@start_row
	call	egc_off
	pop	di
	pop	si
	retn
tiles_redraw_invalidated	endp

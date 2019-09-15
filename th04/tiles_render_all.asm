; Blits all tiles in the ring buffer to the playfield in VRAM.

; void pascal near tiles_render_all(void);
public TILES_RENDER_ALL
tiles_render_all	proc near
	push	si
	push	di
	call	egc_start_copy_inlined_noframe
	mov	di, ((RES_Y - TILE_H) * ROW_SIZE) + PLAYFIELD_VRAM_X
	mov	bx, offset _tile_ring[TILES_MEMORY_X * (TILES_Y - 1) * 2]
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing

@@start_row:
	mov	dl, TILES_X

@@next_tile_in_row:
	mov	si, [bx]
	mov	cx, TILE_H
	nop

@@blit_tile_lines:
	mov	ax, es:[si]
	mov	es:[di], ax
	add	si, ROW_SIZE
	add	di, ROW_SIZE
	loop	@@blit_tile_lines
	sub	di, (TILE_H * ROW_SIZE) - TILE_VRAM_W
	add	bx, 2
	dec	dl
	jnz	short @@next_tile_in_row
	sub	bx, (TILES_MEMORY_X + TILES_X) * 2
	sub	di, (TILE_H * ROW_SIZE) + (TILE_VRAM_W * TILES_X)
	jge	short @@start_row
	call	egc_off
	pop	di
	pop	si
	retn
tiles_render_all	endp


; void pascal near egc_start_copy_inlined_noframe(void);
public EGC_START_COPY_INLINED_NOFRAME
egc_start_copy_inlined_noframe	proc near
		EGC_START_COPY_INLINED
		retn
egc_start_copy_inlined_noframe	endp
		nop

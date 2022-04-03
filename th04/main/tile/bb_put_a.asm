public @TILES_BB_PUT_RAW$QI
@tiles_bb_put_raw$qi proc near

@@top           	= word ptr -6
@@left          	= word ptr -4
@@row_tiles_left	= byte ptr -2
@@bb_shiftreg   	= byte ptr -1
@@cel           	= word ptr  4

@@bb_seg	equ <fs>
@@bb_off	equ <di>

	enter	6, 0
	push	di
	push	GC_TDW
	mov	al, _tiles_bb_col
	mov	ah, 0
	call	grcg_setcolor pascal, ax
	mov	ax, _tiles_bb_seg
	mov	@@bb_seg, ax
	mov	@@bb_off, [bp+@@cel]
	shl	@@bb_off, 7
	mov	[bp+@@top], PLAYFIELD_TOP

@@row_loop:
	mov	[bp+@@left], PLAYFIELD_LEFT
	mov	[bp+@@row_tiles_left], TILES_X

@@bb_byte_loop:
	mov	al, @@bb_seg:[@@bb_off]
	mov	[bp+@@bb_shiftreg], al

@@next_tile_in_row:
	test	[bp+@@bb_shiftreg], 80h
	jz	short @@skip_tile
	mov	ax, [bp+@@left]
	mov	dx, [bp+@@top]
	if (GAME eq 5)
		cmp	_scroll_active, 0
		jz	short @@roll?
	endif
	add	dx, _scroll_line

@@roll?:
	cmp	dx, RES_Y
	jl	short @@put
	sub	dx, RES_Y

@@put:
	call	@grcg_tile_bb_put_8

@@skip_tile:
	shl	[bp+@@bb_shiftreg], 1
	add	[bp+@@left], TILE_W
	dec	[bp+@@row_tiles_left]
	jz	short @@row_next
	test	[bp+@@row_tiles_left], 7
	jnz	short @@next_tile_in_row
	inc	@@bb_off
	jmp	short @@bb_byte_loop
; ---------------------------------------------------------------------------

@@row_next:
	add	@@bb_off, 2 ; 1 since we skipped the INC, 1 to skip the 8 unused tiles
	add	[bp+@@top], TILE_H
	cmp	[bp+@@top], PLAYFIELD_BOTTOM
	jb	short @@row_loop
	GRCG_OFF_CLOBBERING dx
	pop	di
	leave
	retn	2
@tiles_bb_put_raw$qi endp
	even

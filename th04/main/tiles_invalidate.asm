; Marks all stage background tiles for redrawing that lie in the area covered
; by [tile_invalidate_box] around [center] (in playfield space and 16th-pixel
; units).

; void pascal near tiles_invalidate_around(Point center);
public TILES_INVALIDATE_AROUND
tiles_invalidate_around	proc near
@@center	= Point ptr 2

	mov	bx, sp
	mov	dx, _tile_invalidate_box.x
	shr	dx, 1
	mov	ax, ss:[bx+@@center.x]
	sar	ax, 4
	sub	ax, dx
	cmp	ax, PLAYFIELD_W
	jl	short @@left_edge_left_of_playfield?

@@outside_playfield:
	retn	4
; ---------------------------------------------------------------------------

@@left_edge_left_of_playfield?:
	mov	cx, ax
	or	ax, ax
	js	short @@right_edge_left_of_playfield?
	and	ax, (TILE_W - 1)

@@right_edge_left_of_playfield?:
	add	ax, _tile_invalidate_box.x
	dec	ax
	js	short @@outside_playfield
	sar	cx, 4
	jns	short @@check_y
	xor	cx, cx

@@check_y:
	mov	_invalidate_left_x_tile, cx
	shr	ax, 4
	inc	ax
	mov	cx, ax	; CX = number of horizontal tiles to invalidate
	mov	dx, _tile_invalidate_box.y
	sar	dx, 1
	mov	ax, ss:[bx+@@center.y]
	sar	ax, 4
	add	ax, TILE_H
	sub	ax, dx
	jns	short @@bottom_below_playfield?
	mov	dx, _tile_invalidate_box.y
	add	dx, ax
	or	dx, dx
	jle	short @@outside_playfield

@@bottom_below_playfield?:
	cmp	ax, PLAYFIELD_H + TILE_H
	jge	short @@outside_playfield
	mov	bh, 0
	mov	bl, _page_back
	add	bx, bx
	add	ax, _scroll_line_on_plane[bx]
	jns	short @@scroll_wrap?
	add	ax, RES_Y
	jmp	short @@invalidate
; ---------------------------------------------------------------------------

@@scroll_wrap?:
	cmp	ax, RES_Y
	jl	short @@invalidate
	sub	ax, RES_Y

@@invalidate:
	mov	dx, ax
	and	dx, 7
	add	dx, _tile_invalidate_box.y	; DX = Invalidated height in pixels
	mov	bx, dx
	add	bx, ax
	shr	ax, 3
	shl	ax, 5	; AX *= TILES_MEMORY_X
	push	si
	push	di
	push	ds
	pop	es
	assume es:_DATA
	mov	di, ax
	add	di, _invalidate_left_x_tile
	add	di, offset _halftiles_dirty
	mov	si, TILES_MEMORY_X
	sub	si, cx	; SI = row stride
	mov	ah, cl
	mov	al, 1
	cmp	bx, RES_Y
	jl	short @@set_nowrap
	mov	bx, offset _halftiles_dirty_end

@@set_wrap:
	mov	cl, ah
	rep stosb
	sub	dx, TILE_FLAG_H
	add	di, si
	cmp	di, bx
	jl	short @@set_wrap
	sub	di, size _halftiles_dirty

@@set_nowrap:
	mov	cl, ah
	rep stosb
	add	di, si
	sub	dx, TILE_FLAG_H
	jg	short @@set_nowrap
	pop	di
	pop	si
	retn	4
tiles_invalidate_around	endp

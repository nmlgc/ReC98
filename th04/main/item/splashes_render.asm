public ITEM_SPLASHES_RENDER
item_splashes_render	proc near

@@radius	= word ptr -4
@@i		= word ptr -2

	enter	4, 0
	push	si
	push	di
	mov	ah, 15
	call	_grcg_setcolor_direct_seg1_raw
	mov	si, offset _item_splashes
	mov	[bp+@@i], 0
	jmp	short @@more?

@@alive?:
	cmp	[si+item_splash_t.flag], 1
	jnz	short @@next_circle
	xor	di, di
	jmp	short @@drawn_all_dots?

@@draw:
	mov	ax, [si+item_splash_t.radius_cur]
	mov	[bp+@@radius], ax
	push	offset _drawpoint
	push	[si+item_splash_t.center.x]
	push	[si+item_splash_t.center.y]
	push	ax
	push	di
	call	vector2_at
	cmp	_drawpoint.y, 0
	jl	short @@next_dot
	cmp	_drawpoint.y, (PLAYFIELD_H shl 4)
	jge	short @@next_dot
	cmp	_drawpoint.x, 0
	jl	short @@next_dot
	cmp	_drawpoint.x, (PLAYFIELD_W shl 4)
	jge	short @@next_dot
	mov	ax, _drawpoint.y
	add	ax, (PLAYFIELD_Y shl 4)
	call	scroll_subpixel_y_to_vram_seg1 pascal, ax
	mov	dx, ax
	mov	ax, _drawpoint.x
	sar	ax, 4
	add	ax, PLAYFIELD_X
	call	@item_splash_dot_render

@@next_dot:
	add	di, 256 / ITEM_SPLASH_DOTS

@@drawn_all_dots?:
	cmp	di, 256
	jl	short @@draw

@@next_circle:
	inc	[bp+@@i]
	add	si, size item_splash_t

@@more?:
	cmp	[bp+@@i], ITEM_SPLASH_COUNT
	jl	short @@alive?
	pop	di
	pop	si
	leave
	retn
item_splashes_render	endp

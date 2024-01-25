public ITEMS_RENDER
items_render	proc near
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	ax, GRAM_400
	mov	es, ax
	call	item_splashes_render
	mov	si, offset _items
	xor	di, di
	jmp	short @@more?

@@loop:
	cmp	[si.item_t.flag], F_ALIVE
	jnz	short @@next
	cmp	[si+item_t.pos.cur.y], (-(ITEM_H / 2) shl 4)
	jle	short @@next
	mov	ax, [si+item_t.pos.cur.y]
	add	ax, ((PLAYFIELD_TOP - (ITEM_H / 2)) shl 4)
	call	scroll_subpixel_y_to_vram_seg1 pascal, ax
	mov	dx, ax
	mov	ax, [si+item_t.pos.cur.x]
	sar	ax, 4
	add	ax, PLAYFIELD_LEFT - (ITEM_W / 2)
	call	z_super_roll_put_tiny_16x16_raw pascal, [si+item_t.ITEM_patnum]

@@next:
	inc	di
	add	si, size item_t

@@more?:
	cmp	di, ITEM_COUNT
	jl	short @@loop
	pop	di
	pop	si
	pop	bp
	retn
items_render	endp

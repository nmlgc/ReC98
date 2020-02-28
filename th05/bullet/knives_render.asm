public KNIVES_RENDER
knives_render	proc near

@@patnum_tiny	= word ptr -2

	enter	2, 0
	push	si
	push	di
	mov	ax, GRAM_400
	mov	es, ax
	mov	si, offset knives
	mov	di, 1
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+knife_t.flag], 0
	jz	short @@next
	mov	ax, [si+knife_t.KNIFE_patnum_tiny]
	mov	[bp+@@patnum_tiny], ax
	call	scroll_subpixel_y_to_vram_seg1 pascal, [si+knife_t.pos.cur.y]
	mov	dx, ax
	mov	ax, [si+knife_t.pos.cur.x]
	sar	ax, 4
	add	ax, (PLAYFIELD_X - (KNIFE_W / 2))
	call	z_super_roll_put_tiny_32x32_raw pascal, [bp+@@patnum_tiny]

@@next:
	inc	di
	add	si, size knife_t

@@more?:
	cmp	di, 1 + KNIFE_COUNT
	jl	short @@loop
	pop	di
	pop	si
	leave
	retn
knives_render	endp

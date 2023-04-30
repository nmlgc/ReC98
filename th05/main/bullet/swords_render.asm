public SWORDS_RENDER
swords_render proc near

@@patnum_tiny	= word ptr -2

	enter	2, 0
	push	si
	push	di
	mov	ax, GRAM_400
	mov	es, ax
	mov	si, offset swords
	mov	di, 1
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+sword_t.flag], F_FREE
	jz	short @@next
	mov	ax, [si+sword_t.SWORD_patnum_tiny]
	mov	[bp+@@patnum_tiny], ax
	call	scroll_subpixel_y_to_vram_seg1 pascal, [si+sword_t.pos.cur.y]
	mov	dx, ax
	mov	ax, [si+sword_t.pos.cur.x]
	sar	ax, 4
	add	ax, (PLAYFIELD_LEFT - (SWORD_W / 2))
	call	z_super_roll_put_tiny_32x32_raw pascal, [bp+@@patnum_tiny]

@@next:
	inc	di
	add	si, size sword_t

@@more?:
	cmp	di, 1 + SWORD_COUNT
	jl	short @@loop
	pop	di
	pop	si
	leave
	retn
swords_render endp

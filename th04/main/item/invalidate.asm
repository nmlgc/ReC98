public @items_invalidate$qv
@items_invalidate$qv proc near
	push	si
	push	di
	mov	_tile_invalidate_box, (ITEM_W shl 16) or ITEM_H
	mov	si, offset _items
if GAME eq 5
	; ZUN bug: ITEM_COUNT was 32 in TH04 and is 40 in TH05. This is the only
	; function in TH05 that still has 32.
	mov	di, 32
else
	mov	di, ITEM_COUNT
endif

@@item_loop:
	cmp	[si+item_t.flag], F_FREE
	jz	short @@item_next
	call	tiles_invalidate_around pascal, large dword ptr [si+item_t.pos.prev]

@@item_next:
	add	si, size item_t
	dec	di
	jnz	short @@item_loop
	mov	si, offset _item_splashes
	mov	di, ITEM_SPLASH_COUNT

@@item_splash_loop:
	cmp	[si+item_splash_t.flag], F_FREE
	jz	short @@item_splash_next
	mov	ax, [si+item_splash_t.radius_prev]
	shr	ax, 3
	inc	ax
	mov	_tile_invalidate_box.x, ax
	mov	_tile_invalidate_box.y, ax
	call	tiles_invalidate_around pascal, large dword ptr [si+item_splash_t.center]

@@item_splash_next:
	add	si, size item_splash_t
	dec	di
	jnz	short @@item_splash_loop
	pop	di
	pop	si
	retn
@items_invalidate$qv endp
	nop

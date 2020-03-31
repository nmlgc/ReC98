public BULLETS_GATHER_INVALIDATE
bullets_gather_invalidate	proc near
	push	si
	push	di
	mov	si, offset _bullets
	if GAME eq 5
		mov	di, PELLET_COUNT
		mov	_tile_invalidate_box, (PELLET_W shl 16) or PELLET_H
	else
		mov	di, BULLET_COUNT
	endif
	cmp	_bullet_clear_trigger, 0
	jnz	short @@pellets_decaying
	cmp	_bullet_clear_time, 0
	jnz	short @@pellets_decaying
	if GAME eq 4
		mov	_tile_invalidate_box, (PELLET_W shl 16) or PELLET_H
		mov	di, PELLET_COUNT
	endif

@@pellet_loop:
	cmp	[si+bullet_t.flag], 0
	jz	short @@pellet_next
	if GAME eq 5
		cmp	[si+bullet_t.spawn_state], BSS_GRAZED
		jbe	short @@pellet_not_grazed
		shl	_tile_invalidate_box, 1
		call	tiles_invalidate_around pascal, large dword ptr [si+bullet_t.pos.prev]
		shr	_tile_invalidate_box, 1
		jmp	short @@pellet_next
	; ---------------------------------------------------------------------------

	@@pellet_not_grazed:
	endif
	call	tiles_invalidate_around pascal, large dword ptr [si+bullet_t.pos.prev]

@@pellet_next:
	add	si, size bullet_t
	dec	di
	jnz	short @@pellet_loop

	if GAME eq 5
	@@pellets_decaying:
		add	di, BULLET16_COUNT
		shl	_tile_invalidate_box, 1
	else
		mov	di, BULLET16_COUNT

	@@pellets_decaying:
		mov	_tile_invalidate_box, (BULLET16_W shl 16) or BULLET16_H
	endif

@@bullet16_loop:
	cmp	[si+bullet_t.flag], 0
	jz	short @@bullet16_next
	cmp	[si+bullet_t.spawn_state], BSS_GRAZED
	jbe	short @@bullet16_not_grazed
	shl	_tile_invalidate_box, 1
	call	tiles_invalidate_around pascal, large dword ptr [si+bullet_t.pos.prev]
	shr	_tile_invalidate_box, 1
	jmp	short @@bullet16_next
; ---------------------------------------------------------------------------

@@bullet16_not_grazed:
	call	tiles_invalidate_around pascal, large dword ptr [si+bullet_t.pos.prev]

@@bullet16_next:
	add	si, size bullet_t
	dec	di
	jnz	short @@bullet16_loop
	mov	si, offset _gather_circles
	mov	di, GATHER_COUNT

@@gather_loop:
	cmp	[si+gather_t.G_flag], 0
	jz	short @@gather_next
	mov	ax, [si+gather_t.G_radius_cur]
	shr	ax, 3
	add	ax, 16
	mov	_tile_invalidate_box.x, ax
	mov	_tile_invalidate_box.y, ax
	call	tiles_invalidate_around pascal, large dword ptr [si+gather_t.G_center.prev]

@@gather_next:
	add	si, size gather_t
	dec	di
	jnz	short @@gather_loop
	pop	di
	pop	si
	retn
bullets_gather_invalidate	endp
	even

public @enemies_invalidate$qv
@enemies_invalidate$qv proc near
	push	si
	push	di
	mov	_tile_invalidate_box, (ENEMY_W shl 16) or ENEMY_H
	mov	si, offset _enemies
	mov	di, ENEMY_COUNT

@@loop:
	cmp	[si+enemy_t.flag], EF_FREE
	jz	short @@next
	cmp	[si+enemy_t.flag], EF_ALIVE_FIRST_FRAME
	jz	short @@next
	call	tiles_invalidate_around pascal, large dword ptr [si+enemy_t.pos.prev]

@@next:
	add	si, size enemy_t
	dec	di
	jnz	short @@loop
	pop	di
	pop	si
	retn
@enemies_invalidate$qv endp
	even

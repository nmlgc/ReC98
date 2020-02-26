public STAGE2_INVALIDATE
stage2_invalidate	proc near
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	_tile_invalidate_box.x, 8
	mov	_tile_invalidate_box.y, 8
	mov	si, offset s2particles
	xor	di, di
	jmp	short @@more?

@@loop:
	cmp	[si+s2particle_t.flag], 0
	jz	short @@next
	call	tiles_invalidate_around pascal, [si+s2particle_t.pos.prev.y], [si+s2particle_t.pos.prev.x]

@@next:
	inc	di
	add	si, size s2particle_t

@@more?:
	cmp	di, S2PARTICLE_COUNT
	jl	short @@loop
	pop	di
	pop	si
	pop	bp
	retn
stage2_invalidate	endp

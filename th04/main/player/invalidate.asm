; void pascal near player_invalidate(void);
public PLAYER_INVALIDATE
player_invalidate	proc near
@@angle	= byte ptr [bp-1]

	enter	2, 0
	push	si
	push	di
	mov	_tile_invalidate_box.y, PLAYER_H
	cmp	_miss_time, 0
	jz	short @@alive
	mov	_tile_invalidate_box.x, MISS_EXPLOSION_W
	mov	ax, _miss_explosion_radius
	; Go back a frame
	add	ax, -MISS_EXPLOSION_RADIUS_VELOCITY
	mov	di, ax
	xor	si, si
	mov	al, _miss_explosion_angle
	add	al, -MISS_EXPLOSION_ANGLE_VELOCITY
	jmp	short @@more?

@@loop:
	cmp	si, MISS_EXPLOSION_COUNT / 2
	jnz	short @@invalidate
	mov	ax, di
	cwd
	sub	ax, dx
	sar	ax, 1
	mov	di, ax
	mov	al, @@angle
	neg	al
	mov	@@angle, al

@@invalidate:
	push	offset _drawpoint
	push	_player_pos.cur.x
	push	_player_pos.cur.y
	push	di
	mov	al, @@angle
	mov	ah, 0
	push	ax
	call	vector2_at
	MISS_EXPLOSION_CLIP	 @@next
	call	main_01:tiles_invalidate_around pascal, _drawpoint.y, _drawpoint.x

@@next:
	inc	si
	mov	al, @@angle
	add	al, 256 / (MISS_EXPLOSION_COUNT / 2)

@@more?:
	mov	@@angle, al
	cmp	si, MISS_EXPLOSION_COUNT
	jl	short @@loop
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@alive:
	mov	_tile_invalidate_box.x, PLAYER_W
	call	main_01:tiles_invalidate_around pascal, large [_player_pos.prev]
	mov	_tile_invalidate_box.x, PLAYER_OPTION_W + PLAYER_W + PLAYER_OPTION_W
	mov	_tile_invalidate_box.y, PLAYER_OPTION_H
	call	main_01:tiles_invalidate_around pascal, large [_player_option_pos_prev]

@@ret:
	pop	di
	pop	si
	leave
	retn
player_invalidate	endp

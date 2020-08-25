public EXPLOSIONS_SMALL_UPDATE_AND_RENDER
explosions_small_update_and_render	proc near

@@angle		= byte ptr -7
@@i     	= word ptr -6
@@draw_y	= word ptr -4
@@draw_x	= word ptr -2

	enter	8, 0
	push	si
	push	di
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	call	_grcg_setmode_rmw_seg1
	mov	si, offset _explosions_small
	mov	[bp+@@i], 0
	jmp	@@more_explosions?
; ---------------------------------------------------------------------------

@@explosion_loop:
	cmp	[si+explosion_t.flag], 0
	jz	@@next_explosion
	xor	di, di
	mov	[bp+@@angle], 0
	jmp	short @@more_sprites?
; ---------------------------------------------------------------------------

@@sprite_loop:
	push	[si+explosion_t.center.x]
	push	[si+explosion_t.EXPLOSION_radius_cur.x]
	mov	al, [bp+@@angle]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_CosTable8[bx]
	call	vector1_at
	mov	[bp+@@draw_x], ax
	push	[si+explosion_t.center.y]
	push	[si+explosion_t.EXPLOSION_radius_cur.y]
	mov	al, [si+explosion_t.angle_offset]
	add	al, [bp+@@angle]
	mov	ah, 0
	add	ax, ax
	mov	bx, ax
	push	_SinTable8[bx]
	call	vector1_at
	mov	[bp+@@draw_y], ax
	sar	ax, 4
	add	ax, PLAYFIELD_TOP - (EXPLOSION_SMALL_H / 2)
	mov	dx, ax
	mov	ax, [bp+@@draw_x]
	sar	ax, 4
	add	ax, PLAYFIELD_LEFT - (EXPLOSION_SMALL_W / 2)
	cmp	ax, PLAYFIELD_LEFT - EXPLOSION_SMALL_W
	jbe	short @@next_sprite
	cmp	ax, PLAYFIELD_LEFT + PLAYFIELD_W
	jnb	short @@next_sprite
	or	dx, dx
	jbe	short @@next_sprite
	cmp	dx, PLAYFIELD_TOP + PLAYFIELD_H
	jnb	short @@next_sprite
	call	z_super_roll_put_tiny_16x16_raw pascal, PAT_EXPLOSION_SMALL

@@next_sprite:
	inc	di
	mov	al, [bp+@@angle]
	add	al, (256 / EXPLOSION_SMALL_SPRITES)
	mov	[bp+@@angle], al

@@more_sprites?:
	cmp	di, EXPLOSION_SMALL_SPRITES
	jl	short @@sprite_loop
	mov	ax, [si+explosion_t.EXPLOSION_radius_delta.x]
	add	[si+explosion_t.EXPLOSION_radius_cur.x], ax
	mov	ax, [si+explosion_t.EXPLOSION_radius_delta.y]
	add	[si+explosion_t.EXPLOSION_radius_cur.y], ax
	inc	[si+explosion_t.age]
	cmp	[si+explosion_t.age], EXPLOSION_AGE_MAX
	jb	short @@next_explosion
	mov	[si+explosion_t.flag], 0

@@next_explosion:
	inc	[bp+@@i]
	add	si, size explosion_t

@@more_explosions?:
	cmp	[bp+@@i], 2
	jl	@@explosion_loop
	GRCG_OFF_CLOBBERING dx
	pop	di
	pop	si
	leave
	retn
explosions_small_update_and_render	endp

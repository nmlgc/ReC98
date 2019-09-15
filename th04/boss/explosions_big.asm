; void pascal near explosions_big_update_and_render(void);
public EXPLOSIONS_BIG_UPDATE_AND_RENDER
explosions_big_update_and_render	proc near

@@angle 	= byte ptr -5
@@draw_y	= word ptr -4
@@i     	= word ptr -2

	enter	6, 0
	push	si
	push	di
	mov	si, offset _explosions_big
	cmp	[si+explosion_t.flag], 0
	jz	@@reset_frame
	mov	[bp+@@i], 0
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
	mov	di, ax
	sar	ax, 4
	mov	di, ax
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
	; Yes, these are not clipped exactly to the playfield boundaries?
	add	ax, -16
	mov	[bp+@@draw_y], ax
	or	di, di
	jl	short @@next_sprite
	cmp	di, 384
	jg	short @@next_sprite
	cmp	[bp+@@draw_y], 0
	jl	short @@next_sprite
	cmp	[bp+@@draw_y], 336
	jg	short @@next_sprite
	call	super_put pascal, di, ax, 3

@@next_sprite:
	inc	[bp+@@i]
	mov	al, [bp+@@angle]
	add	al, (256 / EXPLOSION_BIG_SPRITES)
	mov	[bp+@@angle], al

@@more_sprites?:
	cmp	[bp+@@i], EXPLOSION_BIG_SPRITES
	jl	short @@sprite_loop
	mov	ax, [si+explosion_t.EXPLOSION_radius_delta.x]
	add	[si+explosion_t.EXPLOSION_radius_cur.x], ax
	mov	ax, [si+explosion_t.EXPLOSION_radius_delta.y]
	add	[si+explosion_t.EXPLOSION_radius_cur.y], ax
	inc	[si+explosion_t.age]
	cmp	[si+explosion_t.age], EXPLOSION_AGE_MAX
	jb	short @@tone_update
	mov	[si+explosion_t.flag], 0

@@tone_update:
	inc	_explosion_big_frame
	cmp	_explosion_big_frame, 8
	jge	short @@tone_flash?
	test	byte ptr _explosion_big_frame, 1
	jz	short @@tone_flash?
	mov	PaletteTone, 150
	jmp	short @@ret_palette_changed
; ---------------------------------------------------------------------------

@@tone_flash?:
	cmp	_explosion_big_frame, 8
	jl	short @@tone_regular
	cmp	_explosion_big_frame, 16
	jge	short @@tone_regular
	mov	ax, _explosion_big_frame
	imul	ax, 6
	mov	dx, 196
	sub	dx, ax
	mov	PaletteTone, dx

@@ret_palette_changed:
	mov	_palette_changed, 1
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@tone_regular:
	mov	PaletteTone, 100
	jmp	short @@ret_palette_changed
; ---------------------------------------------------------------------------

@@reset_frame:
	mov	_explosion_big_frame, 0

@@ret:
	pop	di
	pop	si
	leave
	retn
explosions_big_update_and_render	endp

; void pascal near player_render(void);
public PLAYER_RENDER
player_render	proc near
@@angle   	= byte ptr -5
@@i       	= word ptr -4
@@screen_y	= word ptr -2
@@patnum  	equ si

	enter	6, 0
	push	si
	push	di
	cmp	_miss_time, 0
	jz	short @@alive
	cmp	_miss_time, MISS_ANIM_FRAMES
	jbe	@@in_miss_anim

@@alive:
	mov	ax, _player_pos.cur.x
	sar	ax, 4
	add	ax, PLAYFIELD_LEFT - (PLAYER_W / 2)
	mov	di, ax
	mov	ax, _player_pos.cur.y
	add	ax, ((PLAYFIELD_TOP - (PLAYER_H / 2)) shl 4)
	call	scroll_subpixel_y_to_vram_seg1 pascal, ax
	mov	[bp+@@screen_y], ax
	cmp	_player_pos.velocity.x, 0
	jge	short @@moving_right?
	mov	@@patnum, 1
	jmp	short @@invincible?

@@moving_right?:
	cmp	_player_pos.velocity.x, 0
	jz	short @@no_x_movement
	mov	@@patnum, 2
	jmp	short @@invincible?

@@no_x_movement:
	xor	@@patnum, @@patnum

; ---------------------------------------------------------------------------

@@invincible?:
	cmp	_player_invincibility_time, 0
	jz	short @@render_regular
	cmp	_stage_frame_mod4, 0
	jnz	short @@render_regular
	call	super_roll_put_1plane pascal, di, [bp+@@screen_y], @@patnum, large PLANE_PUT or GC_BRGI
	jmp	short @@got_options?

@@render_regular:
	call	super_roll_put  pascal, di, [bp+@@screen_y], @@patnum

@@got_options?:
	cmp	_shot_level, 2
	jb	@@ret
	call	@grcg_setmode_rmw$qv
	mov	ax, _player_option_pos_cur.x
	sar	ax, 4
	; Technically, DI = AX + PLAYFIELD_LEFT - PLAYER_OPTION_DISTANCE - (PLAYER_OPTION_W / 2)
	mov	di, ax
	mov	ax, _player_option_pos_cur.y
	add	ax, ((PLAYFIELD_TOP - (PLAYER_OPTION_H / 2)) shl 4)
	call	scroll_subpixel_y_to_vram_seg1 pascal, ax
	mov	[bp+@@screen_y], ax
	mov	ax, di
	mov	dx, [bp+@@screen_y]
	call	z_super_roll_put_tiny_16x16_raw pascal, _player_option_patnum
	lea	ax, [di + PLAYER_OPTION_DISTANCE * 2]
	mov	dx, [bp+@@screen_y]
	call	z_super_roll_put_tiny_16x16_raw pascal, _player_option_patnum
	GRCG_OFF_CLOBBERING dx
	jmp	@@ret
; ---------------------------------------------------------------------------

@@in_miss_anim:
	cmp	_miss_time, MISS_ANIM_FRAMES - MISS_ANIM_EXPLODE_UNTIL
	jbe	@@ret
	mov	si, _miss_explosion_radius
	mov	[bp+@@i], 0
	mov	al, _miss_explosion_angle
	jmp	short @@more?

@@loop:
	cmp	[bp+@@i], MISS_EXPLOSION_COUNT / 2
	jnz	short @@put
	mov	ax, si
	cwd
	sub	ax, dx
	sar	ax, 1
	mov	si, ax
	mov	al, [bp+@@angle]
	neg	al
	mov	[bp+@@angle], al

@@put:
	push	offset _drawpoint
	push	_player_pos.cur.x
	push	_player_pos.cur.y
	push	si
	mov	al, [bp+@@angle]
	mov	ah, 0
	push	ax
	call	vector2_at
	MISS_EXPLOSION_CLIP	@@next
	mov	ax, _drawpoint.x
	sar	ax, 4
	add	ax, PLAYFIELD_LEFT - (MISS_EXPLOSION_W / 2)
	mov	di, ax
	mov	ax, _drawpoint.y
	add	ax, ((PLAYFIELD_TOP - (MISS_EXPLOSION_H / 2)) shl 4)
	call	scroll_subpixel_y_to_vram_seg1 pascal, ax
	mov	[bp+@@screen_y], ax
	call	super_roll_put pascal, di, ax, 3

@@next:
	inc	[bp+@@i]
	mov	al, [bp+@@angle]
	add	al, 256 / (MISS_EXPLOSION_COUNT / 2)

@@more?:
	mov	[bp+@@angle], al
	cmp	[bp+@@i], MISS_EXPLOSION_COUNT
	jl	short @@loop

@@ret:
	pop	di
	pop	si
	leave
	retn
player_render	endp

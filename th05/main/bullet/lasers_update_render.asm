	@LASER_RENDER_RAY$QRX14LASER_COORDS_T procdesc pascal near \
		coords:word

public @lasers_render$qv
@lasers_render$qv	proc near

@@radius	= byte ptr -0Ah
@@width_orig	= byte ptr -9
@@end_distance_orig	= word ptr -8
@@draw_y	= word ptr -6
@@draw_x	= word ptr -4
@@i	= word ptr -2

	push	bp
	mov	bp, sp
	sub	sp, 0Ah
	push	si
	push	di
	mov	si, offset _lasers
	mov	[bp+@@i], 0
	jmp	@@more_lasers?
; ---------------------------------------------------------------------------

@@laser_loop:
	cmp	[si+laser_t.flag], LF_FREE
	jz	@@next_laser
	mov	al, [si+laser_t.coords.LASER_width]
	mov	[bp+@@width_orig], al
	mov	[bp+@@radius], al
	push	offset _drawpoint
	push	[si+laser_t.coords.origin.x]
	push	[si+laser_t.coords.origin.y]
	push	(16 shl 4)
	mov	al, [si+laser_t.coords.angle]
	mov	ah, 0
	push	ax
	call	vector2_at
	mov	ax, _drawpoint.x
	sar	ax, 4
	add	ax, 32
	mov	[bp+@@draw_x], ax
	mov	ax, _drawpoint.y
	sar	ax, 4
	add	ax, 16
	mov	[bp+@@draw_y], ax
	cmp	[si+laser_t.flag], LF_SHOOTOUT_DECAY
	jz	@@decay
	cmp	[bp+@@radius], 2
	jnb	short @@draw_outer_circle?
	mov	[bp+@@radius], 2

@@draw_outer_circle?:
	cmp	[si+laser_t.coords.LASER_width], 3
	jb	short @@draw_inner_circle?
	mov	ah, [si+laser_t.LASER_color]
	call	@grcg_setcolor_direct_raw$qv
	cmp	[si+laser_t.coords.starts_at_distance], (16 shl 4)
	jg	short @@draw_outer_ray?
	push	[bp+@@draw_x]
	push	[bp+@@draw_y]
	mov	al, [bp+@@radius]
	mov	ah, 0
	push	ax
	call	grcg_circlefill
	mov	al, [bp+@@radius]
	add	al, -2
	mov	[bp+@@radius], al

@@draw_outer_ray?:
	cmp	[si+laser_t.coords.ends_at_distance], (2 shl 4)
	jle	short @@draw_inner
	mov	ax, [si+laser_t.coords.ends_at_distance]
	mov	[bp+@@end_distance_orig], ax
	sub	[si+laser_t.coords.ends_at_distance], (2 shl 4)
	lea	ax, [si+laser_t.coords]
	call	@laser_render_ray$qrx14laser_coords_t pascal, ax
	mov	ax, [bp+@@end_distance_orig]
	mov	[si+laser_t.coords.ends_at_distance], ax

@@draw_inner:
	cmp	[si+laser_t.coords.LASER_width], 5
	jb	short @@sub_2
	mov	al, [si+laser_t.coords.LASER_width]
	add	al, -4
	jmp	short @@set_inner_width
; ---------------------------------------------------------------------------

@@sub_2:
	mov	al, [si+laser_t.coords.LASER_width]
	add	al, -2

@@set_inner_width:
	mov	[si+laser_t.coords.LASER_width], al

@@draw_inner_circle?:
	mov	ah, V_WHITE
	call	@grcg_setcolor_direct_raw$qv
	cmp	[si+laser_t.coords.starts_at_distance], (16 shl 4)
	jg	short @@draw_inner_ray_or_line?
	push	[bp+@@draw_x]
	push	[bp+@@draw_y]
	mov	al, [bp+@@radius]
	mov	ah, 0
	push	ax
	call	grcg_circlefill

@@draw_inner_ray_or_line?:
	cmp	[si+laser_t.coords.LASER_width], 1
	ja	short @@draw_inner_ray
	push	offset _drawpoint
	push	[si+laser_t.coords.origin.x]
	push	[si+laser_t.coords.origin.y]
	push	[si+laser_t.coords.starts_at_distance]
	mov	al, [si+laser_t.coords.angle]
	mov	ah, 0
	push	ax
	call	vector2_at
	push	offset _laser_line_endpoint
	push	[si+laser_t.coords.origin.x]
	push	[si+laser_t.coords.origin.y]
	push	[si+laser_t.coords.ends_at_distance]
	mov	al, [si+laser_t.coords.angle]
	mov	ah, 0
	push	ax
	call	vector2_at
	mov	ax, _drawpoint.x
	sar	ax, 4
	add	ax, 32
	mov	_drawpoint.x, ax
	mov	ax, _drawpoint.y
	sar	ax, 4
	add	ax, 16
	mov	_drawpoint.y, ax
	mov	ax, _laser_line_endpoint.x
	sar	ax, 4
	add	ax, 32
	mov	_laser_line_endpoint.x, ax
	mov	ax, _laser_line_endpoint.y
	sar	ax, 4
	add	ax, 16
	mov	_laser_line_endpoint.y, ax
	push	_drawpoint.x
	push	_drawpoint.y
	push	_laser_line_endpoint.x
	push	ax
	call	grcg_line
	jmp	@@width_reset
; ---------------------------------------------------------------------------

@@draw_inner_ray:
	lea	ax, [si+laser_t.coords]
	call	@laser_render_ray$qrx14laser_coords_t pascal, ax
	or	ax, ax
	jz	@@width_reset
	mov	[si+laser_t.flag], LF_FREE
	jmp	@@width_reset
; ---------------------------------------------------------------------------

@@decay:
	mov	ah, V_WHITE
	call	@grcg_setcolor_direct_raw$qv
	shl	[bp+@@radius], 3
	push	offset _drawpoint
	push	[si+laser_t.coords.origin.x]
	push	[si+laser_t.coords.origin.y]
	mov	al, [bp+@@radius]
	mov	ah, 0
	push	ax
	mov	al, [si+laser_t.coords.angle]
	mov	ah, 0
	add	ax, 40h
	push	ax
	call	vector2_at
	xor	di, di
	jmp	@@more_decay_lines?
; ---------------------------------------------------------------------------

@@decay_line_draw:
	push	offset _laser_line_endpoint
	push	_drawpoint.x
	push	_drawpoint.y
	push	[si+laser_t.coords.ends_at_distance]
	mov	al, [si+laser_t.coords.angle]
	mov	ah, 0
	push	ax
	call	vector2_at
	push	offset _drawpoint
	push	_drawpoint.x
	push	_drawpoint.y
	push	[si+laser_t.coords.starts_at_distance]
	mov	al, [si+laser_t.coords.angle]
	mov	ah, 0
	push	ax
	call	vector2_at
	mov	ax, _drawpoint.x
	sar	ax, 4
	add	ax, 32
	mov	_drawpoint.x, ax
	mov	ax, _drawpoint.y
	sar	ax, 4
	add	ax, 16
	mov	_drawpoint.y, ax
	mov	ax, _laser_line_endpoint.x
	sar	ax, 4
	add	ax, 32
	mov	_laser_line_endpoint.x, ax
	mov	ax, _laser_line_endpoint.y
	sar	ax, 4
	add	ax, 16
	mov	_laser_line_endpoint.y, ax
	push	_drawpoint.x
	push	_drawpoint.y
	push	_laser_line_endpoint.x
	push	ax
	call	grcg_line
	push	offset _drawpoint
	push	[si+laser_t.coords.origin.x]
	push	[si+laser_t.coords.origin.y]
	mov	al, [bp+@@radius]
	mov	ah, 0
	push	ax
	mov	al, [si+laser_t.coords.angle]
	mov	ah, 0
	add	ax, (-4 shl 4)
	push	ax
	call	vector2_at
	inc	di

@@more_decay_lines?:
	cmp	di, 2
	jl	@@decay_line_draw

@@width_reset:
	mov	al, [bp+@@width_orig]
	mov	[si+laser_t.coords.LASER_width], al

@@next_laser:
	inc	[bp+@@i]
	add	si, size laser_t

@@more_lasers?:
	cmp	[bp+@@i], LASER_COUNT
	jl	@@laser_loop
	pop	di
	pop	si
	leave
	retn
@lasers_render$qv	endp

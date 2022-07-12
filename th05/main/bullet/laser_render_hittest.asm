; Returns the Y coordinate in AX.

; int __usercall near vector2_at_opt(int angle<cx>, pixel_t length<bx>, Point origin<ss:bp>, Point near *ret<ss:di>)
vector2_at_opt	proc near
	push	si
	mov	si, cx
	add	si, si
	movsx	eax, bx
	movsx	edx, _CosTable8[si]
	imul	eax, edx
	sar	eax, 8
	add	ax, [bp+Point.x]
	mov	ss:[di+Point.x], ax
	movsx	eax, bx
	movsx	edx, _SinTable8[si]
	imul	eax, edx
	sar	eax, 8
	add	ax, [bp+Point.y]
	mov	ss:[di+Point.y], ax
	pop	si
	retn
vector2_at_opt	endp


; Builds a line starting at [s], with [t] being [edgelength] 1/16th pixel
; units away from [s]. [s] and [t] are returned in pixel units.

; void __usercall build_line_in_pixels(
; 	Point *s<ss:di> /* (inout) */,
; 	Point *t<ss:bx> /* (out) */,
; 	const Point *edgelength<ss:bp-4> /* (out) */
; )
build_line_in_pixels	proc near
	mov	ax, [bp+size Point+Point.x]
	mov	dx, ss:[di+Point.x]
	add	ax, dx
	sar	ax, 4
	sar	dx, 4
	mov	ss:[bx+Point.x], ax
	mov	ss:[di+Point.x], dx
	mov	ax, [bp+size Point+Point.y]
	mov	dx, ss:[di+Point.y]
	add	ax, dx
	sar	ax, 4
	sar	dx, 4
	mov	ss:[bx+Point.y], ax
	mov	ss:[di+Point.y], dx
	retn
build_line_in_pixels	endp


public @LASER_RENDER_RAY$QP14LASER_COORDS_T
@laser_render_ray$qp14laser_coords_t proc near
point0  	= Point ptr -20h
point1  	= Point ptr -1Ch
point2  	= Point ptr -18h
point3  	= Point ptr -14h
point4  	= Point ptr -10h
point5  	= Point ptr -0Ch
point6  	= Point ptr -8
point7  	= Point ptr -4
@@coords	= word ptr  4

	enter	20h, 0
	push	si
	push	di
	mov	si, [bp+@@coords]
	mov	bl, [si+laser_coords_t.LASER_width]
	mov	bh, 0
	shl	bx, 3
	mov	ax, [si.laser_coords_t.origin.x]
	add	ax, (32 shl 4) ; Translate playfield space to screen space (X)
	mov	[bp+point7.x], ax
	mov	ax, [si+laser_coords_t.origin.y]
	add	ax, (16 shl 4) ; Translate playfield space to screen space (Y)
	mov	[bp+point7.y], ax
	mov	cl, [si+laser_coords_t.angle]
	add	cl, 64
	mov	ch, 0
	lea	di, [bp+point6]
	sub	bp, size Point ; bp = point7
	call	vector2_at_opt
	add	cl, 128
	sub	di, 4 ; di = point5
	call	vector2_at_opt
	sub	[bp-(size Point)+Point.y], ax ; bp = line edge length (Y)
	mov	ax, [bp-(size Point * 2).Point.x]
	sub	[bp-(size Point)+Point.x], ax ; bp = line edge length (X)
	mov	cl, [si+laser_coords_t.angle]
	mov	bx, [si+laser_coords_t.starts_at_distance]
	sub	di, size Point * 5 ; di = point0
	sub	bp, size Point * 2 ; bp = point5
	call	vector2_at_opt
	mov	bx, [si+laser_coords_t.ends_at_distance]
	add	di, size Point * 3 ; di = point3
	call	vector2_at_opt
	lea	di, [bp-(size Point * 5)] ; di = point0
	lea	bx, [bp-(size Point * 4)] ; bx = point1
	call	build_line_in_pixels
	add	di, size Point * 3 ; di = point3
	add	bx, size Point     ; bx = point2
	call	build_line_in_pixels
	add	bp, size Point * 3 ; bp = (what you'd actually expect it to be)
	lea	di, [bp+point0]
	call	grc_clip_polygon_n pascal, ss, di, 8, ss, di, 4
	or	ax, ax
	jz	short @@offscreen
	jge	short @@draw
	mov	ax, 4

@@draw:
	call	grcg_polygon_cx pascal, ss, di, ax
	xor	ax, ax
	jmp	short @@ret

@@offscreen:
	mov	ax, 1

@@ret:
	pop	di
	pop	si
	leave
	retn	2
@laser_render_ray$qp14laser_coords_t endp


public @LASER_HITTEST$QR7LASER_T
@laser_hittest$qr7laser_t proc near
testrect_center		= byte ptr -4
laser		= word ptr  4

	enter	8, 0
	push	di
	push	si
	mov	di, [bp+laser]
	mov	bx, [di+laser_t.coords.ends_at_distance]
	mov	si, [di+laser_t.coords.starts_at_distance]
	sub	bp, size Point
	mov	eax, dword ptr [di+laser_t.coords.origin]
	mov	[bp+0],	eax
	mov	cl, [di+laser_t.coords.angle]
	xor	ch, ch
	lea	di, [bp+testrect_center]

@@loop:
	call	vector2_at_opt
	add	ax, (6 shl 4)
	sub	ax, _player_pos.cur.y
	cmp	ax, (12 shl 4)
	jnb	short @@testrect_move_up
	mov	ax, ss:[di+Point.x]
	add	ax, (6 shl 4)
	sub	ax, _player_pos.cur.x
	cmp	ax, (12 shl 4)
	jnb	short @@testrect_move_up
	mov	_player_is_hit, 1
	jmp	short @@ret

@@testrect_move_up:
	sub	bx, (16 shl 4)
	cmp	bx, si
	jge	short @@loop

@@ret:
	add	bp, 4
	pop	si
	pop	di
	leave
	ret	2
@laser_hittest$qr7laser_t endp

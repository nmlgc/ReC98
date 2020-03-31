public _gather_point_clip
_gather_point_clip	proc near
	push	bp
	mov	bp, sp
	cmp	_drawpoint.x, (-(GATHER_POINT_W / 2) shl 4)
	jle	short @@clip
	cmp	_drawpoint.x, ((PLAYFIELD_W + (GATHER_POINT_W / 2)) shl 4)
	jge	short @@clip
	cmp	_drawpoint.y, (-(GATHER_POINT_H / 2) shl 4)
	jle	short @@clip
	cmp	_drawpoint.y, ((PLAYFIELD_H + (GATHER_POINT_H / 2)) shl 4)
	jge	short @@clip
	mov	ax, 1
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@clip:
	xor	ax, ax

@@ret:
	pop	bp
	retn
_gather_point_clip	endp


public GATHER_RENDER
gather_render	proc far

@@col		= byte ptr -4
@@angle		= byte ptr -3
@@i		= word ptr -2

	enter	4, 0
	push	si
	push	di
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	mov	[bp+@@col], -1
	mov	si, offset _gather_circles
	mov	[bp+@@i], 0
	jmp	short @@circles_more?
; ---------------------------------------------------------------------------

@@circle_loop:
	cmp	[si+gather_t.G_flag], 1
	jnz	short @@circles_next
	mov	al, [si+gather_t.G_col]
	cmp	al, [bp+@@col]
	jz	short @@same_color
	mov	[bp+@@col], al
	mov	ah, [bp+@@col]
	call	grcg_setcolor_direct_noint_2

@@same_color:
	xor	di, di
	jmp	short @@points_more?
; ---------------------------------------------------------------------------

@@point_loop:
	mov	ax, di
	shl	ax, 8
	cwd
	idiv	[si+gather_t.G_ring_points]
	add	al, [si+gather_t.G_angle_cur]
	mov	[bp+@@angle], al
	push	offset _drawpoint
	push	[si+gather_t.G_center.x]
	push	[si+gather_t.G_center.y]
	push	[si+gather_t.G_radius_cur]
	mov	ah, 0
	push	ax
	call	vector2_at
	call	_gather_point_clip
	or	al, al
	jz	short @@point_next
	mov	ax, _drawpoint.y
	add	ax, ((PLAYFIELD_Y - (GATHER_POINT_H / 2)) shl 4)
	call	scroll_subpixel_y_to_vram_seg3 pascal, ax
	mov	dx, ax
	mov	ax, _drawpoint.x
	sar	ax, 4
	add	ax, (PLAYFIELD_X - (GATHER_POINT_W / 2))
	call	@gather_point_render

@@point_next:
	inc	di

@@points_more?:
	cmp	[si+gather_t.G_ring_points], di
	jg	short @@point_loop

@@circles_next:
	inc	[bp+@@i]
	add	si, size gather_t

@@circles_more?:
	cmp	[bp+@@i], GATHER_CAP
	jl	short @@circle_loop
	pop	di
	pop	si
	leave
	retf
gather_render	endp

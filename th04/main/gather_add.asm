public GATHER_BULLET_TEMPLATE_PULL
gather_bullet_template_pull	proc near

@@gather		= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	push	di
if GAME eq 5
	mov	cx, size _bullet_template / 2
	push	ds
	pop	es
	assume es:_DATA
	mov	si, offset _bullet_template
	mov	di, [bp+@@gather]
	add	di, gather_t.G_bullet_template
else
	push	ds
	pop	es
	assume es:_DATA
	mov	si, offset _bullet_template
	mov	di, [bp+@@gather]
	add	di, gather_t.G_bullet_template
	mov	cx, size _bullet_template / 2
endif
	rep movsw
	pop	di
	pop	si
	pop	bp
	retn	2
gather_bullet_template_pull	endp


public _gather_add_bullets
_gather_add_bullets	proc near
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, offset _gather_circles
	xor	di, di
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+gather_t.G_flag], 0
	jnz	short @@next
	mov	[si+gather_t.G_flag], 1
	call	gather_bullet_template_pull pascal, si
	mov	ax, _gather_template.GT_center.x
	mov	[si+gather_t.G_center.x], ax
	mov	ax, _gather_template.GT_center.y
	mov	[si+gather_t.G_center.y], ax
	mov	ax, _gather_template.GT_radius
	mov	[si+gather_t.G_radius_cur], ax
	mov	[si+gather_t.G_radius_prev], ax
	mov	ax, _gather_template.GT_velocity.x
	mov	[si+gather_t.G_center.velocity.x], ax
	mov	ax, _gather_template.GT_velocity.y
	mov	[si+gather_t.G_center.velocity.y], ax
	mov	[si+gather_t.G_angle_cur], 0
	mov	al, _gather_template.GT_angle_delta
	mov	[si+gather_t.G_angle_delta], al
	mov	al, _gather_template.GT_col
	mov	[si+gather_t.G_col], al
	mov	ax, _gather_template.GT_ring_points
	mov	[si+gather_t.G_ring_points], ax
	mov	ax, _gather_template.GT_radius
	mov	bx, GATHER_FRAMES
	cwd
	idiv	bx
	mov	[si+gather_t.G_radius_delta], ax
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@next:
	inc	di
	add	si, size gather_t

@@more?:
	cmp	di, GATHER_CAP
	jl	short @@loop

@@ret:
	pop	di
	pop	si
	pop	bp
	retn
_gather_add_bullets	endp


public _gather_add_only
_gather_add_only	proc near
	push	bp
	mov	bp, sp
	push	si
	mov	si, offset _gather_circles
	xor	cx, cx
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+gather_t.G_flag], 0
	jnz	short @@next
	mov	[si+gather_t.G_flag], 1
	mov	[si+gather_t.G_bullet_template.spawn_type], BST_GATHER_ONLY
	mov	ax, _gather_template.GT_center.x
	mov	[si+gather_t.G_center.x], ax
	mov	ax, _gather_template.GT_center.y
	mov	[si+gather_t.G_center.y], ax
	mov	ax, _gather_template.GT_radius
	mov	[si+gather_t.G_radius_cur], ax
	mov	[si+gather_t.G_radius_prev], ax
	mov	ax, _gather_template.GT_velocity.x
	mov	[si+gather_t.G_center.velocity.x], ax
	mov	ax, _gather_template.GT_velocity.y
	mov	[si+gather_t.G_center.velocity.y], ax
	mov	[si+gather_t.G_angle_cur], 0
	mov	al, _gather_template.GT_angle_delta
	mov	[si+gather_t.G_angle_delta], al
	mov	al, _gather_template.GT_col
	mov	[si+gather_t.G_col], al
	mov	ax, _gather_template.GT_ring_points
	mov	[si+gather_t.G_ring_points], ax
	mov	ax, _gather_template.GT_radius
	mov	bx, GATHER_FRAMES
	cwd
	idiv	bx
	mov	[si+gather_t.G_radius_delta], ax
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@next:
	inc	cx
	add	si, size gather_t

@@more?:
	cmp	cx, GATHER_CAP
	jl	short @@loop

@@ret:
	pop	si
	pop	bp
	retn
_gather_add_only	endp

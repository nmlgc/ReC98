public CIRCLES_ADD_GROWING
circles_add_growing	proc far
@@center_y	= word ptr  6
@@center_x	= word ptr  8

	push	bp
	mov	bp, sp
	push	si
	mov	si, offset _circles
	xor	cx, cx
	jmp	short @@more?

@@loop:
	cmp	[si+circle_t.flag], 0
	jnz	short @@next
	mov	[si+circle_t.flag], 1
	mov	[si+circle_t.age], 0
	mov	ax, [bp+@@center_x]
	mov	bx, 16
	cwd
	idiv	bx
	add	ax, 32
	mov	[si+circle_t.center.x],	ax
	mov	ax, [bp+@@center_y]
	cwd
	idiv	bx
	add	ax, 16
	mov	[si+circle_t.center.y],	ax
	mov	[si+circle_t.radius_cur], 4
	mov	[si+circle_t.radius_delta], 8
	jmp	short @@ret

@@next:
	inc	cx
	add	si, size circle_t

@@more?:
	cmp	cx, CIRCLE_COUNT
	jl	short @@loop

@@ret:
	pop	si
	pop	bp
	retf	4
circles_add_growing	endp


public CIRCLES_ADD_SHRINKING
circles_add_shrinking	proc far
@@center_y	= word ptr  6
@@center_x	= word ptr  8

	push	bp
	mov	bp, sp
	push	si
	mov	si, offset _circles
	xor	cx, cx
	jmp	short @@more?

@@loop:
	cmp	[si+circle_t.flag], 0
	jnz	short @@next
	mov	[si+circle_t.flag], 1
	mov	[si+circle_t.age], 0
	mov	ax, [bp+@@center_x]
	mov	bx, 10h
	cwd
	idiv	bx
	add	ax, 32
	mov	[si+circle_t.center.x],	ax
	mov	ax, [bp+@@center_y]
	cwd
	idiv	bx
	add	ax, 16
	mov	[si+circle_t.center.y],	ax
	mov	[si+circle_t.radius_cur], 132
	mov	[si+circle_t.radius_delta], -8
	jmp	short @@ret

@@next:
	inc	cx
	add	si, size circle_t

@@more?:
	cmp	cx, CIRCLE_COUNT
	jl	short @@loop

@@ret:
	pop	si
	pop	bp
	retf	4
circles_add_shrinking	endp


public CIRCLES_UPDATE
circles_update	proc near
	push	bp
	mov	bp, sp
	push	si
	mov	si, offset _circles
	xor	dx, dx
	jmp	short @@more?

@@loop:
	cmp	[si+circle_t.flag], 2
	jnz	short @@alive?
	mov	[si+circle_t.flag], 0

@@alive?:
	cmp	[si+circle_t.flag], 1
	jnz	short @@next
	mov	ax, [si+circle_t.radius_delta]
	add	[si+circle_t.radius_cur], ax
	inc	[si+circle_t.age]
	cmp	[si+circle_t.age], 16
	jbe	short @@next
	mov	[si+circle_t.flag], 2

@@next:
	inc	dx
	add	si, size circle_t

@@more?:
	cmp	dx, CIRCLE_COUNT
	jl	short @@loop
	pop	si
	pop	bp
	retn
circles_update	endp


public CIRCLES_RENDER
circles_render	proc near
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	ah, _circles_color
	call	@grcg_setcolor_direct_raw$qv
	mov	si, offset _circles
	xor	di, di
	jmp	short @@more?

@@loop?:
	cmp	[si+circle_t.flag], 1
	jnz	short @@next
	push	[si+circle_t.center.x]
	push	[si+circle_t.center.y]
	push	[si+circle_t.radius_cur]
	call	grcg_circle

@@next:
	inc	di
	add	si, size circle_t

@@more?:
	cmp	di, CIRCLE_COUNT
	jl	short @@loop?
	pop	di
	pop	si
	pop	bp
	retn
circles_render	endp

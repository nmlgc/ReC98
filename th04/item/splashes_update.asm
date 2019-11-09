public ITEM_SPLASHES_INIT
item_splashes_init	proc near
	push	bp
	mov	bp, sp
	push	di
	mov	cx, size _item_splashes / 2
	mov	ax, ds
	mov	es, ax
	assume es:_DATA
	xor	ax, ax
	mov	di, offset _item_splashes
	rep stosw
	mov	_item_splash_last_id, 0
	pop	di
	pop	bp
	retn
item_splashes_init	endp


public ITEM_SPLASHES_ADD
item_splashes_add	proc near
@@y	= word ptr  4
@@x	= word ptr  6

	push	bp
	mov	bp, sp
	push	si
	mov	al, _item_splash_last_id
	mov	ah, 0
	imul	ax, size item_splash_t
	add	ax, offset _item_splashes
	mov	si, ax
	inc	_item_splash_last_id
	cmp	_item_splash_last_id, ITEM_SPLASH_COUNT
	jb	short @@found
	mov	_item_splash_last_id, 0

@@found:
	cmp	[si+item_splash_t.flag], 0
	jnz	short @@ret
	mov	[si+item_splash_t.flag], 1
	mov	ax, [bp+@@x]
	mov	[si+item_splash_t.center.x], ax
	mov	ax, [bp+@@y]
	mov	[si+item_splash_t.center.y], ax
	mov	[si+item_splash_t.radius_cur], ITEM_SPLASH_RADIUS_START
	mov	[si+item_splash_t.ITEM_SPLASH_time], 16
	mov	[si+item_splash_t.radius_prev], ITEM_SPLASH_RADIUS_START

@@ret:
	pop	si
	pop	bp
	retn	4
item_splashes_add	endp


public ITEM_SPLASHES_UPDATE
item_splashes_update	proc near
	push	bp
	mov	bp, sp
	push	si
	mov	si, offset _item_splashes
	xor	dx, dx
	jmp	short @@more?

@@loop:
	cmp	[si+item_splash_t.flag], 0
	jz	short @@next
	cmp	[si+item_splash_t.flag], 2
	jnz	short @@alive
	mov	[si+item_splash_t.flag], 0
	jmp	short @@next

@@alive:
	mov	ax, [si+item_splash_t.radius_cur]
	mov	[si+item_splash_t.radius_prev],	ax
	add	[si+item_splash_t.radius_cur], ITEM_SPLASH_RADIUS_DELTA
	cmp	[si+item_splash_t.radius_cur], ITEM_SPLASH_RADIUS_END
	jl	short @@next
	mov	[si+item_splash_t.flag], 2

@@next:
	inc	dx
	add	si, size item_splash_t

@@more?:
	cmp	dx, ITEM_SPLASH_COUNT
	jl	short @@loop
	pop	si
	pop	bp
	retn
item_splashes_update	endp

B6BF_FREE = 0
B6BF_CLOUD = 1

public @SHINKI_CUSTOMBULLETS_RENDER$QV
@shinki_custombullets_render$qv proc near
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, offset b6balls
	mov	di, 1
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+b6ball_t.flag], B6BF_FREE
	jz	short @@next
	cmp	[si+b6ball_t.flag], B6BF_CLOUD
	jnz	short @@no_cloud
	mov	ah, V_WHITE
	call	@grcg_setcolor_direct_raw$qv
	mov	ax, [si+b6ball_t.pos.cur.x]
	sar	ax, 4
	add	ax, PLAYFIELD_LEFT
	push	ax
	mov	ax, [si+b6ball_t.pos.cur.y]
	sar	ax, 4
	add	ax, PLAYFIELD_TOP
	push	ax
	mov	ax, [si+b6ball_t.cloud_radius]
	mov	bx, 16
	cwd
	idiv	bx
	push	ax
	call	grcg_circlefill
	jmp	short @@next
; ---------------------------------------------------------------------------

@@no_cloud:
	mov	ax, GRAM_400
	mov	es, ax
	mov	ax, [si+b6ball_t.pos.cur.y]
	sar	ax, 4
	mov	dx, ax
	mov	ax, [si+b6ball_t.pos.cur.x]
	sar	ax, 4
	add	ax, (PLAYFIELD_LEFT - (B6BALL_W / 2))
	or	dx, dx
	jl	short @@next
	call	z_super_roll_put_tiny_32x32_raw pascal, [si+b6ball_t.B6B_patnum_tiny]

@@next:
	inc	di
	add	si, size b6ball_t

@@more?:
	cmp	di, 1 + B6BALL_COUNT
	jl	short @@loop
	call	cheetos_render
	pop	di
	pop	si
	pop	bp
	retn
@shinki_custombullets_render$qv endp

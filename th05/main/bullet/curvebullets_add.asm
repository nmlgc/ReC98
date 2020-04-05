public CURVEBULLETS_ADD
curvebullets_add	proc near

@@trail		= word ptr -4
@@i		= word ptr -2

	push	bp
	mov	bp, sp
	sub	sp, 4
	push	si
	push	di
	mov	si, offset curvebullet_heads
	mov	[bp+@@trail], offset _curvebullet_trails
	mov	[bp+@@i], 1
	jmp	short @@curvebullets_more?
; ---------------------------------------------------------------------------

@@curvebullet_loop:
	cmp	[si.curvebullet_head_t.flag], 0
	jnz	short @@curvebullet_next
	mov	bx, [bp+@@trail]
	cmp	[bx+curvebullet_trail_t.flag], 0
	jnz	short @@curvebullet_next
	mov	bx, [bp+@@trail]
	mov	[bx+curvebullet_trail_t.flag], 1
	mov	al, curvebullet_template.CBTMPL_angle
	mov	[si+curvebullet_head_t.CBH_angle], al
	mov	al, curvebullet_template.CBTMPL_speed
	mov	[si+curvebullet_head_t.CBH_speed], al
	lea	ax, [si+curvebullet_head_t.pos.velocity]
	push	ax
	push	word ptr [si+curvebullet_head_t.CBH_angle]
	mov	al, [si+curvebullet_head_t.CBH_speed]
	mov	ah, 0
	push	ax
	call	vector2_near
	mov	bx, [bp+@@trail]
	mov	al, byte ptr curvebullet_template.CBTMPL_col
	mov	[bx+curvebullet_trail_t.CBT_col], al
	call	bullet_patnum_for_angle pascal, 0, word ptr [si+curvebullet_head_t.CBH_angle]
	mov	ah, 0
	mov	[si+curvebullet_head_t.CBH_sprite], ax
	mov	eax, curvebullet_template.pos.cur
	mov	dword ptr [si+curvebullet_head_t.pos.cur], eax
	xor	di, di
	jmp	short @@trail_node_more?
; ---------------------------------------------------------------------------

@@trail_node_loop:
	mov	bx, di
	shl	bx, 2
	add	bx, [bp+@@trail]
	mov	eax, curvebullet_template.pos.cur
	mov	dword ptr [bx+curvebullet_trail_t.node_pos], eax
	mov	al, byte ptr [si+curvebullet_head_t.CBH_sprite]
	mov	bx, [bp+@@trail]
	mov	[bx+di+curvebullet_trail_t.node_sprite], al
	inc	di

@@trail_node_more?:
	cmp	di, CURVEBULLET_TRAIL_NODE_COUNT
	jl	short @@trail_node_loop
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@curvebullet_next:
	inc	[bp+@@i]
	add	si, size curvebullet_head_t
	add	[bp+@@trail], size curvebullet_trail_t

@@curvebullets_more?:
	cmp	[bp+@@i], 1 + CURVEBULLET_COUNT
	jl	@@curvebullet_loop

@@ret:
	pop	di
	pop	si
	leave
	retn
curvebullets_add	endp

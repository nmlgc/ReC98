public B4BALLS_RENDER
b4balls_render	proc near

@@i		= word ptr -2

	enter	2, 0
	push	si
	push	di
	mov	ax, GRAM_400
	mov	es, ax
	assume es:nothing
	mov	si, offset b4balls
	mov	[bp+@@i], 1
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+b4ball_t.flag], 0
	jz	short @@next
	mov	di, [si+b4ball_t.B4B_patnum_tiny_base]
	cmp	di, PAT_B4BALL_SNOW_HIT
	jge	short @@put
	mov	ax, [si+b4ball_t.B4B_age]
	and	ax, (B4BALL_CELS - 1)
	add	ax, di
	mov	di, ax
	cmp	[si+b4ball_t.B4B_damaged_this_frame], 0
	jz	short @@not_hit
	add	di, (PAT_B4BALL_SNOW_HIT - PAT_B4BALL_SNOW)

@@not_hit:
	mov	[si+b4ball_t.B4B_damaged_this_frame], 0

@@put:
	call	scroll_subpixel_y_to_vram_seg1 pascal, [si+b4ball_t.pos.cur.y]
	mov	dx, ax
	mov	ax, [si+b4ball_t.pos.cur.x]
	sar	ax, 4
	add	ax, (PLAYFIELD_X - (B4BALL_W / 2))
	call	z_super_roll_put_tiny_32x32_raw pascal, di

@@next:
	inc	[bp+@@i]
	add	si, size b4ball_t

@@more?:
	cmp	[bp+@@i], 1 + B4BALL_COUNT
	jl	short @@loop
	pop	di
	pop	si
	leave
	retn
b4balls_render	endp

public B4BALLS_RESET
b4balls_reset	proc near
	push	bp
	mov	bp, sp
	push	si
	mov	si, offset b4balls
	mov	ax, 1
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	mov	[si+b4ball_t.flag], 0
	inc	ax
	add	si, size b4ball_t

@@more?:
	cmp	ax, 1 + B4BALL_COUNT
	jl	short @@loop
	pop	si
	pop	bp
	retn
b4balls_reset	endp


public B4BALLS_ADD
b4balls_add	proc near

@@speed		= word ptr -2

	enter	2, 0
	push	si
	push	di
	mov	al, b4ball_template.B4B_speed
	call	@playperf_adjust_speed
	mov	ah, 0
	mov	[bp+@@speed], ax
	mov	si, offset b4balls
	mov	di, 1
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+b4ball_t.flag], 0
	jnz	short @@next
	mov	[si+b4ball_t.flag], 1
	mov	eax, b4ball_template.pos.cur
	mov	dword ptr [si+b4ball_t.pos.cur], eax
	lea	ax, [si+b4ball_t.pos.velocity]
	call	vector2_near pascal, ax, word ptr b4ball_template.B4B_angle, [bp+@@speed]
	mov	al, b4ball_template.B4B_angle
	mov	[si+b4ball_t.B4B_angle], al
	mov	al, b4ball_template.B4B_speed
	mov	[si+b4ball_t.B4B_speed], al
	mov	ax, b4ball_template.B4B_patnum_tiny_base
	mov	[si+b4ball_t.B4B_patnum_tiny_base], ax
	mov	ax, b4ball_template.B4B_hp
	mov	[si+b4ball_t.B4B_hp], ax
	mov	[si+b4ball_t.B4B_damaged_this_frame], 0
	mov	ax, b4ball_template.B4B_revenge
	mov	[si+b4ball_t.B4B_revenge], ax
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@next:
	inc	di
	add	si, size b4ball_t

@@more?:
	cmp	di, 1 + B4BALL_COUNT
	jl	short @@loop

@@ret:
	pop	di
	pop	si
	leave
	retn
b4balls_add	endp

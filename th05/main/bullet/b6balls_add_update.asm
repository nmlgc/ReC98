public B6BALLS_ADD
b6balls_add	proc near

@@speed		= word ptr -2

	enter	2, 0
	push	si
	push	di
	mov	al, b6ball_template.B6B_speed
	call	@playperf_adjust_speed
	mov	ah, 0
	mov	[bp+@@speed], ax
	mov	si, offset b6balls
	mov	di, 1
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+b6ball_t.flag], 0
	jnz	short @@next
	mov	[si+b6ball_t.flag], 1
	mov	eax, b6ball_template.pos.cur
	mov	dword ptr [si+b6ball_t.pos.cur], eax
	lea	ax, [si+b6ball_t.pos.velocity]
	call	vector2_near pascal, ax, word ptr b6ball_template.B6B_angle, [bp+@@speed]
	mov	ax, b6ball_template.B6B_patnum_tiny
	mov	[si+b6ball_t.B6B_patnum_tiny], ax
	mov	[si+b6ball_t.cloud_radius], (48 shl 4)
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@next:
	inc	di
	add	si, size b6ball_t

@@more?:
	cmp	di, 1 + B6BALL_COUNT
	jl	short @@loop

@@ret:
	pop	di
	pop	si
	leave
	retn
b6balls_add	endp


public B6BALLS_UPDATE
b6balls_update	proc near
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, offset b6balls
	mov	di, 1
	jmp	@@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+b6ball_t.flag], 0
	jz	@@next
	cmp	[si+b6ball_t.flag], 1
	jnz	short @@no_cloud
	sub	[si+b6ball_t.cloud_radius], (2 shl 4)
	cmp	[si+b6ball_t.cloud_radius], ((B6BALL_W / 2) shl 4)
	jge	@@next
	inc	[si+b6ball_t.flag]

@@no_cloud:
	cmp	_bullet_clear_time, 0
	jnz	short @@decay
	cmp	_bullet_clear_trigger, 0
	jz	short @@motion_update

@@decay:
	mov	[si+b6ball_t.flag], 3

@@motion_update:
	inc	[si+b6ball_t.B6B_age]
	lea	ax, [si+b6ball_t.pos.cur]
	call	_motion_update_2 pascal, ax
	cmp	ax, (-16 shl 4)
	jle	short @@clip
	cmp	ax, ((PLAYFIELD_W + 16) shl 4)
	jge	short @@clip
	cmp	dx, (-16 shl 4)
	jle	short @@clip
	cmp	dx, ((PLAYFIELD_H + 16) shl 4)
	jl	short @@hitbox_active_or_already_decaying?

@@clip:
	jmp	short @@remove
; ---------------------------------------------------------------------------

@@hitbox_active_or_already_decaying?:
	cmp	[si+b6ball_t.flag], 3
	jz	short @@in_decay_state
	sub	ax, _player_pos.cur.x
	sub	dx, _player_pos.cur.y
	add	ax, 8 * 16
	cmp	ax, 16 * 16
	ja	short @@not_hitting_player
	add	dx, 8 * 16
	cmp	dx, 16 * 16
	ja	short @@not_hitting_player
	mov	_player_is_hit, 1
	mov	[si+b6ball_t.flag], 3
	jmp	short @@next
; ---------------------------------------------------------------------------

@@not_hitting_player:
	jmp	short @@next
; ---------------------------------------------------------------------------

@@in_decay_state:
	cmp	[si+b6ball_t.B6B_patnum_tiny], PAT_DECAY_B6BALL
	jge	short @@already_decaying
	mov	[si+b6ball_t.B6B_patnum_tiny], PAT_DECAY_B6BALL
	mov	ax, [si+b6ball_t.pos.velocity.x]
	cwd
	sub	ax, dx
	sar	ax, 1
	mov	[si+b6ball_t.pos.velocity.x], ax
	mov	ax, [si+b6ball_t.pos.velocity.y]
	cwd
	sub	ax, dx
	sar	ax, 1
	mov	[si+b6ball_t.pos.velocity.y], ax
	mov	[si+b6ball_t.B6B_decay_frames], 0
	jmp	short @@next
; ---------------------------------------------------------------------------

@@already_decaying:
	inc	[si+b6ball_t.B6B_decay_frames]
	mov	ax, [si+b6ball_t.B6B_decay_frames]
	mov	bx, 4
	cwd
	idiv	bx
	or	dx, dx
	jnz	short @@next
	inc	[si+b6ball_t.B6B_patnum_tiny]
	cmp	[si+b6ball_t.B6B_patnum_tiny], (PAT_DECAY_B6BALL + BULLET_DECAY_CELS)
	jl	short @@next

@@remove:
	mov	[si+b6ball_t.flag], 0

@@next:
	inc	di
	add	si, size b6ball_t

@@more?:
	cmp	di, 1 + B6BALL_COUNT
	jl	@@loop
	pop	di
	pop	si
	pop	bp
	retn
b6balls_update	endp

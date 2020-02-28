public KNIVES_ADD
knives_add	proc near

@@speed		= word ptr -2

	enter	2, 0
	push	si
	push	di
	mov	al, knife_template.KNIFE_speed
	call	@playperf_adjust_speed
	mov	ah, 0
	mov	[bp+@@speed], ax
	mov	_circles_color, GC_RG
	mov	si, offset knives
	mov	di, 1
	jmp	short @@next
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+knife_t.flag], 0
	jnz	short @@more?
	mov	[si+knife_t.flag], 1
	mov	eax, knife_template.pos.cur
	mov	dword ptr [si+knife_t.pos.cur], eax
	call	circles_add_shrinking pascal, knife_template.pos.cur.x, knife_template.pos.cur.y
	lea	ax, [si+knife_t.pos.velocity]
	call	vector2_near pascal, ax, word ptr knife_template.KNIFE_angle, [bp+@@speed]
	mov	al, knife_template.KNIFE_angle
	mov	[si+knife_t.KNIFE_angle], al
	call	bullet_patnum_for_angle pascal, PAT_KNIFE, word ptr knife_template.KNIFE_angle
	mov	ah, 0
	mov	[si+knife_t.KNIFE_patnum_tiny], ax
	mov	al, byte ptr [bp+@@speed]
	mov	[si+knife_t.KNIFE_speed], al
	mov	ax, knife_template.twirl_time
	mov	[si+knife_t.twirl_time], ax
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@more?:
	inc	di
	add	si, size knife_t

@@next:
	cmp	di, 1 + KNIFE_COUNT
	jl	short @@loop

@@ret:
	pop	di
	pop	si
	leave
	retn
knives_add	endp


public KNIVES_UPDATE
knives_update	proc near
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, offset knives
	mov	di, 1
	jmp	@@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+knife_t.flag], 0
	jz	@@next
	cmp	_bullet_clear_time, 0
	jz	short @@still_twirling?
	cmp	[si+knife_t.flag], 1
	jnz	short @@still_twirling?
	mov	[si+knife_t.flag], 2
	mov	[si+knife_t.twirl_time], 0

@@still_twirling?:
	cmp	[si+knife_t.twirl_time], 0
	jbe	short @@no_twirl
	dec	[si+knife_t.twirl_time]
	cmp	[si+knife_t.twirl_time], 0
	jnz	short @@twirl
	call	bullet_patnum_for_angle pascal, PAT_KNIFE, word ptr [si+knife_t.KNIFE_angle]
	mov	ah, 0
	mov	[si+knife_t.KNIFE_patnum_tiny], ax
	call	snd_se_play pascal, 3
	jmp	short @@no_twirl
; ---------------------------------------------------------------------------

@@twirl:
	test	di, 1
	jz	short @@twirl_counterclockwise
	add	[si+knife_t.KNIFE_patnum_tiny], 2
	cmp	[si+knife_t.KNIFE_patnum_tiny], (PAT_KNIFE + BULLET_V_CELS)
	jl	@@next
	sub	[si+knife_t.KNIFE_patnum_tiny], BULLET_V_CELS
	jmp	@@next
; ---------------------------------------------------------------------------

@@twirl_counterclockwise:
	sub	[si+knife_t.KNIFE_patnum_tiny], 2
	cmp	[si+knife_t.KNIFE_patnum_tiny], PAT_KNIFE
	jge	@@next
	add	[si+knife_t.KNIFE_patnum_tiny], BULLET_V_CELS
	jmp	@@next
; ---------------------------------------------------------------------------

@@no_twirl:
	lea	ax, [si+knife_t.pos]
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
	cmp	[si+knife_t.flag], 2
	jz	short @@in_decay_state
	sub	ax, _player_pos.cur.x
	sub	dx, _player_pos.cur.y
	add	ax, (7 shl 4)
	cmp	ax, (14 shl 4)
	ja	short @@not_hitting_player
	add	dx, (7 shl 4)
	cmp	dx, (14 shl 4)
	ja	short @@not_hitting_player
	mov	_player_is_hit, 1
	mov	[si+knife_t.flag], 2
	jmp	short @@next
; ---------------------------------------------------------------------------

@@not_hitting_player:
	jmp	short @@next
; ---------------------------------------------------------------------------

@@in_decay_state:
	cmp	[si+knife_t.KNIFE_patnum_tiny], PAT_DECAY_KNIFE
	jge	short @@already_decaying
	mov	[si+knife_t.KNIFE_patnum_tiny], PAT_DECAY_KNIFE
	mov	ax, [si+knife_t.pos.velocity.x]
	cwd
	sub	ax, dx
	sar	ax, 1
	mov	[si+knife_t.pos.velocity.x], ax
	mov	ax, [si+knife_t.pos.velocity.y]
	cwd
	sub	ax, dx
	sar	ax, 1
	mov	[si+knife_t.pos.velocity.y], ax
	mov	[si+knife_t.KNIFE_decay_frames], 0
	jmp	short @@next
; ---------------------------------------------------------------------------

@@already_decaying:
	inc	[si+knife_t.KNIFE_decay_frames]
	mov	ax, [si+knife_t.KNIFE_decay_frames]
	mov	bx, 4
	cwd
	idiv	bx
	or	dx, dx
	jnz	short @@next
	inc	[si+knife_t.KNIFE_patnum_tiny]
	cmp	[si+knife_t.KNIFE_patnum_tiny], (PAT_DECAY_KNIFE + BULLET_DECAY_CELS)
	jl	short @@next

@@remove:
	mov	[si+knife_t.flag], 0

@@next:
	inc	di
	add	si, size knife_t

@@more?:
	cmp	di, 1 + KNIFE_COUNT
	jl	@@loop
	pop	di
	pop	si
	pop	bp
	retn
knives_update	endp

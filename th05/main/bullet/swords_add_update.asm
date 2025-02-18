public SWORDS_ADD
swords_add proc near

@@speed		= word ptr -2

	enter	2, 0
	push	si
	push	di
	mov	al, sword_template.SWORD_speed
	call	@playperf_speedtune
	mov	ah, 0
	mov	[bp+@@speed], ax
	mov	_circles_color, GC_RG
	mov	si, offset swords
	mov	di, 1
	jmp	short @@next
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+sword_t.flag], F_FREE
	jnz	short @@more?
	mov	[si+sword_t.flag], F_ALIVE
	mov	eax, sword_template.pos.cur
	mov	dword ptr [si+sword_t.pos.cur], eax
	call	@circles_add_shrinking$qii pascal, sword_template.pos.cur.x, sword_template.pos.cur.y
	lea	ax, [si+sword_t.pos.velocity]
	call	vector2_near pascal, ax, word ptr sword_template.SWORD_angle, [bp+@@speed]
	mov	al, sword_template.SWORD_angle
	mov	[si+sword_t.SWORD_angle], al
	call	@bullet_patnum_for_angle$quiuc pascal, PAT_SWORD, word ptr sword_template.SWORD_angle
	mov	ah, 0
	mov	[si+sword_t.SWORD_patnum_tiny], ax
	mov	al, byte ptr [bp+@@speed]
	mov	[si+sword_t.SWORD_speed], al
	mov	ax, sword_template.twirl_time
	mov	[si+sword_t.twirl_time], ax
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@more?:
	inc	di
	add	si, size sword_t

@@next:
	cmp	di, 1 + SWORD_COUNT
	jl	short @@loop

@@ret:
	pop	di
	pop	si
	leave
	retn
swords_add endp


public SWORDS_UPDATE
swords_update proc near
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	si, offset swords
	mov	di, 1
	jmp	@@more?
; ---------------------------------------------------------------------------

@@loop:
	cmp	[si+sword_t.flag], F_FREE
	jz	@@next
	cmp	_bullet_clear_time, 0
	jz	short @@still_twirling?
	cmp	[si+sword_t.flag], F_ALIVE
	jnz	short @@still_twirling?
	mov	[si+sword_t.flag], F_REMOVE
	mov	[si+sword_t.twirl_time], 0

@@still_twirling?:
	cmp	[si+sword_t.twirl_time], 0
	jbe	short @@no_twirl
	dec	[si+sword_t.twirl_time]
	cmp	[si+sword_t.twirl_time], 0
	jnz	short @@twirl
	call	@bullet_patnum_for_angle$quiuc pascal, PAT_SWORD, word ptr [si+sword_t.SWORD_angle]
	mov	ah, 0
	mov	[si+sword_t.SWORD_patnum_tiny], ax
	call	snd_se_play pascal, 3
	jmp	short @@no_twirl
; ---------------------------------------------------------------------------

@@twirl:
	test	di, 1
	jz	short @@twirl_counterclockwise
	add	[si+sword_t.SWORD_patnum_tiny], 2
	cmp	[si+sword_t.SWORD_patnum_tiny], (PAT_SWORD + BULLET_V_CELS)
	jl	@@next
	sub	[si+sword_t.SWORD_patnum_tiny], BULLET_V_CELS
	jmp	@@next
; ---------------------------------------------------------------------------

@@twirl_counterclockwise:
	sub	[si+sword_t.SWORD_patnum_tiny], 2
	cmp	[si+sword_t.SWORD_patnum_tiny], PAT_SWORD
	jge	@@next
	add	[si+sword_t.SWORD_patnum_tiny], BULLET_V_CELS
	jmp	@@next
; ---------------------------------------------------------------------------

@@no_twirl:
	lea	ax, [si+sword_t.pos]
	call	@PlayfieldMotion@update_seg3$qv pascal, ax
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
	cmp	[si+sword_t.flag], F_REMOVE
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
	mov	[si+sword_t.flag], F_REMOVE
	jmp	short @@next
; ---------------------------------------------------------------------------

@@not_hitting_player:
	jmp	short @@next
; ---------------------------------------------------------------------------

@@in_decay_state:
	cmp	[si+sword_t.SWORD_patnum_tiny], PAT_DECAY_SWORD
	jge	short @@already_decaying
	mov	[si+sword_t.SWORD_patnum_tiny], PAT_DECAY_SWORD
	mov	ax, [si+sword_t.pos.velocity.x]
	cwd
	sub	ax, dx
	sar	ax, 1
	mov	[si+sword_t.pos.velocity.x], ax
	mov	ax, [si+sword_t.pos.velocity.y]
	cwd
	sub	ax, dx
	sar	ax, 1
	mov	[si+sword_t.pos.velocity.y], ax
	mov	[si+sword_t.SWORD_decay_frames], 0
	jmp	short @@next
; ---------------------------------------------------------------------------

@@already_decaying:
	inc	[si+sword_t.SWORD_decay_frames]
	mov	ax, [si+sword_t.SWORD_decay_frames]
	mov	bx, 4
	cwd
	idiv	bx
	or	dx, dx
	jnz	short @@next
	inc	[si+sword_t.SWORD_patnum_tiny]
	cmp	[si+sword_t.SWORD_patnum_tiny], (PAT_DECAY_SWORD + BULLET_DECAY_CELS)
	jl	short @@next

@@remove:
	mov	[si+sword_t.flag], F_FREE

@@next:
	inc	di
	add	si, size sword_t

@@more?:
	cmp	di, 1 + SWORD_COUNT
	jl	@@loop
	pop	di
	pop	si
	pop	bp
	retn
swords_update endp

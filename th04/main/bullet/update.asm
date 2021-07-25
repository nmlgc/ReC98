public BULLET_TURN_X
bullet_turn_x proc near

@@bullet	= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	mov	si, [bp+@@bullet]
	inc	[si+bullet_t.turn_count]
	mov	al, 80h
	sub	al, [si+bullet_t.BULLET_angle]
	mov	[si+bullet_t.BULLET_angle], al
	mov	al, [si+bullet_t.turn_count]
	cmp	al, _bullet_turn_count_max
	jb	short @@still_allowed_to_turn
	mov	[si+bullet_t.move_state], BMS_REGULAR

@@still_allowed_to_turn:
	lea	ax, [si+bullet_t.pos.velocity]
	push	ax
	push	word ptr [si+bullet_t.BULLET_angle]
	mov	al, [si+bullet_t.speed_cur]
	mov	ah, 0
	push	ax
	call	vector2_near
if GAME eq 5
	call	bullet_update_patnum pascal, si
endif
	pop	si
	pop	bp
	retn	2
bullet_turn_x endp


public BULLET_TURN_Y
bullet_turn_y proc near

@@bullet	= word ptr  4

	push	bp
	mov	bp, sp
	push	si
	mov	si, [bp+@@bullet]
	inc	[si+bullet_t.turn_count]
	mov	al, [si+bullet_t.BULLET_angle]
	neg	al
	mov	[si+bullet_t.BULLET_angle], al
	mov	al, [si+bullet_t.turn_count]
	cmp	al, _bullet_turn_count_max
	jb	short @@still_allowed_to_turn
	mov	[si+bullet_t.move_state], BMS_REGULAR

@@still_allowed_to_turn:
	lea	ax, [si+bullet_t.pos.velocity]
	push	ax
	push	word ptr [si+bullet_t.BULLET_angle]
	mov	al, [si+bullet_t.speed_cur]
	mov	ah, 0
	push	ax
	call	vector2_near
if GAME eq 5
	call	bullet_update_patnum pascal, si
endif
	pop	si
	pop	bp
	retn	2
bullet_turn_y endp

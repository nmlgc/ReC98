public YUUKA6_PHASE_NEXT
yuuka6_phase_next proc near

@@next_end_hp		= word ptr  4
@@explosion_type		= word ptr  6

	push	bp
	mov	bp, sp
	cmp	_bullet_clear_time, 20
	jnb	short @@already_clearing
	mov	_bullet_clear_time, 20

@@already_clearing:
	call	@boss_explode_small$q16explosion_type_t pascal, [bp+@@explosion_type]
	inc	_boss_phase
	mov	_boss_phase_frame, 0
	mov	_boss_mode_change, 0
	mov	_boss_mode, 0
	mov	ax, _boss_phase_end_hp
	mov	_boss_hp, ax
	mov	ax, [bp+@@next_end_hp]
	mov	_boss_phase_end_hp, ax
	mov	_yuuka6_anim_frame, 0
	mov	_boss_sprite, PAT_YUUKA6_PARASOL_BACK_OPEN
	mov	_yuuka6_anim_frame, 0
	mov	_yuuka6_sprite_state, Y6SS_PARASOL_BACK_OPEN
	pop	bp
	retn	4
yuuka6_phase_next endp

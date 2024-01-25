public MUGETSU_PHASE2_NEXT
mugetsu_phase2_next	proc near

@@next_end_hp		= word ptr  4
@@explosion_type		= word ptr  6

	push	bp
	mov	bp, sp
	call	@boss_items_drop$qv
	call	@boss_explode_small$q16explosion_type_t pascal, [bp+@@explosion_type]
	inc	_boss_phase
	mov	_boss_phase_frame, 0
	mov	_boss_mode, 0
	mov	_boss_phase_state, 0
	mov	ax, _boss_phase_end_hp
	mov	_boss_hp, ax
	mov	ax, [bp+@@next_end_hp]
	mov	_boss_phase_end_hp, ax
	mov	_mugetsu_phase2_mode, 0
	pop	bp
	retn	4
mugetsu_phase2_next endp

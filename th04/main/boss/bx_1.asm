public MUGETSU_PHASE2_END
mugetsu_phase2_end	proc near

@@next_phase_end_hp		= word ptr  4
@@explosion_type		= word ptr  6

	push	bp
	mov	bp, sp
	call	_boss_items_drop
	call	boss_explode_small pascal, [bp+@@explosion_type]
	inc	_boss_phase
	mov	_boss_phase_frame, 0
	mov	_boss_mode, 0
	mov	_boss_mode_change, 0
	mov	ax, _boss_phase_end_hp
	mov	_boss_hp, ax
	mov	ax, [bp+@@next_phase_end_hp]
	mov	_boss_phase_end_hp, ax
	mov	_mugetsu_phase2_mode, 0
	pop	bp
	retn	4
mugetsu_phase2_end	endp

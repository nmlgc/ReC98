public EXALICE_PHASE_END
exalice_phase_end	proc near

@@next_phase_end_hp		= word ptr  4
@@explode_type		= word ptr  6

	push	bp
	mov	bp, sp
	push	si
	mov	si, [bp+@@explode_type]
	cmp	si, ET_NONE
	jz	short @@set
	call	boss_explode_small pascal, si
	cmp	_boss_phase_timed_out, 0
	jnz	short @@set
	mov	_bullet_zap_drop_point_items, 1
	mov	_bullet_zap_active, 1
	call	_boss_items_drop

@@set:
	mov	_boss_phase_timed_out, 1
	inc	_boss_phase
	mov	_boss_phase_frame, 0
	mov	_boss_mode, 0
	mov	_boss_mode_change, 0
	mov	ax, _boss_phase_end_hp
	mov	_boss_hp, ax
	mov	ax, [bp+@@next_phase_end_hp]
	mov	_boss_phase_end_hp, ax
	pop	si
	pop	bp
	retn	4
exalice_phase_end	endp

public CFG_LOAD_RESIDENT
cfg_load_resident	proc near

@@cfg	= cfg_t ptr -(size cfg_t)

	enter	(size cfg_t), 0
	push	si
	call	file_ropen pascal, ds, offset _CFG_FN
	push	ss
	lea	ax, [bp+@@cfg]
	push	ax
	push	size cfg_t
	call	file_read
	call	file_close
	mov	si, [bp+@@cfg.resident_sgm]
	mov	word ptr _resident+2, si
	mov	word ptr _resident, 0
	mov	ax, si
	pop	si
	leave
	retn
cfg_load_resident	endp

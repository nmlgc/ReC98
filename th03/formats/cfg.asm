public CFG_LOAD
cfg_load	proc near

@@sgm	= word ptr -0Ah
@@cfg	= byte ptr -(size cfg_t)

	enter	0Ah, 0
	call	file_ropen pascal, ds, offset aYume_cfg ; "YUME.CFG"
	push	ss
	lea	ax, [bp+@@cfg]
	push	ax
	push	size cfg_t
	call	file_read
	call	file_close
	mov	ax, [bp+@@cfg.resident_sgm]
	mov	[bp+@@sgm], ax
	mov	word ptr _resident+2, ax
	mov	word ptr _resident, 0
	les	bx, _resident
	mov	al, [bp+@@cfg.CFG_bgm_mode]
	mov	es:[bx+resident_t.bgm_mode], al
	call	snd_determine_mode
	mov	_snd_sel_disabled, 0
	cmp	_snd_active, 0
	jnz	short @@snd_disabled?
	les	bx, _resident
	mov	es:[bx+resident_t.bgm_mode], SND_BGM_OFF
	mov	_snd_sel_disabled, 1
	jmp	short @@set_and_ret
; ---------------------------------------------------------------------------

@@snd_disabled?:
	cmp	[bp+@@cfg.CFG_bgm_mode], SND_BGM_OFF
	jnz	short @@set_and_ret
	mov	_snd_active, 0

@@set_and_ret:
	les	bx, _resident
	mov	al, [bp+@@cfg.CFG_key_mode]
	mov	es:[bx+resident_t.key_mode], al
	mov	al, [bp+@@cfg.CFG_rank]
	mov	es:[bx+resident_t.rank], al
	leave
	retn
cfg_load	endp


public CFG_SAVE
cfg_save	proc near

@@cfg	= byte ptr -(size cfg_t)

	enter	(size cfg_t), 0
	call	file_append pascal, ds, offset aYume_cfg ; "YUME.CFG"
	call	file_seek pascal, large 0, 0
	les	bx, _resident
	mov	al, es:[bx+resident_t.bgm_mode]
	mov	[bp+@@cfg.opts.CFG_bgm_mode], al
	mov	al, es:[bx+resident_t.key_mode]
	mov	[bp+@@cfg.opts.CFG_key_mode], al
	mov	al, es:[bx+resident_t.rank]
	mov	[bp+@@cfg.opts.CFG_rank], al
	push	ss
	lea	ax, [bp+@@cfg]
	push	ax
	push	4
	call	file_write
	call	file_close
	leave
	retn
cfg_save	endp


public CFG_SAVE_EXIT
cfg_save_exit	proc near

@@cfg	= byte ptr -(size cfg_t)

	enter	(size cfg_t), 0
	lea	ax, [bp+@@cfg]
	push	ss
	push	ax
	push	ds
	push	offset _cfg_empty
	mov	cx, size _cfg_empty
	call	SCOPY@
	call	file_append pascal, ds, offset aYume_cfg ; "YUME.CFG"
	call	file_seek pascal, large 0, 0
	les	bx, _resident
	mov	al, es:[bx+resident_t.bgm_mode]
	mov	[bp+@@cfg.CFG_bgm_mode], al
	mov	al, es:[bx+resident_t.key_mode]
	mov	[bp+@@cfg.CFG_key_mode], al
	mov	al, es:[bx+resident_t.rank]
	mov	[bp+@@cfg.CFG_rank], al
	push	ss
	lea	ax, [bp+@@cfg]
	push	ax
	push	size cfg_t
	call	file_write
	call	file_close
	leave
	retn
cfg_save_exit	endp

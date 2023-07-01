public CFG_LOAD
cfg_load	proc near

@@seg	= word ptr -0Ch
@@cfg	= byte ptr -(size cfg_t)

	enter	0Ch, 0
	call	file_ropen pascal, ds, offset _cfg_fn
	push	ss
	lea	ax, [bp+@@cfg]
	push	ax
	push	size cfg_t
	call	file_read
	call	file_close
	mov	ax, [bp+@@cfg.resident_seg]
	mov	[bp+@@seg], ax
	mov	word ptr _resident+2, ax
	mov	word ptr _resident, 0
	les	bx, _resident
	; TH05 does this in RES_KSO.COM
if GAME eq 4
	mov	al, [bp+@@cfg.CFG_rank]
	mov	es:[bx+resident_t.rank], al
	mov	al, [bp+@@cfg.lives]
	mov	es:[bx+resident_t.cfg_lives], al
	mov	al, [bp+@@cfg.bombs]
	mov	es:[bx+resident_t.cfg_bombs], al
	mov	al, [bp+@@cfg.CFG_bgm_mode]
	mov	es:[bx+resident_t.bgm_mode], al
	mov	al, [bp+@@cfg.CFG_se_mode]
	mov	es:[bx+resident_t.se_mode], al
	mov	al, [bp+@@cfg.CFG_turbo_mode]
	mov	es:[bx+resident_t.turbo_mode], al
endif
	cmp	es:[bx+resident_t.cfg_lives], CFG_LIVES_MAX
	ja	short @@lives_reset
	cmp	es:[bx+resident_t.cfg_lives], 0
	jnz	short @@bombs_reset?

@@lives_reset:
	les	bx, _resident
	mov	es:[bx+resident_t.cfg_lives], CFG_LIVES_DEFAULT

@@bombs_reset?:
	les	bx, _resident
	cmp	es:[bx+resident_t.cfg_bombs], CFG_BOMBS_MAX
	jbe	short @@bgm_mode_reset?
	mov	es:[bx+resident_t.cfg_bombs], CFG_BOMBS_MAX

@@bgm_mode_reset?:
	les	bx, _resident
	cmp	es:[bx+resident_t.bgm_mode], SND_BGM_MODE_COUNT
	jb	short @@se_mode_reset?
	mov	es:[bx+resident_t.bgm_mode], SND_BGM_OFF

@@se_mode_reset?:
	les	bx, _resident
	cmp	es:[bx+resident_t.se_mode], SND_SE_MODE_COUNT
	jb	short @@ret
	mov	es:[bx+resident_t.se_mode], SND_SE_OFF

@@ret:
	leave
	retn
cfg_load	endp


public CFG_SAVE
cfg_save	proc near

@@opts	= cfg_options_t ptr -8
@@opts_sum	= byte ptr -2

	enter	8, 0
	call	file_append pascal, ds, offset _cfg_fn
	call	file_seek pascal, large 0, 0
	les	bx, _resident
	mov	al, es:[bx+resident_t.rank]
	mov	[bp+@@opts.CFG_rank], al
	mov	al, es:[bx+resident_t.cfg_lives]
	mov	[bp+@@opts.lives], al
	mov	al, es:[bx+resident_t.cfg_bombs]
	mov	[bp+@@opts.bombs], al
	mov	al, es:[bx+resident_t.bgm_mode]
	mov	[bp+@@opts.CFG_bgm_mode], al
	mov	al, es:[bx+resident_t.se_mode]
	mov	[bp+@@opts.CFG_se_mode], al
	mov	al, es:[bx+resident_t.turbo_mode]
	mov	[bp+@@opts.CFG_turbo_mode], al
	push	ss
	lea	ax, [bp+@@opts]
	push	ax
	push	size cfg_options_t
	call	file_write
	call	file_seek pascal, large offset cfg_t.opts_sum, 0
	mov	al, [bp+@@opts.CFG_rank]
	add	al, [bp+@@opts.lives]
	add	al, [bp+@@opts.bombs]
	add	al, [bp+@@opts.CFG_bgm_mode]
	add	al, [bp+@@opts.CFG_se_mode]
	add	al, [bp+@@opts.CFG_turbo_mode]
	mov	[bp+@@opts_sum], al
	push	ss
	lea	ax, [bp+@@opts_sum]
	push	ax
	push	byte
	call	file_write
	call	file_close
	leave
	retn
cfg_save	endp


public CFG_SAVE_EXIT
cfg_save_exit	proc near

@@cfg	= cfg_t ptr -(size cfg_t)

	enter	(size cfg_t), 0
	lea	ax, [bp+@@cfg]
	push	ss
	push	ax
	push	ds
	push	offset _cfg_empty
	mov	cx, size cfg_t
	call	SCOPY@
	call	file_append pascal, ds, offset _cfg_fn
	call	file_seek pascal, large 0, 0
	les	bx, _resident
	mov	al, es:[bx+resident_t.rank]
	mov	[bp+@@cfg.CFG_rank], al
	mov	al, es:[bx+resident_t.cfg_lives]
	mov	[bp+@@cfg.lives], al
	mov	al, es:[bx+resident_t.cfg_bombs]
	mov	[bp+@@cfg.bombs], al
	mov	al, es:[bx+resident_t.bgm_mode]
	mov	[bp+@@cfg.CFG_bgm_mode], al
	mov	al, es:[bx+resident_t.se_mode]
	mov	[bp+@@cfg.CFG_se_mode], al
	mov	al, es:[bx+resident_t.turbo_mode]
	mov	[bp+@@cfg.CFG_turbo_mode], al
	mov	al, [bp+@@cfg.CFG_rank]
	add	al, [bp+@@cfg.lives]
	add	al, [bp+@@cfg.bombs]
	add	al, [bp+@@cfg.CFG_bgm_mode]
	add	al, [bp+@@cfg.CFG_se_mode]
	add	al, [bp+@@cfg.CFG_turbo_mode]
	mov	[bp+@@cfg.opts_sum], al
	push	ss
	lea	ax, [bp+@@cfg]
	push	ax
	push	size cfg_t
	call	file_write
	call	file_close
	leave
	retn
cfg_save_exit	endp

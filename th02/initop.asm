; (only covering TH03 and above)
public _game_init_op
_game_init_op	proc far

@@pf_fn	= dword	ptr  6

if GAME ge 4
PARAS equ <_mem_assign_paras>
else
PARAS = MEM_ASSIGN_PARAS_OP
endif

	push	bp
	mov	bp, sp
	call	mem_assign_dos pascal, PARAS
	or	ax, ax
	jz	short @@assign_success
	mov	ax, 1
	pop	bp
	retf

@@assign_success:
if GAME le 4
	nopcall	_vram_planes_set
endif
	call	graph_start
	graph_accesspage 1
	call	graph_clear
	graph_accesspage 0
	call	graph_clear
	graph_accesspage 0
	graph_showpage al
if GAME ge 4
	mov	bbufsiz, 2000h
endif
	call	vsync_start
	call	key_beep_off
	call	text_systemline_hide
	call	text_cursor_hide
	call	egc_start
if GAME eq 3
	call	js_start
	call	pfstart pascal, large [bp+@@pf_fn]
else
	call	js_start
	les	bx, [bp+@@pf_fn]
	cmp	byte ptr es:[bx], 0
	jz	short @@no_pf
	call	pfstart pascal, word ptr [bp+@@pf_fn+2], bx

@@no_pf:
	call	bgm_init pascal, 1024
endif
	xor	ax, ax
	pop	bp
	retf
_game_init_op	endp

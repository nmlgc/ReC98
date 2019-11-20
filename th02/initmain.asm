; (only covering TH03 and above)
public GAME_INIT_MAIN
game_init_main	proc far

@@pf_fn		= dword	ptr  6

if GAME ge 4
PARAS equ <_mem_assign_paras>
else
PARAS = MEM_ASSIGN_PARAS_MAIN
endif

	push	bp
	mov	bp, sp
	call	mem_assign_dos pascal, PARAS
	or	ax, ax
	jz	short @@assign_success
	mov	ax, 1
	pop	bp
if GAME ge 3
	retf	4
else
	retf
endif
; ---------------------------------------------------------------------------

@@assign_success:
if GAME ge 4
	mov		bbufsiz, 1000h
endif
if GAME le 4
	nopcall	vram_planes_set
endif
	call	vsync_start
	call	egc_start
	call	graph_400line
	call	js_start
	call	pfstart pascal, large [bp+@@pf_fn]
if GAME ge 4
	call	bgm_init pascal, 2048
endif
	xor	ax, ax
	pop	bp
if GAME ge 3
	retf	4
else
	retf
endif
game_init_main	endp

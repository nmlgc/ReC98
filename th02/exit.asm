public GAME_EXIT
game_exit	proc far
	push	bp
	mov	bp, sp
	call	pfend
	graph_accesspage 1
	call	graph_clear
	graph_accesspage 0
	call	graph_clear
	graph_accesspage 0
	graph_showpage al
if GAME ge 4
	call	mem_unassign
	call	vsync_end
else
	call	vsync_end
	call	mem_unassign
endif
	call	text_clear
if GAME ge 3
	call	js_end
endif
	call	egc_start
if GAME ge 4
	call	bgm_finish
endif
	pop	bp
	retf
game_exit	endp

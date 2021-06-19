public BOSS_BACKDROP_RENDER
boss_backdrop_render	proc near

@@color	= byte ptr  4
@@y    	= word ptr  6
@@x    	= word ptr  8

	push	bp
	mov	bp, sp
	call	cdg_put_noalpha_8 pascal, [bp+@@x], [bp+@@y], CDG_BG_BOSS
	call	grcg_setmode_tdw
	mov	ah, [bp+@@color]
	call	_grcg_setcolor_direct_seg1_raw
	call	_boss_backdrop_colorfill
	GRCG_OFF_CLOBBERING dx
	pop	bp
	retn	6
boss_backdrop_render	endp

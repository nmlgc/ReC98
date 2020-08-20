; Renders the boss battle background image at the given position, surrounded
; by the given background [color].

; void pascal near boss_backdrop_render(screen_x_t left, screen_y_t top, uint4_t color);
public BOSS_BACKDROP_RENDER
boss_backdrop_render	proc near

@@color	= byte ptr  4
@@y    	= word ptr  6
@@x    	= word ptr  8

	push	bp
	mov	bp, sp
	call	cdg_put_noalpha pascal, [bp+@@x], [bp+@@y], 16
	call	grcg_setmode_tdw
	mov	ah, [bp+@@color]
	call	_grcg_setcolor_direct_seg1_raw
	call	_boss_backdrop_colorfill
	GRCG_OFF_CLOBBERING dx
	pop	bp
	retn	6
boss_backdrop_render	endp

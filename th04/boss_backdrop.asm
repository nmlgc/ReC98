; Renders the boss battle background image at the given position, surrounded
; by the given background [color].

; void boss_backdrop_render(int x, int y, char color)
public _boss_backdrop_render
_boss_backdrop_render	proc near

@@color	= byte ptr  4
@@y    	= word ptr  6
@@x    	= word ptr  8

	push	bp
	mov	bp, sp
	call	cdg_put_noalpha pascal, [bp+@@x], [bp+@@y], 16
	call	_grcg_setmode_tdw
	mov	ah, [bp+@@color]
	call	_grcg_setcolor_direct_noint_1
	call	_boss_backdrop_colorfill
	GRCG_OFF_CLOBBERING dx
	pop	bp
	retn	6
_boss_backdrop_render	endp

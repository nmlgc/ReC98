	@nopoly_B_snap$qv procdesc near
	@nopoly_B_free$qv procdesc near
	@nopoly_B_put$qv procdesc near
	@polygons_update_and_render$qv procdesc near

public MUSIC_FLIP
music_flip	proc near
	push	bp
	mov	bp, sp
	call	@nopoly_B_put$qv
if GAME eq 5
	call	@piano_render$qv
endif
	call	grcg_setcolor pascal, ((GC_RMW or GC_B) shl 16) + V_WHITE
	call	@polygons_update_and_render$qv
if GAME ge 4
	GRCG_OFF_CLOBBERING dx
	if GAME eq 5
		call	@frame_delay$qi pascal, 1
	endif
else
	call	grcg_off
endif
	graph_showpage _music_page
	mov	al, 1
	sub	al, _music_page
	mov	_music_page, al
	graph_accesspage al
if GAME le 4
	call	@frame_delay_2$qi pascal, 1
endif
	pop	bp
	retn
music_flip	endp

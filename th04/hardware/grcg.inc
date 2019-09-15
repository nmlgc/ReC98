; Redefined versions of master.lib's grcg_setmode() and grcg_setcolor().

GRCG_SETMODE_RMW_DEF macro instance
	; void pascal near grcg_setmode_rmw(void);
	public GRCG_SETMODE_RMW_&instance
	grcg_setmode_rmw_&instance	proc near
		GRCG_SETMODE_VIA_MOV al, GC_RMW
		ret
	grcg_setmode_rmw_&instance	endp
		nop
endm

GRCG_SETCOLOR_DIRECT_NOINT_DEF macro instance
	; Takes the GC_* color parameter in AH.

	; void pascal near grcg_setcolor_direct_noint(void);
	public GRCG_SETCOLOR_DIRECT_NOINT_&instance
	grcg_setcolor_direct_noint_&instance	proc near
		cli
		GRCG_SETCOLOR_DIRECT_CLOBBERING dx, ah
		sti
		ret
	grcg_setcolor_direct_noint_&instance	endp
endm

; Convenience macro to prepare ES:DI.
GRCG_FILL_PLAYFIELD_ROWS	macro y:req, num_rows:req, scratch_sgm:=<ax>
	mov	scratch_sgm, GRAM_400 + (((y + PLAYFIELD_Y) * ROW_SIZE) shr 4)
	mov	es, scratch_sgm
	mov	di, ((num_rows - 1) * ROW_SIZE) + PLAYFIELD_VRAM_X
	call	_grcg_fill_playfield_rows
endm

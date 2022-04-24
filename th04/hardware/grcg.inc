GRCG_SETCOLOR_DIRECT_DEF macro sgm
	public _grcg_setcolor_direct_seg&sgm&_raw
	_grcg_setcolor_direct_seg&sgm&_raw	proc near
		cli
		mov	dx, 7Eh
		rept 4
			shr	ah, 1
			sbb	al, al
			out	dx, al
		endm
		sti
		ret
	_grcg_setcolor_direct_seg&sgm&_raw	endp
endm

; Convenience macro to prepare ES:DI.
GRCG_FILL_PLAYFIELD_ROWS	macro y:req, num_rows:req, scratch_sgm:=<ax>
	mov	scratch_sgm, GRAM_400 + (((y + PLAYFIELD_TOP) * ROW_SIZE) shr 4)
	mov	es, scratch_sgm
	mov	di, ((num_rows - 1) * ROW_SIZE) + PLAYFIELD_VRAM_LEFT
	call	_grcg_fill_playfield_rows
endm

; PI-related macros. Need to be in a separate file because TASM doesn't seem
; to like macro definitions inside segments...

freePISlotLarge	macro slot
	push	ds
	push	offset _pi_headers + (slot * size PiHeader)
	push	large [_pi_buffers + (slot * dPtrSize)]
	call	graph_pi_free
endm

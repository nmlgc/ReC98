; PI-related macros. Need to be in a separate file because TASM doesn't seem
; to like macro definitions inside segments...

freePISlot	macro slot
	push	ds
	push	offset _pi_slot_headers + (slot * size PiHeader)
	push	word ptr _pi_slot_buffers + (slot * dPtrSize) + 2
	push	word ptr _pi_slot_buffers + (slot * dPtrSize)
	call	graph_pi_free
endm

freePISlotLarge	macro slot
	push	ds
	push	offset _pi_slot_headers + (slot * size PiHeader)
	push	large [_pi_slot_buffers + (slot * dPtrSize)]
	call	graph_pi_free
endm

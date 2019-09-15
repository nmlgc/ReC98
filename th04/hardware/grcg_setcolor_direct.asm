; Takes the GC_* color parameter in AH.

; void pascal near grcg_setcolor_direct(void);
public GRCG_SETCOLOR_DIRECT
grcg_setcolor_direct	proc near
	GRCG_SETCOLOR_DIRECT_INLINED ah
	ret
grcg_setcolor_direct	endp
	even

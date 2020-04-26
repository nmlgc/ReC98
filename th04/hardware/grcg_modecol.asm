GRCG_SETMODE_RMW_DEF 1

public GRCG_SETMODE_TDW
grcg_setmode_tdw	proc near
	GRCG_SETMODE_VIA_MOV al, GC_TDW
	ret
grcg_setmode_tdw	endp
	even

GRCG_SETCOLOR_DIRECT_DEF 1

GRCG_SETMODE_RMW_DEF 1

; void grcg_setmode_tdw(void)
public _grcg_setmode_tdw
_grcg_setmode_tdw	proc near
	GRCG_SETMODE_VIA_MOV al, GC_TDW
	ret
_grcg_setmode_tdw	endp
	even

GRCG_SETCOLOR_DIRECT_NOINT_DEF 1

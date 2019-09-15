GRCG_SETMODE_RMW_DEF 1

; void pascal near grcg_setmode_tdw(void);
public GRCG_SETMODE_TDW
grcg_setmode_tdw	proc near
	GRCG_SETMODE_VIA_MOV al, GC_TDW
	ret
grcg_setmode_tdw	endp
	even

GRCG_SETCOLOR_DIRECT_NOINT_DEF 1

public _grcg_setmode_rmw_seg1
_grcg_setmode_rmw_seg1 proc near
	GRCG_SETMODE_VIA_MOV al, GC_RMW
	ret
_grcg_setmode_rmw_seg1 endp
	even

public _grcg_setmode_tdw
_grcg_setmode_tdw	proc near
	GRCG_SETMODE_VIA_MOV al, GC_TDW
	ret
_grcg_setmode_tdw	endp
	even

GRCG_SETCOLOR_DIRECT_DEF 1

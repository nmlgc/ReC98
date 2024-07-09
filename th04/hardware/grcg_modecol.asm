public @grcg_setmode_rmw$qv
@grcg_setmode_rmw$qv proc near
	GRCG_SETMODE_VIA_MOV al, GC_RMW
	ret
@grcg_setmode_rmw$qv endp
	even

public @grcg_setmode_tdw$qv
@grcg_setmode_tdw$qv proc near
	GRCG_SETMODE_VIA_MOV al, GC_TDW
	ret
@grcg_setmode_tdw$qv endp
	even

GRCG_SETCOLOR_DIRECT_DEF

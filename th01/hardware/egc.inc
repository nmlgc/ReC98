; ReC98
; Inlined EGC code

graph_mode_change macro enable_or_disable:req
	mov	al, (6 + enable_or_disable)
	out	6Ah, al
endm

graph_mode_egc macro enable_or_disable:req
	mov	al, (4 + enable_or_disable)
	out	6Ah, al
endm

graph_egc macro enable_or_disable:req
	graph_mode_change	1
	graph_mode_egc	enable_or_disable
	graph_mode_change	0
endm

EGC_SETUP_COPY macro
	outw2	EGC_ACTIVEPLANEREG, 0FFF0h
	egc_selectpat
	egc_setrop	EGC_COMPAREREAD or EGC_WS_PATREG or EGC_RL_MEMREAD
	outw2	EGC_MASKREG, 0FFFFh
	outw2	EGC_ADDRRESSREG, 0
	outw2	EGC_BITLENGTHREG, 0Fh
endm

; Varieties of egc_on() + EGC_SETUP_COPY.
EGC_START_COPY_DEF macro instance, distance
	; void egc_start_copy();
	public egc_start_copy_&instance
	egc_start_copy_&instance	proc distance
		push	bp
		mov	bp, sp
		call	egc_on
		EGC_SETUP_COPY
		pop	bp
		ret
	egc_start_copy_&instance	endp
endm

EGC_START_COPY_INLINED macro
	GRCG_OFF_VIA_MOV al
	graph_mode_change	1
	graph_mode_egc	1
	GRCG_SETMODE_VIA_MOV al, GC_TDW
	graph_mode_change	0
	EGC_SETUP_COPY
endm

; ReC98
; Inlined EGC code

; Requires the EGC to have been activated before, via egc_on() or equivalent
; inlined writes to the EGC ports.
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
	mov	al, 7
	out	6Ah, al
	mov	al, 5
	out	6Ah, al
	GRCG_SETMODE_VIA_MOV al, GC_TDW
	mov	al, 6
	out	6Ah, al
	EGC_SETUP_COPY
endm

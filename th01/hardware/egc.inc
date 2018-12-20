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

; ReC98
; Main include file

locals

include libs/BorlandC/RULES.ASI
include libs/master.lib/func.inc
include libs/master.lib/super.inc

nopcall macro func
if LDATA
	nop	; PC-98 Touhou compatibility
endif
	call func
endm

pushSS_ macro
if LDATA
	push ss
endif
endm

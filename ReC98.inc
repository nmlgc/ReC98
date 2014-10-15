; ReC98
; Main include file

locals

include libs/BorlandC/RULES.ASI
include libs/BorlandC/doserror.inc
include libs/BorlandC/fcntl.inc
include libs/BorlandC/stdio.inc
include libs/BorlandC/sys/stat.inc
include libs/master.lib/func.inc
include libs/master.lib/super.inc
include libs/master.lib/bgm.inc
include libs/master.lib/pf.inc
include libs/master.lib/clip.inc

; Manually put dseg into DGROUP if we're not tiny. The alternative, renaming
; dseg to _DATA, unfortunately doesn't work because that segment is enforced
; to be 32-bit after specifying .386...
if @model ne 1
	DGROUP group dseg
endif

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

; ReC98
; Main include file

locals

include libs/BorlandC/RULES.ASI
include libs/BorlandC/ctype.inc
include libs/BorlandC/dos.inc
include libs/BorlandC/doserror.inc
include libs/BorlandC/errno.inc
include libs/BorlandC/fcntl.inc
include libs/BorlandC/stdio.inc
include libs/BorlandC/_printf.inc
include libs/BorlandC/sys/stat.inc
include libs/master.lib/func.inc
include libs/master.lib/super.inc
include libs/master.lib/bgm.inc
include libs/master.lib/pf.inc
include libs/master.lib/clip.inc
include libs/master.lib/macros.inc
include libs/kaja/kaja.inc
include th02/formats/pi_slots.inc

nopcall macro func
if LDATA
	nop	; PC-98 Touhou compatibility
endif
	call func
endm

; Avoids specifying both segment and offset of a function. Too bad that it
; still doesn't cause TASM to require [func] to be a valid identifier.
setfarfp macro farfp, func
	mov word ptr farfp+2, seg func
	mov word ptr farfp, offset func
endm

pushSS_ macro
if LDATA
	push ss
endif
endm

popCX_ macro
if LDATA
	pop cx
endif
endm

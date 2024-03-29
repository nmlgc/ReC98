; ReC98
; Main include file

locals

LDATA = @DataSize
dPtrSize = (@DataSize + 1) * 2

include libs/master.lib/func.inc
include libs/master.lib/super.inc
include libs/master.lib/bgm.inc
include libs/master.lib/pf.inc
include libs/master.lib/clip.inc
include libs/master.lib/macros.inc
include libs/kaja/kaja.inc
include twobyte.inc
include pc98.inc
include th01/hardware/egc.inc
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

ifdef BINARY
	; See decomp.hpp
	public _address_0
	_address_0 = 0
endif

; master.lib extensions
; ---------------------
; super_roll_put_1plane() plane_put constants
PLANE_PUT  = 0FF00h or GC_RMW
; ---------------------

; Rank definitions
RANK_EASY = 0
RANK_NORMAL = 1
RANK_HARD = 2
RANK_LUNATIC = 3
RANK_EXTRA = 4
RANK_COUNT = 5

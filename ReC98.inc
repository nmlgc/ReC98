; ReC98
; Main include file

; Order segments alphabetically.
; Rather ugly workaround to prevent the automatically generated code segment
; for the large model (filename_TEXT) from enforcing its word alignment
; between _TEXT and the first code segment even though we never emit anything
; into it.
; However, this merely pushes filename_TEXT before _TEXTC, and therefore
; breaks another group of files. In these, we actually have to rename that
; automatically generated code segment to one that is expected to have word
; alignment.
.alpha

locals

LDATA = @DataSize
dPtrSize = (@DataSize + 1) * 2

; ctype character classes
_IS_DIG = 02h
_IS_CTL = 20h

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

; See decomp.hpp
public _address_0
_address_0 = 0

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
RANK_DEFAULT = -1

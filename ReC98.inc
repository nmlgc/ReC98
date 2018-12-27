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

include libs/BorlandC/RULES.ASI
include libs/BorlandC/doserror.inc
include libs/BorlandC/errno.inc
include libs/BorlandC/stdio.inc
include libs/master.lib/func.inc
include libs/master.lib/super.inc
include libs/master.lib/bgm.inc
include libs/master.lib/pf.inc
include libs/master.lib/clip.inc
include libs/master.lib/macros.inc
include libs/kaja/kaja.inc
include th01/hardware/egc.inc
include th02/formats/pi_slots.inc
include th03/formats/cdg.inc

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

twobyte_t struc
	lo	db ?
	hi	db ?
twobyte_t ends

RES_X = 640
RES_Y = 400

PLAYFIELD_X = 32
PLAYFIELD_Y = 16
PLAYFIELD_W = 384
PLAYFIELD_H = 368
PLAYFIELD_VRAM_X = PLAYFIELD_X / 8
PLAYFIELD_VRAM_W = PLAYFIELD_W / 8

ROW_SIZE = (RES_X / 8)

TILE_W = 16
TILE_H = 16
TILES_Y = 1 + (PLAYFIELD_H / TILE_H) + 1
TILES_X = (PLAYFIELD_W / TILE_W)

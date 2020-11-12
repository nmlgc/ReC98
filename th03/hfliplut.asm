	extern _hflip_lut:byte:256

; The original function layouts unfortunately require this one to be placed at
; a word-aligned address, which can't be achieved from Turbo C++ alone :( Oh
; well, its decompilation would have been a mess anyway.
SHARED	segment word public 'CODE' use16
	assume cs:SHARED
include th03/formats/hfliplut.asm
SHARED ends

	end

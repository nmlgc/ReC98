	extern _hflip_lut:byte:256

; Would have been decompilable into a mess.
SHARED	segment word public 'CODE' use16
	assume cs:SHARED
include th03/formats/hfliplut.asm
SHARED ends

	end

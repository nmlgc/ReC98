; Function numbers for the PMD and MMD drivers, according to PMDDATA.DOC and
; MMDFUNC.DOC. Functions prefixed with KAJA are available in both drivers.
; Only includes functions that are actually used in the games.

KAJA_SONG_PLAY equ 00h
KAJA_SONG_STOP equ 01h
KAJA_SONG_FADE equ 02h
KAJA_GET_SONG_MEASURE equ 05h
KAJA_GET_SONG_ADDRESS equ 06h
KAJA_GET_VOLUME equ 08h
PMD_GET_DRIVER_VERSION equ 09h
PMD_GET_SE_ADDRESS equ 0Bh
PMD_SE_PLAY equ 0Ch
PMD_GET_WORKAREA_ADDRESS equ 10h

kajacall	macro func, param := <0>
	call	snd_kaja_interrupt pascal, (func shl 8) or (param and 0ffh)
endm

MMD_TICKS_PER_QUARTER_NOTE = 48

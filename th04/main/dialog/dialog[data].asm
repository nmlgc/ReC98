DIALOG_BOX_W = 320
DIALOG_BOX_H = 48
DIALOG_BOX_TILE_W = 16
DIALOG_BOX_TILE_H = 4
DIALOG_BOX_TILE_COUNT = 3

DIALOG_BOX_TILE_VRAM_W = (DIALOG_BOX_TILE_W / 8)
DIALOG_BOX_VRAM_W = (DIALOG_BOX_W / 8)

DIALOG_SIDE_PLAYCHAR = 0
DIALOG_SIDE_BOSS = 1

public _DIALOG_BOX_TILES
_DIALOG_BOX_TILES label word
; 0
	dw 1000100010001000b
	dw  100010001000100b
	dw   10001000100010b
	dw    1000100010001b
; 1
	dw 1100110011001100b
	dw  110011001100110b
	dw   11001100110011b
	dw 1001100110011001b
; 2
	dw 1110111011101110b
	dw  111011101110111b
	dw 1011101110111011b
	dw 1101110111011101b

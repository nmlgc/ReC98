PELLET_BOTTOM_H = 4

public _sPELLET_BOTTOM
label _sPELLET_BOTTOM byte
	; x + 0
	db        1b,00000000b
	db 10000011b,00000000b
	db  1111110b,00000000b
	db   111100b,00000000b
	; x + 1
	db        0b,10000000b
	db  1000001b,10000000b
	db   111111b,00000000b
	db    11110b,00000000b
	; x + 2
	db        0b,01000000b
	db   100000b,11000000b
	db    11111b,10000000b
	db     1111b,00000000b
	; x + 3
	db        0b,00100000b
	db    10000b,01100000b
	db     1111b,11000000b
	db      111b,10000000b
	; x + 4
	db        0b,00010000b
	db     1000b,00110000b
	db      111b,11100000b
	db       11b,11000000b
	; x + 5
	db        0b,00001000b
	db      100b,00011000b
	db       11b,11110000b
	db        1b,11100000b
	; x + 6
	db        0b,00000100b
	db       10b,00001100b
	db        1b,11111000b
	db        0b,11110000b
	; x + 7
	db        0b,00000010b
	db        1b,00000110b
	db        0b,11111100b
	db        0b,01111000b

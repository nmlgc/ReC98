label _sPELLET_DECAY_0
; x + 0
	db    11000b,       0b
	db   100100b,       0b
	db  1000010b,       0b
	db 10000001b,       0b
	db 10000001b,       0b
	db  1000010b,       0b
	db   100100b,       0b
	db    11000b,       0b
; x + 1
	db     1100b,       0b
	db    10010b,       0b
	db   100001b,       0b
	db  1000000b,10000000b
	db  1000000b,10000000b
	db   100001b,       0b
	db    10010b,       0b
	db     1100b,       0b
; x + 2
	db      110b,       0b
	db     1001b,       0b
	db    10000b,10000000b
	db   100000b,01000000b
	db   100000b,01000000b
	db    10000b,10000000b
	db     1001b,       0b
	db      110b,       0b
; x + 3
	db       11b,       0b
	db      100b,10000000b
	db     1000b,01000000b
	db    10000b,00100000b
	db    10000b,00100000b
	db     1000b,01000000b
	db      100b,10000000b
	db       11b,       0b
; x + 4
	db        1b,10000000b
	db       10b,01000000b
	db      100b,00100000b
	db     1000b,00010000b
	db     1000b,00010000b
	db      100b,00100000b
	db       10b,01000000b
	db        1b,10000000b
; x + 5
	db        0b,11000000b
	db        1b,00100000b
	db       10b,00010000b
	db      100b,00001000b
	db      100b,00001000b
	db       10b,00010000b
	db        1b,00100000b
	db        0b,11000000b
; x + 6
	db        0b,01100000b
	db        0b,10010000b
	db        1b,00001000b
	db       10b,00000100b
	db       10b,00000100b
	db        1b,00001000b
	db        0b,10010000b
	db        0b,01100000b
; x + 7
	db        0b,00110000b
	db        0b,01001000b
	db        0b,10000100b
	db        1b,00000010b
	db        1b,00000010b
	db        0b,10000100b
	db        0b,01001000b
	db        0b,00110000b

label _sPELLET_DECAY_1
; x + 0
	db        0b,       0b
	db   100100b,       0b
	db  1000010b,       0b
	db        0b,       0b
	db        0b,       0b
	db  1000010b,       0b
	db   100100b,       0b
	db        0b,       0b
; x + 1
	db        0b,       0b
	db    10010b,       0b
	db   100001b,       0b
	db        0b,       0b
	db        0b,       0b
	db   100001b,       0b
	db    10010b,       0b
	db        0b,       0b
; x + 2
	db        0b,       0b
	db     1001b,       0b
	db    10000b,10000000b
	db        0b,       0b
	db        0b,       0b
	db    10000b,10000000b
	db     1001b,       0b
	db        0b,       0b
; x + 3
	db        0b,       0b
	db      100b,10000000b
	db     1000b,01000000b
	db        0b,       0b
	db        0b,       0b
	db     1000b,01000000b
	db      100b,10000000b
	db        0b,       0b
; x + 4
	db        0b,       0b
	db       10b,01000000b
	db      100b,00100000b
	db        0b,       0b
	db        0b,       0b
	db      100b,00100000b
	db       10b,01000000b
	db        0b,       0b
; x + 5
	db        0b,       0b
	db        1b,00100000b
	db       10b,00010000b
	db        0b,       0b
	db        0b,       0b
	db       10b,00010000b
	db        1b,00100000b
	db        0b,       0b
; x + 6
	db        0b,       0b
	db        0b,10010000b
	db        1b,00001000b
	db        0b,       0b
	db        0b,       0b
	db        1b,00001000b
	db        0b,10010000b
	db        0b,       0b
; x + 7
	db        0b,       0b
	db        0b,01001000b
	db        0b,10000100b
	db        0b,       0b
	db        0b,       0b
	db        0b,10000100b
	db        0b,01001000b
	db        0b,       0b

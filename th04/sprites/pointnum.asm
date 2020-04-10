POINTNUM_W = 8
POINTNUM_H = 8

POINTNUM = 0
POINTNUM_TIMES = 10
POINTNUM_TIMES_2 = 11

public _sPOINTNUMS
label _sPOINTNUMS byte
; 0
	db        0b,       0b
	db   111000b,       0b
	db  1000100b,       0b
	db 10000010b,       0b
	db 10000010b,       0b
	db 10000010b,       0b
	db  1000100b,       0b
	db   111000b,       0b
	db        0b,       0b
	db    11100b,       0b
	db   100010b,       0b
	db  1000001b,       0b
	db  1000001b,       0b
	db  1000001b,       0b
	db   100010b,       0b
	db    11100b,       0b
	db        0b,       0b
	db     1110b,       0b
	db    10001b,       0b
	db   100000b,10000000b
	db   100000b,10000000b
	db   100000b,10000000b
	db    10001b,       0b
	db     1110b,       0b
	db        0b,       0b
	db      111b,       0b
	db     1000b,10000000b
	db    10000b, 1000000b
	db    10000b, 1000000b
	db    10000b, 1000000b
	db     1000b,10000000b
	db      111b,       0b
	db        0b,       0b
	db       11b,10000000b
	db      100b, 1000000b
	db     1000b,  100000b
	db     1000b,  100000b
	db     1000b,  100000b
	db      100b, 1000000b
	db       11b,10000000b
	db        0b,       0b
	db        1b,11000000b
	db       10b,  100000b
	db      100b,   10000b
	db      100b,   10000b
	db      100b,   10000b
	db       10b,  100000b
	db        1b,11000000b
	db        0b,       0b
	db        0b,11100000b
	db        1b,   10000b
	db       10b,    1000b
	db       10b,    1000b
	db       10b,    1000b
	db        1b,   10000b
	db        0b,11100000b
	db        0b,       0b
	db        0b, 1110000b
	db        0b,10001000b
	db        1b,     100b
	db        1b,     100b
	db        1b,     100b
	db        0b,10001000b
	db        0b, 1110000b
; 1
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db      110b,       0b
	db  1111110b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db       11b,       0b
	db   111111b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        1b,10000000b
	db    11111b,10000000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,11000000b
	db     1111b,11000000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b, 1100000b
	db      111b,11100000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,  110000b
	db       11b,11110000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,   11000b
	db        1b,11111000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,    1100b
	db        0b,11111100b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
; 2
	db        0b,       0b
	db     1100b,       0b
	db   111100b,       0b
	db        0b,       0b
	db        0b,       0b
	db      110b,       0b
	db  1111110b,       0b
	db        0b,       0b
	db        0b,       0b
	db      110b,       0b
	db    11110b,       0b
	db        0b,       0b
	db        0b,       0b
	db       11b,       0b
	db   111111b,       0b
	db        0b,       0b
	db        0b,       0b
	db       11b,       0b
	db     1111b,       0b
	db        0b,       0b
	db        0b,       0b
	db        1b,10000000b
	db    11111b,10000000b
	db        0b,       0b
	db        0b,       0b
	db        1b,10000000b
	db      111b,10000000b
	db        0b,       0b
	db        0b,       0b
	db        0b,11000000b
	db     1111b,11000000b
	db        0b,       0b
	db        0b,       0b
	db        0b,11000000b
	db       11b,11000000b
	db        0b,       0b
	db        0b,       0b
	db        0b, 1100000b
	db      111b,11100000b
	db        0b,       0b
	db        0b,       0b
	db        0b, 1100000b
	db        1b,11100000b
	db        0b,       0b
	db        0b,       0b
	db        0b,  110000b
	db       11b,11110000b
	db        0b,       0b
	db        0b,       0b
	db        0b,  110000b
	db        0b,11110000b
	db        0b,       0b
	db        0b,       0b
	db        0b,   11000b
	db        1b,11111000b
	db        0b,       0b
	db        0b,       0b
	db        0b,   11000b
	db        0b, 1111000b
	db        0b,       0b
	db        0b,       0b
	db        0b,    1100b
	db        0b,11111100b
	db        0b,       0b
; 3
	db      110b,       0b
	db  1111110b,       0b
	db        0b,       0b
	db      110b,       0b
	db   111100b,       0b
	db        0b,       0b
	db       11b,       0b
	db 11111111b,       0b
	db       11b,       0b
	db   111111b,       0b
	db        0b,       0b
	db       11b,       0b
	db    11110b,       0b
	db        0b,       0b
	db        1b,10000000b
	db  1111111b,10000000b
	db        1b,10000000b
	db    11111b,10000000b
	db        0b,       0b
	db        1b,10000000b
	db     1111b,       0b
	db        0b,       0b
	db        0b,11000000b
	db   111111b,11000000b
	db        0b,11000000b
	db     1111b,11000000b
	db        0b,       0b
	db        0b,11000000b
	db      111b,10000000b
	db        0b,       0b
	db        0b, 1100000b
	db    11111b,11100000b
	db        0b, 1100000b
	db      111b,11100000b
	db        0b,       0b
	db        0b, 1100000b
	db       11b,11000000b
	db        0b,       0b
	db        0b,  110000b
	db     1111b,11110000b
	db        0b,  110000b
	db       11b,11110000b
	db        0b,       0b
	db        0b,  110000b
	db        1b,11100000b
	db        0b,       0b
	db        0b,   11000b
	db      111b,11111000b
	db        0b,   11000b
	db        1b,11111000b
	db        0b,       0b
	db        0b,   11000b
	db        0b,11110000b
	db        0b,       0b
	db        0b,    1100b
	db       11b,11111100b
	db        0b,    1100b
	db        0b,11111100b
	db        0b,       0b
	db        0b,    1100b
	db        0b, 1111000b
	db        0b,       0b
	db        0b,     110b
	db        1b,11111110b
; 4
	db        0b,       0b
	db  1111110b,       0b
	db  1011010b,       0b
	db  1111110b,       0b
	db  1000010b,       0b
	db  1000010b,       0b
	db  1111110b,       0b
	db        0b,       0b
	db        0b,       0b
	db   111111b,       0b
	db   101101b,       0b
	db   111111b,       0b
	db   100001b,       0b
	db   100001b,       0b
	db   111111b,       0b
	db        0b,       0b
	db        0b,       0b
	db    11111b,10000000b
	db    10110b,10000000b
	db    11111b,10000000b
	db    10000b,10000000b
	db    10000b,10000000b
	db    11111b,10000000b
	db        0b,       0b
	db        0b,       0b
	db     1111b,11000000b
	db     1011b, 1000000b
	db     1111b,11000000b
	db     1000b, 1000000b
	db     1000b, 1000000b
	db     1111b,11000000b
	db        0b,       0b
	db        0b,       0b
	db      111b,11100000b
	db      101b,10100000b
	db      111b,11100000b
	db      100b,  100000b
	db      100b,  100000b
	db      111b,11100000b
	db        0b,       0b
	db        0b,       0b
	db       11b,11110000b
	db       10b,11010000b
	db       11b,11110000b
	db       10b,   10000b
	db       10b,   10000b
	db       11b,11110000b
	db        0b,       0b
	db        0b,       0b
	db        1b,11111000b
	db        1b, 1101000b
	db        1b,11111000b
	db        1b,    1000b
	db        1b,    1000b
	db        1b,11111000b
	db        0b,       0b
	db        0b,       0b
	db        0b,11111100b
	db        0b,10110100b
	db        0b,11111100b
	db        0b,10000100b
	db        0b,10000100b
	db        0b,11111100b
	db        0b,       0b
; 5
	db        0b,       0b
	db  1111110b,       0b
	db     1000b,       0b
	db    10000b,       0b
	db  1111100b,       0b
	db   100100b,       0b
	db  1000100b,       0b
	db 11111111b,       0b
	db        0b,       0b
	db   111111b,       0b
	db      100b,       0b
	db     1000b,       0b
	db   111110b,       0b
	db    10010b,       0b
	db   100010b,       0b
	db  1111111b,10000000b
	db        0b,       0b
	db    11111b,10000000b
	db       10b,       0b
	db      100b,       0b
	db    11111b,       0b
	db     1001b,       0b
	db    10001b,       0b
	db   111111b,11000000b
	db        0b,       0b
	db     1111b,11000000b
	db        1b,       0b
	db       10b,       0b
	db     1111b,10000000b
	db      100b,10000000b
	db     1000b,10000000b
	db    11111b,11100000b
	db        0b,       0b
	db      111b,11100000b
	db        0b,10000000b
	db        1b,       0b
	db      111b,11000000b
	db       10b, 1000000b
	db      100b, 1000000b
	db     1111b,11110000b
	db        0b,       0b
	db       11b,11110000b
	db        0b, 1000000b
	db        0b,10000000b
	db       11b,11100000b
	db        1b,  100000b
	db       10b,  100000b
	db      111b,11111000b
	db        0b,       0b
	db        1b,11111000b
	db        0b,  100000b
	db        0b, 1000000b
	db        1b,11110000b
	db        0b,10010000b
	db        1b,   10000b
	db       11b,11111100b
	db        0b,       0b
	db        0b,11111100b
	db        0b,   10000b
	db        0b,  100000b
	db        0b,11111000b
	db        0b, 1001000b
	db        0b,10001000b
	db        1b,11111110b
; 6
	db        0b,       0b
	db    11000b,       0b
	db  1111110b,       0b
	db        0b,       0b
	db        0b,       0b
	db   100100b,       0b
	db  1000010b,       0b
	db        0b,       0b
	db        0b,       0b
	db     1100b,       0b
	db   111111b,       0b
	db        0b,       0b
	db        0b,       0b
	db    10010b,       0b
	db   100001b,       0b
	db        0b,       0b
	db        0b,       0b
	db      110b,       0b
	db    11111b,10000000b
	db        0b,       0b
	db        0b,       0b
	db     1001b,       0b
	db    10000b,10000000b
	db        0b,       0b
	db        0b,       0b
	db       11b,       0b
	db     1111b,11000000b
	db        0b,       0b
	db        0b,       0b
	db      100b,10000000b
	db     1000b, 1000000b
	db        0b,       0b
	db        0b,       0b
	db        1b,10000000b
	db      111b,11100000b
	db        0b,       0b
	db        0b,       0b
	db       10b, 1000000b
	db      100b,  100000b
	db        0b,       0b
	db        0b,       0b
	db        0b,11000000b
	db       11b,11110000b
	db        0b,       0b
	db        0b,       0b
	db        1b,  100000b
	db       10b,   10000b
	db        0b,       0b
	db        0b,       0b
	db        0b, 1100000b
	db        1b,11111000b
	db        0b,       0b
	db        0b,       0b
	db        0b,10010000b
	db        1b,    1000b
	db        0b,       0b
	db        0b,       0b
	db        0b,  110000b
	db        0b,11111100b
	db        0b,       0b
	db        0b,       0b
	db        0b, 1001000b
	db        0b,10000100b
	db        0b,       0b
; 7
	db        0b,       0b
	db   100000b,       0b
	db  1111110b,       0b
	db   100000b,       0b
	db   100000b,       0b
	db   111100b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db    10000b,       0b
	db   111111b,       0b
	db    10000b,       0b
	db    10000b,       0b
	db    11110b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db     1000b,       0b
	db    11111b,10000000b
	db     1000b,       0b
	db     1000b,       0b
	db     1111b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db      100b,       0b
	db     1111b,11000000b
	db      100b,       0b
	db      100b,       0b
	db      111b,10000000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db       10b,       0b
	db      111b,11100000b
	db       10b,       0b
	db       10b,       0b
	db       11b,11000000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        1b,       0b
	db       11b,11110000b
	db        1b,       0b
	db        1b,       0b
	db        1b,11100000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,10000000b
	db        1b,11111000b
	db        0b,10000000b
	db        0b,10000000b
	db        0b,11110000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b, 1000000b
	db        0b,11111100b
	db        0b, 1000000b
	db        0b, 1000000b
	db        0b, 1111000b
	db        0b,       0b
	db        0b,       0b
; 8
	db        0b,       0b
	db      100b,       0b
	db   100100b,       0b
	db   100010b,       0b
	db  1000010b,       0b
	db  1000001b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db       10b,       0b
	db    10010b,       0b
	db    10001b,       0b
	db   100001b,       0b
	db   100000b,10000000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        1b,       0b
	db     1001b,       0b
	db     1000b,10000000b
	db    10000b,10000000b
	db    10000b, 1000000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,10000000b
	db      100b,10000000b
	db      100b, 1000000b
	db     1000b, 1000000b
	db     1000b,  100000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b, 1000000b
	db       10b, 1000000b
	db       10b,  100000b
	db      100b,  100000b
	db      100b,   10000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,  100000b
	db        1b,  100000b
	db        1b,   10000b
	db       10b,   10000b
	db       10b,    1000b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,   10000b
	db        0b,10010000b
	db        0b,10001000b
	db        1b,    1000b
	db        1b,     100b
	db        0b,       0b
	db        0b,       0b
	db        0b,       0b
	db        0b,    1000b
	db        0b, 1001000b
	db        0b, 1000100b
	db        0b,10000100b
	db        0b,10000010b
	db        0b,       0b
	db        0b,       0b
; 9
	db        0b,       0b
	db    10000b,       0b
	db   111110b,       0b
	db   100100b,       0b
	db   100110b,       0b
	db  1001010b,       0b
	db 10001110b,       0b
	db        0b,       0b
	db        0b,       0b
	db     1000b,       0b
	db    11111b,       0b
	db    10010b,       0b
	db    10011b,       0b
	db   100101b,       0b
	db  1000111b,       0b
	db        0b,       0b
	db        0b,       0b
	db      100b,       0b
	db     1111b,10000000b
	db     1001b,       0b
	db     1001b,10000000b
	db    10010b,10000000b
	db   100011b,10000000b
	db        0b,       0b
	db        0b,       0b
	db       10b,       0b
	db      111b,11000000b
	db      100b,10000000b
	db      100b,11000000b
	db     1001b, 1000000b
	db    10001b,11000000b
	db        0b,       0b
	db        0b,       0b
	db        1b,       0b
	db       11b,11100000b
	db       10b, 1000000b
	db       10b, 1100000b
	db      100b,10100000b
	db     1000b,11100000b
	db        0b,       0b
	db        0b,       0b
	db        0b,10000000b
	db        1b,11110000b
	db        1b,  100000b
	db        1b,  110000b
	db       10b, 1010000b
	db      100b, 1110000b
	db        0b,       0b
	db        0b,       0b
	db        0b, 1000000b
	db        0b,11111000b
	db        0b,10010000b
	db        0b,10011000b
	db        1b,  101000b
	db       10b,  111000b
	db        0b,       0b
	db        0b,       0b
	db        0b,  100000b
	db        0b, 1111100b
	db        0b, 1001000b
	db        0b, 1001100b
	db        0b,10010100b
	db        1b,   11100b
	db        0b,       0b
; ✕
	db 10000001b,       0b
	db  1000010b,       0b
	db   100100b,       0b
	db    11000b,       0b
	db    11000b,       0b
	db   100100b,       0b
	db  1000010b,       0b
	db 10000001b,       0b
	db  1000000b,10000000b
	db   100001b,       0b
	db    10010b,       0b
	db     1100b,       0b
	db     1100b,       0b
	db    10010b,       0b
	db   100001b,       0b
	db  1000000b,10000000b
	db   100000b, 1000000b
	db    10000b,10000000b
	db     1001b,       0b
	db      110b,       0b
	db      110b,       0b
	db     1001b,       0b
	db    10000b,10000000b
	db   100000b, 1000000b
	db    10000b,  100000b
	db     1000b, 1000000b
	db      100b,10000000b
	db       11b,       0b
	db       11b,       0b
	db      100b,10000000b
	db     1000b, 1000000b
	db    10000b,  100000b
	db     1000b,   10000b
	db      100b,  100000b
	db       10b, 1000000b
	db        1b,10000000b
	db        1b,10000000b
	db       10b, 1000000b
	db      100b,  100000b
	db     1000b,   10000b
	db      100b,    1000b
	db       10b,   10000b
	db        1b,  100000b
	db        0b,11000000b
	db        0b,11000000b
	db        1b,  100000b
	db       10b,   10000b
	db      100b,    1000b
	db       10b,     100b
	db        1b,    1000b
	db        0b,10010000b
	db        0b, 1100000b
	db        0b, 1100000b
	db        0b,10010000b
	db        1b,    1000b
	db       10b,     100b
	db        1b,      10b
	db        0b,10000100b
	db        0b, 1001000b
	db        0b,  110000b
	db        0b,  110000b
	db        0b, 1001000b
	db        0b,10000100b
	db        1b,      10b
; 2 (multiplier)
	db   111100b,       0b
	db  1000110b,       0b
	db  1000110b,       0b
	db      110b,       0b
	db   111100b,       0b
	db  1100000b,       0b
	db 11000001b,       0b
	db 11111111b,       0b
	db    11110b,       0b
	db   100011b,       0b
	db   100011b,       0b
	db       11b,       0b
	db    11110b,       0b
	db   110000b,       0b
	db  1100000b,10000000b
	db  1111111b,10000000b
	db     1111b,       0b
	db    10001b,10000000b
	db    10001b,10000000b
	db        1b,10000000b
	db     1111b,       0b
	db    11000b,       0b
	db   110000b, 1000000b
	db   111111b,11000000b
	db      111b,10000000b
	db     1000b,11000000b
	db     1000b,11000000b
	db        0b,11000000b
	db      111b,10000000b
	db     1100b,       0b
	db    11000b,  100000b
	db    11111b,11100000b
	db       11b,11000000b
	db      100b, 1100000b
	db      100b, 1100000b
	db        0b, 1100000b
	db       11b,11000000b
	db      110b,       0b
	db     1100b,   10000b
	db     1111b,11110000b
	db        1b,11100000b
	db       10b,  110000b
	db       10b,  110000b
	db        0b,  110000b
	db        1b,11100000b
	db       11b,       0b
	db      110b,    1000b
	db      111b,11111000b
	db        0b,11110000b
	db        1b,   11000b
	db        1b,   11000b
	db        0b,   11000b
	db        0b,11110000b
	db        1b,10000000b
	db       11b,     100b
	db       11b,11111100b
	db        0b, 1111000b
	db        0b,10001100b
	db        0b,10001100b
	db        0b,    1100b
	db        0b, 1111000b
	db        0b,11000000b
	db        1b,10000010b
	db        1b,11111110b

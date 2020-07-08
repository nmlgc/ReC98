; 1bpp sprite data
; ----------------
PIANO_KEYS_WHITE = 1110111011101110b

; Every 7-byte line covers two octaves.
public _PIANO_KEYS_BLACK
_PIANO_KEYS_BLACK	label byte
;     C#   D#         F#    G#   A#         C#    D#         F#    G#   A#
db 00111011b, 10000011b, 10111011b, 10000011b, 10111000b, 00111011b, 10111000b
db 00111011b, 10000011b, 10111011b, 10000011b, 10111000b, 00111011b, 10111000b
db 00111011b, 10000011b, 10111011b, 10000011b, 10111000b, 00111011b, 10111000b
db 00111011b, 10000011b, 10111011b, 10000011b, 10111000b, 00111011b, 10111000b
; ; ----------------

PIANO_LABEL_FONT_W = 8
PIANO_LABEL_FONT_H = 8

pl_F = 0
pl_M = 1
pl_1 = 2
pl_2 = 3
pl_3 = 4
pl_4 = 5
pl_5 = 6
pl_S = 7
pl_G = 8

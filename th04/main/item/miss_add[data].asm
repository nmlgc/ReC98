MISS_ITEM_COUNT = 5
MISS_FIELD_LEFT = 0
MISS_FIELD_CENTER = 1
MISS_FIELD_RIGHT = 2

public _ITEM_MISS_VELOCITIES
_ITEM_MISS_VELOCITIES	label word
; MISS_FIELD_LEFT
dw (-3 shl 4), (-3 shl 4) -  8, (-4 shl 4),     (-4 shl 4) - 8, (-5 shl 4)
dw ( 0 shl 4), ( 0 shl 4) + 12, ( 1 shl 4) + 8, ( 2 shl 4) + 4, ( 3 shl 4)

; MISS_FIELD_CENTER
dw (-3 shl 4),     (-3 shl 4) -  8, (-4 shl 4), (-3 shl 4) -  8, (-3 shl 4)
dw (-1 shl 4) - 8, ( 0 shl 4) - 12, ( 0 shl 4), ( 0 shl 4) + 12, ( 1 shl 4) + 8

; MISS_FIELD_RIGHT
dw (-3 shl 4), (-3 shl 4) -  8, (-4 shl 4),     (-4 shl 4) - 8, (-5 shl 4)
dw ( 0 shl 4), ( 0 shl 4) - 12, (-1 shl 4) - 8, (-2 shl 4) - 4, (-3 shl 4)

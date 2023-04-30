public _item_playperf_raise, _item_playperf_lower
_item_playperf_raise	db 0
_item_playperf_lower	db 0

public _ITEM_TYPE_PATNUM
_ITEM_TYPE_PATNUM label word
	dw	PAT_ITEM + IT_POWER
	dw	PAT_ITEM + IT_POINT
	dw	PAT_ITEM + IT_DREAM
	dw	PAT_ITEM + IT_BIGPOWER
	dw	PAT_ITEM + IT_BOMB
	dw	PAT_ITEM + IT_1UP
	dw	PAT_ITEM + IT_FULLPOWER

include th02/main/power_overflow[data].asm

; Score per # of Dream items collected, divided by 10.
public _DREAM_SCORE_PER_ITEMS
_DREAM_SCORE_PER_ITEMS	dw 0, 100, 200, 400, 600, 800, 1000, 1280

public _power_overflow, _items_spawned, _items_collected
_power_overflow	dw 0
_items_spawned	dw 0
_items_collected	dw 0

if GAME eq 5
	public _extend_point_items_collected
	_extend_point_items_collected	dw 0
endif

public _total_point_items_collected, _total_max_valued_point_items_collected
_total_point_items_collected	dw 0
_total_max_valued_point_items_collected	dw 0

public _items_pull_to_player
_items_pull_to_player	db 0
	evendata

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

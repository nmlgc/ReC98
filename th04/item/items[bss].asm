; item_type_t
IT_POWER = 0
IT_POINT = 1
IT_DREAM = 2
IT_BIGPOWER = 3
IT_BOMB = 4
IT_1UP = 5
IT_FULLPOWER = 6

item_t struc
	flag	db ?
	db ?
	pos	motion_t <?>
	ITEM_type	db ?
	ITEM_unknown	db ?
	ITEM_patnum	dw ?
	pulled_to_player	dw ?
item_t ends

ITEM_W = 16
ITEM_H = 16
ITEM_PULL_SPEED = 10

if GAME eq 5
ITEM_COUNT = 40
else
ITEM_COUNT = 32
endif

public _items
_items	item_t ITEM_COUNT dup(<?>)
; 4 additional unused one, for some reason?
	item_t 4 dup(<?>)

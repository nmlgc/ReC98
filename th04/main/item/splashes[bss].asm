item_splash_t struc
	flag 	db ?
		db ?
	center	Point ?
	radius_cur 	dw ?
	radius_prev	dw ?
item_splash_t ends

ITEM_SPLASH_COUNT = 8
if GAME eq 5
ITEM_SPLASH_DOTS = 32
else
ITEM_SPLASH_DOTS = 64
endif

public _item_splashes, _item_splash_last_id
_item_splashes	item_splash_t ITEM_SPLASH_COUNT dup(<?>)
_item_splashes_unused	item_splash_t <?>
_item_splash_last_id	db ?
	evendata

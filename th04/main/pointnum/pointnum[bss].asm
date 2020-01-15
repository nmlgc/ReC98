POINTNUM_POPUP_DISTANCE = (12 shl 4)
POINTNUM_POPUP_FRAMES = 24
POINTNUM_FRAMES = 36

if GAME eq 5
	POINTNUM_DIGITS = 5
	POINTNUM_YELLOW_COUNT = 80
else
	POINTNUM_DIGITS = 4
	POINTNUM_YELLOW_COUNT = 200
	POINTNUM_TIMES_2_W = (POINTNUM_W * 2)
endif
POINTNUM_WHITE_COUNT = 200
POINTNUM_COUNT = (POINTNUM_WHITE_COUNT + POINTNUM_YELLOW_COUNT)

pointnum_t struc
	flag	db ?
	age	db ?
	PN_center_cur Point <?>
	PN_center_prev_y	dw ?
	if GAME eq 5
		PN_width dw ?
		PN_digits_lebcd db POINTNUM_DIGITS dup (?)
	else
		PN_digits_lebcd db POINTNUM_DIGITS dup (?)
		PN_width dw ?
		PN_times_2 db ?
	endif
	db ?
pointnum_t ends

public _pointnums
_pointnums	pointnum_t POINTNUM_COUNT dup (<?>)

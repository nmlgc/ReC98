; Growing or shrinking circles.
circle_t struc
	flag        	db ?
	age         	db ?
	center      	Point ?
	radius_cur  	dw ?
	radius_delta	dw ? ; signed
circle_t ends

if GAME eq 5
CIRCLE_COUNT = 8
else
CIRCLE_COUNT = 16
endif
_circles	circle_t CIRCLE_COUNT dup(<?>)

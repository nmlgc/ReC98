explosion_t struc
	flag	db ?
	age	db ?
	; Stored in 1/16th-pixel playfield coordinates.
	center	Point <?>
	EXPLOSION_radius_cur	Point <?>
	EXPLOSION_radius_delta	Point <?>
		db ?
	; Offset to add to the angle for the Y coordinate, turning the circle into
	; a slanted ellipse. See https://www.desmos.com/calculator/faeefi6w1u for
	; a plot of the effect.
	angle_offset	db ?
explosion_t ends

EXPLOSION_AGE_MAX = 32
EXPLOSION_SMALL_COUNT = 2
EXPLOSION_SMALL_W = 16
EXPLOSION_SMALL_H = 16
EXPLOSION_SMALL_SPRITES = 64
EXPLOSION_BIG_SPRITES = 16

public _explosions_small
public _explosions_big
_explosions_small	explosion_t EXPLOSION_SMALL_COUNT dup (<?>)
_explosions_big  	explosion_t <?>

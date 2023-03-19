explosion_t struc
	EXPLOSION_alive	db ?
	age	db ?
	center	Point <?>
	EXPLOSION_radius_cur	Point <?>
	EXPLOSION_radius_delta	Point <?>
		db ?
	angle_offset	db ?
explosion_t ends

EXPLOSION_AGE_MAX = 32
EXPLOSION_SMALL_COUNT = 2
EXPLOSION_SMALL_W = 16
EXPLOSION_SMALL_H = 16
EXPLOSION_SMALL_SPRITES = 64
EXPLOSION_BIG_SPRITES = 16

; explosion_type_t
ET_NONE = -1
ET_CIRCLE = 0
ET_NW_SE = 1
ET_SW_NE = 2
ET_HORIZONTAL = 3
ET_VERTICAL = 4

public _explosions_small
public _explosions_big
_explosions_small	explosion_t EXPLOSION_SMALL_COUNT dup (<?>)
_explosions_big  	explosion_t <?>

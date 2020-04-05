; Decay animation after a shot hit a stage enemy or boss. [patnum] is assumed
; to be a 16×16 sprite.
; TODO: Remove the anti-collision HITSHOT_ prefix once this gets decompiled.
hitshot_t struc
	HITSHOT_age	db ?
	patnum     	db ?
	pos        	motion_t <?>
hitshot_t ends

HITSHOT_W = 16
HITSHOT_H = 16

HITSHOT_COUNT = 24
HITSHOT_AGE_MAX = 13
HITSHOT_AGE_CLIPPED = 18
public _hitshots
_hitshots	hitshot_t HITSHOT_COUNT dup(<?>)

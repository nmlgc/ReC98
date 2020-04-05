combo_t struc
	COMBO_time	db ?
	hits	db ?
	bonus	dw ?
combo_t	ends

COMBO_FRAMES = 80
COMBO_HIT_RESET_FRAMES = 32
COMBO_HIT_MIN = 2
COMBO_HIT_CAP = 99
COMBO_BONUS_CAP = 65535

public _combos
_combos	combo_t PLAYER_COUNT dup(<?>)

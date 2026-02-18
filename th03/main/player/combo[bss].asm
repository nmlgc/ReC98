combo_t struc
	COMBO_time  	db ?
	hits_highest	db ?
	bonus_total 	dw ?
combo_t ends

public _combos
_combos	combo_t PLAYER_COUNT dup(<?>)

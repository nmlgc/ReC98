; The player's options are supposed to lag behind the player's movement by one
; frame, and therefore have to be tracked separately.

public _player_option_pos_cur, _player_option_pos_prev
_player_option_pos_cur	Point <?>
_player_option_pos_prev	Point <?>
if GAME eq 4
	_player_option_patnum	dw ?
else
	_player_option_patnum = PAT_OPTION
endif

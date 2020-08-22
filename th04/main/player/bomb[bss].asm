public _bombing, _bomb_frame, _playchar_bomb_func

_bombing	db ?
_bomb_frame	db ?
if GAME eq 4
	public _player_bomb_func
	_player_bomb_func	dw ?
endif
_playchar_bomb_func	dw ?

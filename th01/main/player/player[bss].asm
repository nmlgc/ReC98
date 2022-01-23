PLAYER_W = 32
PLAYER_H = 32

PLAYER_LEFT_MIN = (PLAYFIELD_LEFT)
PLAYER_LEFT_MAX = (PLAYFIELD_RIGHT - PLAYER_W)

PLAYER_LEFT_START = (PLAYFIELD_CENTER_X - (PLAYER_W / 2))

public _player_invincibility_time, _player_left
_player_invincibility_time	dw ?
_player_left	dw ?
_player_top = (PLAYFIELD_BOTTOM - PLAYER_H)

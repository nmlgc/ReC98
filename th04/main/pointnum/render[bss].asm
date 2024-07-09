public _pointnum_white_p, _pointnum_yellow_p
_pointnum_white_p	db ?
_pointnum_yellow_p	db ?

public _pointnums_alive, _pointnum_first_yellow_alive
_pointnums_alive	dw	(POINTNUM_COUNT + 1) dup (?)
_pointnum_first_yellow_alive	dw ?

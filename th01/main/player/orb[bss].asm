ORB_W = 32
ORB_H = 32

ORB_LEFT_MIN = (PLAYFIELD_LEFT)
ORB_LEFT_MAX = (PLAYFIELD_RIGHT - ORB_W)
ORB_TOP_MIN = (PLAYFIELD_TOP)
ORB_TOP_MAX = (PLAYFIELD_BOTTOM - ORB_H)

ORB_LEFT_START = (ORB_LEFT_MAX -  8)
 ORB_TOP_START = ( ORB_TOP_MAX - 88)

public _orb_cur_left, _orb_cur_top, _orb_force_frame
_orb_cur_left	dw ?
_orb_cur_top 	dw ?
_orb_force_frame	dw ?

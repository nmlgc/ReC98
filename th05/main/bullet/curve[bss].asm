CURVEBULLET_W = 32
CURVEBULLET_H = 32
CURVEBULLET_TRAIL_NODE_COUNT = 16
CURVEBULLET_COUNT = 7

curvebullet_trail_t struc
	flag	db ?
	CBT_col	db ?
	node_pos	Point CURVEBULLET_TRAIL_NODE_COUNT dup (<?>)
	node_sprite	db CURVEBULLET_TRAIL_NODE_COUNT dup (?)
curvebullet_trail_t ends

public _curvebullet_trails
_curvebullet_trails	curvebullet_trail_t (CURVEBULLET_COUNT + 1) dup (<?>)

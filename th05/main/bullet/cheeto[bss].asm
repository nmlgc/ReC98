CHEETO_W = 32
CHEETO_H = 32
CHEETO_TRAIL_NODE_COUNT = 16
CHEETO_COUNT = 7

cheeto_trail_t struc
	flag	db ?
	CBT_col	db ?
	node_pos	Point CHEETO_TRAIL_NODE_COUNT dup (<?>)
	node_sprite	db CHEETO_TRAIL_NODE_COUNT dup (?)
cheeto_trail_t ends

public _cheeto_trails
_cheeto_trails	cheeto_trail_t (CHEETO_COUNT + 1) dup (<?>)

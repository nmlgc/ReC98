SHOT_COUNT = 8

CShots struc
	SHOT_left	dw SHOT_COUNT dup(?)
	SHOT_top	dw SHOT_COUNT dup(?)
	SHOT_unknown	dw SHOT_COUNT dup(?)
	SHOT_moving	db SHOT_COUNT dup(?)
	SHOT_decay_frame	db SHOT_COUNT dup(?)
CShots ends

public _Shots
_Shots	CShots <?>

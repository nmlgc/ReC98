SHOT_VELOCITY = (-12 shl 4)
SHOT_SO_PID = (320 / 8)

SHOT_SPRITE_COUNT = 4
SHOT_W = 16
SHOT_H = 8
SHOT_VRAM_W = (SHOT_W / 8)
SHOT_VRAM_H = (SHOT_H / 2)

shotpair_t struc
	flag	db ?
	unused_1	db ?
	topleft	Point <?>
	velocity_y	dw ?
	so_pid	dw ?
	so_anim	db ?
	db ?
	pid	db ?
	db ?
shotpair_t ends

SHOTPAIR_DISTANCE = 16
SHOTPAIR_COUNT = 32

public _shotpairs
_shotpairs	shotpair_t SHOTPAIR_COUNT dup(<?>)

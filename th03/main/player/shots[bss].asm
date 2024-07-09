SHOT_VELOCITY = (-12 shl 4)
SHOT_SO_PID = (320 / 8)

; shot_mode_t
SM_NONE = 0
SM_1_PAIR = 1
SM_2_PAIRS = 2
SM_4_PAIRS = 3
SM_REIMU_HYPER = 4

; shot_active_t
SA_DISABLED = 0
SA_ENABLED = 1
SA_BLOCKED_FOR_THIS_FRAME = 2

shotpair_t struc
	SP_alive	db ?
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

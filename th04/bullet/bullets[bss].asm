BSS_CLOUD_FRAMES = 16
BMS_DECAY_FRAMES = 16
BMS_SLOWDOWN_BASE_SPEED = (4 shl 4) + 8
BMS_SLOWDOWN_FRAMES = 32

BSS_GRAZEABLE = 0
BSS_GRAZED = 1
BSS_ACTIVE = 2
BSS_CLOUD_BACKWARDS = 3
BSS_CLOUD_FORWARDS = 4
BSS_CLOUD_END = (BSS_CLOUD_FORWARDS + BSS_CLOUD_FRAMES)

BMS_SLOWDOWN = 0
BMS_SPECIAL = 1
BMS_NORMAL = 2
BMS_DECAY = 4
BMS_DECAY_END = (BMS_DECAY + BMS_DECAY_FRAMES)

bullet_t struc
	flag	db ?
	age	db ?
	pos	motion_t <?>
	from_pattern	db ?
		db ?
	speed_cur	db ?
	BULLET_angle	db ?
	spawn_state	db ?
	move_state	db ?
	special_motion	db ?
	speed_final	db ?

	slowdown_time	label byte
	turn_count	label byte
		db ?

	slowdown_speed_delta	label byte
	turn_angle	label byte
		db ?

	BULLET_patnum	dw ?

	if GAME eq 5
		BULLET_origin	Point <?>
		distance	dw ?
	endif
bullet_t ends

pellet_render_t struc
	PRT_left label word
	PRB_vram_offset label word
		dw ?
	PRT_top label word
	PRB_sprite_offset label word
		dw ?
pellet_render_t ends

PELLET_W = 8
PELLET_H = 8
BULLET16_W = 16
BULLET16_H = 16

if GAME eq 5
	PELLET_COUNT = 180
	BULLET16_COUNT = 220
else
	PELLET_COUNT = 240
	BULLET16_COUNT = 200
endif

BULLET_COUNT = (PELLET_COUNT + BULLET16_COUNT)

public _bullets, _pellets, _bullets16, _pellets_render
_bullets label bullet_t
_pellets	bullet_t PELLET_COUNT dup(<?>)
_bullets16	bullet_t BULLET16_COUNT dup(<?>)
_pellets_render	pellet_render_t PELLET_COUNT dup(<?>)

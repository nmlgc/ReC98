; Everything here needs to be kept in sync with the C++ versions in
; bullet.hpp!

; States and modes
; ----------------
BSS_CLOUD_FRAMES = 16
BMS_DECAY_FRAMES = 16
BMS_SLOWDOWN_BASE_SPEED = (4 shl 4) + 8
BMS_SLOWDOWN_FRAMES = 32

; bullet_spawn_state_t
BSS_GRAZEABLE = 0
BSS_GRAZED = 1
BSS_ACTIVE = 2
BSS_CLOUD_BACKWARDS = 3
BSS_CLOUD_FORWARDS = 4
BSS_CLOUD_END = (BSS_CLOUD_FORWARDS + BSS_CLOUD_FRAMES)

; bullet_move_state_t
BMS_SLOWDOWN = 0
BMS_SPECIAL = 1
BMS_REGULAR = 2
BMS_DECAY = 4
BMS_DECAY_END = (BMS_DECAY + BMS_DECAY_FRAMES)
; ----------------

bullet_t struc
	flag	db ?
	age	db ?
	pos	motion_t <?>
	from_group	db ?
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

bullet_template_t struc
	spawn_type	db ?
	patnum	db ?
	BT_origin	Point <?>
if GAME eq 5
	BT_group	db ?
	BT_special_motion	db ?
	spread	db ?
	spread_angle_delta	db ?
	BT_stack	db ?
	stack_speed_delta	db ?
	BT_angle	db ?
	speed	db ?
else
	BT_velocity	Point <?>
	BT_group	db ?
	BT_angle	db ?
	speed	db ?
	count	db ?
	BT_delta	bullet_template_delta_t <?>
		db ?
	BT_special_motion	db ?
		db ?
endif
bullet_template_t ends

PELLET_W = 8
PELLET_H = 8
BULLET16_W = 16
BULLET16_H = 16

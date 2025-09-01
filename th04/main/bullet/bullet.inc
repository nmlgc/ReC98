; Everything here needs to be kept in sync with the C++ versions in
; bullet.hpp!

include th02/main/entity.inc

; States and modes
; ----------------
BSS_CLOUD_FRAMES = 16
BMS_DECAY_FRAMES = 16
BMS_DECELERATE_BASE_SPEED = (4 shl 4) + 8
BMS_DECELERATE_THRESHOLD = (BMS_DECELERATE_BASE_SPEED - 8)
BMS_DECELERATE_FRAMES = 32

; bullet_spawn_state_t
BSS_GRAZEABLE = 0
BSS_GRAZED = 1
BSS_ACTIVE = 2
BSS_CLOUD_BACKWARDS = 3
BSS_CLOUD_FORWARDS = 4
BSS_CLOUD_END = (BSS_CLOUD_FORWARDS + BSS_CLOUD_FRAMES)

; bullet_move_state_t
BMS_DECELERATE = 0
BMS_SPECIAL = 1
BMS_REGULAR = 2
BMS_DECAY = 4
BMS_DECAY_END = (BMS_DECAY + BMS_DECAY_FRAMES)

; bullet_special_motion_t
_bullet_special_motion_t_offset = ((GAME - 5) * 81h) and 0FFh
BSM_DECELERATE_THEN_TURN_AIMED = (_bullet_special_motion_t_offset + 1)
BSM_DECELERATE_THEN_TURN = (BSM_DECELERATE_THEN_TURN_AIMED + 1)
BSM_SPEEDUP = (BSM_DECELERATE_THEN_TURN + 1)
BSM_DECELERATE_TO_ANGLE = (BSM_SPEEDUP + 1)
BSM_BOUNCE_LEFT_RIGHT = (BSM_DECELERATE_TO_ANGLE + 1)
BSM_BOUNCE_TOP_BOTTOM = (BSM_BOUNCE_LEFT_RIGHT + 1)
BSM_BOUNCE_LEFT_RIGHT_TOP_BOTTOM = (BSM_BOUNCE_TOP_BOTTOM + 1)
BSM_BOUNCE_LEFT_RIGHT_TOP = (BSM_BOUNCE_LEFT_RIGHT_TOP_BOTTOM + 1)
BSM_GRAVITY = (BSM_BOUNCE_LEFT_RIGHT_TOP + 1)
if (GAME eq 5)
	BSM_EXACT_LINEAR = (BSM_GRAVITY + 1)
endif
BSM_NONE = 0FFh

bullet_special_angle_t union
	BSA_turn_by	db ?
	BSA_target	db ?
	BSA_v	db ?
bullet_special_angle_t ends
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

	decelerate_time	label byte
	turns_done	label byte
	BULLET_ax	db ?

	decelerate_speed_delta	label byte
	BULLET_SPECIAL_angle	label bullet_special_angle_t
	BULLET_dx	db ?

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

if GAME eq 5
	PELLET_COUNT = 180
	BULLET16_COUNT = 220
else
	PELLET_COUNT = 240
	BULLET16_COUNT = 200
endif

BULLET_COUNT = (PELLET_COUNT + BULLET16_COUNT)

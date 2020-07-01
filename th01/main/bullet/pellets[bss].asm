PELLET_COUNT = 100

PM_NORMAL = 0
PM_GRAVITY = 1
PM_SLING_AIMED = 2
PM_BOUNCE_FROM_TOP_THEN_GRAVITY = 3
PM_FALL_STRAIGHT_FROM_TOP_THEN_NORMAL = 4
PM_SPIN = 5
PM_CHASE = 6

pellet_t	struc
	PELLET_moving	db ?
	PELLET_motion_type	db ?
	PELLET_cur_left	dw ?
	PELLET_cur_top	dw ?
	PELLET_spin_center	Point <?>
	PELLET_prev_left	dw ?
	PELLET_prev_top	dw ?
	PELLET_from_pattern	dw ?
	PELLET_velocity	Point <?>
	PELLET_spin_velocity	Point <?>
	PELLET_not_rendered	dw ?
	PELLET_age	dw ?
	PELLET_speed	dw ?
	PELLET_decay_frame	dw ?
	PELLET_cloud_frame	dw ?
	PELLET_cloud_left	dw ?
	PELLET_cloud_top	dw ?
	PELLET_angle	dw ?
	PELLET_sling_direction	dw ?
pellet_t	ends

CPellets	struc
	pellets	pellet_t PELLET_COUNT dup(<?>)
	PELLET_alive_count	dw ?
	PELLET_unknown_zero	dw 10 dup(?)
	PELLET_unknown_seven	dw ?
	PELLET_interlace_field	dw ?
	PELLET_spawn_with_cloud	db ?
CPellets	ends

public _Pellets
_Pellets	CPellets <?>

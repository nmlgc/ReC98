PELLET_COUNT = 100

PM_REGULAR = 0
PM_GRAVITY = 1
PM_SLING_AIMED = 2
PM_BOUNCE_FROM_TOP_THEN_GRAVITY = 3
PM_FALL_STRAIGHT_FROM_TOP_THEN_NORMAL = 4
PM_SPIN = 5
PM_CHASE = 6

PG_NONE = 0
PG_1 = 1
PG_1_AIMED = 12
PG_2_SPREAD_WIDE = 13
PG_2_SPREAD_NARROW = 14
PG_3_SPREAD_WIDE = 15
PG_3_SPREAD_NARROW = 16
PG_4_SPREAD_WIDE = 17
PG_4_SPREAD_NARROW = 18
PG_5_SPREAD_WIDE = 19
PG_5_SPREAD_NARROW = 20
PG_AIMED_SPREADS = 21
PG_2_SPREAD_WIDE_AIMED = 21
PG_2_SPREAD_NARROW_AIMED = 22
PG_3_SPREAD_WIDE_AIMED = 23
PG_3_SPREAD_NARROW_AIMED = 24
PG_4_SPREAD_WIDE_AIMED = 25
PG_4_SPREAD_NARROW_AIMED = 26
PG_5_SPREAD_WIDE_AIMED = 27
PG_5_SPREAD_NARROW_AIMED = 28
PG_1_RANDOM_NARROW_AIMED = 29
PG_1_RANDOM_WIDE = 30

pellet_t	struc
	PELLET_moving	db ?
	PELLET_motion_type	db ?
	PELLET_cur_left	dw ?
	PELLET_cur_top	dw ?
	PELLET_spin_center	Point <?>
	PELLET_prev_left	dw ?
	PELLET_prev_top	dw ?
	PELLET_from_group	dw ?
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

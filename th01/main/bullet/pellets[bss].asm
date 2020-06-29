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

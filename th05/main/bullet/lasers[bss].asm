LF_FREE = 0
LF_FIXED_WAIT_TO_GROW = 2
LF_FIXED_SHRINK_AND_WAIT_TO_GROW = 6
LF_SHOOTOUT_DECAY = 7

laser_coords_t struc
	origin            	Point <?>
	starts_at_distance	dw ?
	ends_at_distance  	dw ?
	angle             	db ?
	LASER_width       	db ?
laser_coords_t ends

laser_t struc
	flag          	db ?
	LASER_color   	db ?
	coords        	laser_coords_t <?>
	shootout_speed	dw ?
	LASER_age     	dw ?

	grow_at_age   	label word
	moveout_at_age	label word
	              	dw ?

	shrink_at_age 	dw ?
	grow_to_width 	db ?
	              	db 3 dup(?)
laser_t ends

LASER_COUNT = 32
public _lasers, _laser_template
_lasers        	laser_t LASER_COUNT dup(<?>)
_laser_template	laser_t <?>

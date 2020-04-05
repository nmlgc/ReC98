if GAME eq 4
	bullet_template_delta_t union
		spread_angle	db ?
		stack_speed 	db ?
	bullet_template_delta_t ends
endif

bullet_template_t struc
	spawn_type	db ?
	patnum	db ?
	BT_origin	Point <?>
if GAME eq 5
	pattern	db ?
	BT_special_motion	db ?
	spread	db ?
	spread_angle_delta	db ?
	BT_stack	db ?
	stack_speed_delta	db ?
	BT_angle	db ?
	speed	db ?
else
	BT_velocity	Point <?>
	pattern	db ?
	BT_angle	db ?
	speed	db ?
	count	db ?
	BT_delta	bullet_template_delta_t <?>
		db ?
	BT_special_motion	db ?
		db ?
endif
bullet_template_t ends

public _bullet_template
_bullet_template	bullet_template_t <?>

REIMU_STAR_TRAILS = 6
REIMU_STAR_NODE_COUNT = 8
MARISA_LASER_COUNT = 8
MIMA_CIRCLE_COUNT = 8

reimu_star_t struc
	BA_topleft	Point <?>
	BA_velocity	Point <?>
	BA_angle	db ?
		db ?
reimu_star_t ends

marisa_laser_t struc
	BA_center	Point <?>
		dw ?
	BA_radius	dw ?
		dw ?
marisa_laser_t ends

mima_circle_t struc
	BA_center	Point <?>
		dw ?
	BA_distance	dw ?
	BA_angle	db ?
		db ?
mima_circle_t ends

yuuka_heart_t struc
	BA_topleft	Point <?>
		dw ?
	BA_distance	dw ?
	BA_angle	db ?
		db ?
yuuka_heart_t ends

bomb_anim_t	union
	reimu_star_t	REIMU_STAR_TRAILS dup (REIMU_STAR_NODE_COUNT dup (<?>))
	marisa_laser_t	MARISA_LASER_COUNT dup (<?>)
	mima_circle_t	MIMA_CIRCLE_COUNT dup (<?>)
	yuuka_heart_t	<?>
bomb_anim_t ends

public _bomb_anim
	dw ?
_bomb_anim	bomb_anim_t <?>
	reimu_star_t <?>	; 1 additional unused one, for some reason?
	dd ?

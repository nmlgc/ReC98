; Everything here needs to be kept in sync with the C++ versions in
; gather.hpp!

gather_t struc
	G_flag	db ?
	G_col	db ?
	G_center	motion_t <?>
	G_radius_cur	dw ?
	G_ring_points	dw ?
	G_angle_cur	db ?
	G_angle_delta	db ?
if GAME eq 4
	G_bullet_template bullet_template_t <?>
endif
	G_radius_prev	dw ?
	G_radius_delta	dw ?
if GAME eq 5
	G_bullet_template bullet_template_t <?>
endif
gather_t ends

gather_template_t struc
	GT_center	Point <?>
	GT_velocity	Point <?>
	GT_radius	dw ?
	GT_ring_points	dw ?
	GT_col	db ?
	GT_angle_delta	db ?
gather_template_t ends

GATHER_FRAMES = 32
GATHER_RADIUS_START = (64 shl 4)
GATHER_RADIUS_END = (2 shl 4)

GATHER_COUNT = 16
if GAME eq 5
	GATHER_CAP = 8
else
	GATHER_CAP = GATHER_COUNT
endif

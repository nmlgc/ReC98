LINESET_LINE_COUNT = 20
LINESET_COUNT = 4
BOSS_PARTICLE_COUNT = 64

lineset_t struc
	LS_center	Point LINESET_LINE_COUNT dup (<?>)
	LS_velocity_y	dw ?
	LS_radius	dw LINESET_LINE_COUNT dup (?)
	LS_angle	db LINESET_LINE_COUNT dup (?)
lineset_t ends

boss_particle_t struc
	BP_pos	Point <?>
	BP_origin	Point <?>
	BP_velocity	Point <?>
	BP_age	dw ?
	BP_angle	db ?
	BP_patnum	db ?
boss_particle_t ends

public _linesets, _boss_particles
_linesets	lineset_t LINESET_COUNT dup (<?>)
lineset0	equ <_linesets[0 * size lineset_t]>
lineset1	equ <_linesets[1 * size lineset_t]>

_boss_particles	boss_particle_t BOSS_PARTICLE_COUNT dup (<?>)

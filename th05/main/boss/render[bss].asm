BOSS_PARTICLE_COUNT = 64

boss_particle_t struc
	BP_pos	Point <?>
	BP_origin	Point <?>
	BP_velocity	Point <?>
	BP_age	dw ?
	BP_angle	db ?
	BP_patnum	db ?
boss_particle_t ends

public _boss_particles
_boss_particles	boss_particle_t BOSS_PARTICLE_COUNT dup (<?>)

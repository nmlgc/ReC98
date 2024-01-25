enum particle_origin_t {
	PO_TOP = 0,
	PO_TOP_RIGHT = 1,
	PO_RIGHT = 2,
	PO_BOTTOM_RIGHT = 3,
	PO_BOTTOM = 4,
	PO_BOTTOM_LEFT = 5,
	PO_LEFT = 6,
	PO_TOP_LEFT = 7,
	PO_INITIALIZE = 255, // (renders nothing)

	_particle_origin_t_FORCE_INT16 = 0x7FFF
};

// Runs a frame of the particle system, with new particles spawning from a
// random position on the [origin] edge(s) and flying into the opposite
// direction. Must be called with [origin] == PO_INITIALIZE first!
void particles_unput_update_render(particle_origin_t origin, vc2 col);

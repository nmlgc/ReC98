#include "th01/math/subpixel.hpp"

enum particle_origin_t {
	PO_TOP = 0,
	PO_TOP_RIGHT = 1,
	PO_RIGHT = 2,
	PO_BOTTOM_RIGHT = 3,
	PO_BOTTOM = 4,
	PO_BOTTOM_LEFT = 5,
	PO_LEFT = 6,
	PO_TOP_LEFT = 7,

	_particle_origin_t_FORCE_INT16 = 0x7FFF
};

static const int PARTICLE_COUNT = 40;

struct CParticles {
	int spawn_interval;
	pixel_t velocity_base_max;
	Subpixel x[PARTICLE_COUNT];
	Subpixel y[PARTICLE_COUNT];
	Subpixel velocity_x[PARTICLE_COUNT];
	Subpixel velocity_y[PARTICLE_COUNT];
	bool alive[PARTICLE_COUNT];

	// MODDERS: Should be local, and just a single variable, not an array.
	unsigned char velocity_base[PARTICLE_COUNT];

	unsigned char spawn_cycle;

	void init();

	// Runs a frame of the particle system, with new particles spawning from a
	// random position on the [origin] edge(s) and flying into the opposite
	// direction. init() must have been called before!
	void unput_update_render(particle_origin_t origin, vc_t col);
};

extern CParticles Particles;

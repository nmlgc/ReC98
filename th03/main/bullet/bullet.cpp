#include "th03/main/bullet/bullet.hpp"

struct bullet_trail_coords_t {
	PlayfieldSubpixel v[TRAIL_POINT_COUNT];
};

struct bullet_trail_t {
	bullet_trail_coords_t center_x;
	bullet_trail_coords_t center_y;
};

// State
// -----

extern bullet_trail_t bullet_trail_ring[TRAIL_RING_SIZE];

// Index of the next `bullet_trail_t` instance within [bullet_trail_ring] to be
// assigned to a bullet with trail sprites.
extern uint8_t bullet_trail_ring_i;
// -----

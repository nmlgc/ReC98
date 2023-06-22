#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"

// Structures
// ----------

#define EXPLOSION_SMALL_COUNT 2

struct explosion_t {
	bool alive;
	unsigned char age;
	SPPoint center;
	SPPoint radius_cur;
	SPPoint radius_delta;
	int8_t unused; // ZUN bloat

	// Offset to add to the angle for the Y coordinate, turning the circle
	// into a slanted ellipse. See https://www.desmos.com/calculator/faeefi6w1u
	// for a plot of the effect.
	unsigned char angle_offset;
};

extern explosion_t explosions_small[EXPLOSION_SMALL_COUNT];
extern explosion_t explosions_big;
// ----------

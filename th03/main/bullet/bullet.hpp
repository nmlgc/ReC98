#include "th03/main/playfld.hpp"
#include "th03/sprites/main_s16.hpp"

// Constants
// ---------

static const int TRAIL_POINTS_PER_SPRITE = 2;
static const int TRAIL_POINT_COUNT = (
	TRAIL_POINTS_PER_SPRITE * BULLET16_TRAIL_CELS
);
static const int TRAIL_RING_SIZE = 48;
// ---------

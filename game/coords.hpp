#include "th01/math/subpixel.hpp"

// Points that change from subpixel screen space to pixel screen space within
// the same variable...
// ZUN bloat: Just use separate variables.
union space_changing_point_t {
	SPPoint sp;
	screen_point_t pixel;
};

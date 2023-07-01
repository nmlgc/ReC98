extern "C" {
#include "th02/math/vector.hpp"

extern "C" void pascal near vector2_near(
	SPPoint near &ret, unsigned char angle, subpixel_t length
);

extern "C" void pascal vector2_at(
	SPPoint near &ret,
	subpixel_t origin_x,
	subpixel_t origin_y,
	subpixel_t length,
	int angle
);
}

#include "th03/math/vector.hpp"

// (different calling convention than the TH03 one)
int pascal vector1_at(int origin, int length, int angle);

void pascal near vector2_near(
	SPPoint near &ret, unsigned char angle, subpixel_t length
);

void pascal vector2_at(
	SPPoint near &ret,
	subpixel_t origin_x,
	subpixel_t origin_y,
	subpixel_t length,
	int angle
);

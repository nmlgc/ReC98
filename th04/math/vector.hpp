#include "th03/math/vector.hpp"

// (different calling convention than the TH03 one)
int pascal vector1_at(int origin, int length, int angle);

int pascal near vector2_near(Point near &ret, unsigned char angle, int length);

int pascal vector2_at(
	Point near &ret, int origin_x, int origin_y, int length, int angle
);

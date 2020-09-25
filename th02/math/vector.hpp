#include "th01/math/vector.hpp"

void pascal vector2(int &ret_x, int &ret_y, unsigned char angle, int length);

// Constructs a vector from (x1, y1) to (x2, y2), and additionally applies
// [plus_angle] to the resulting angle between the two points.
void pascal vector2_between_plus(
	int x1,
	int y1,
	int x2,
	int y2,
	unsigned char plus_angle,
	int &ret_x,
	int &ret_y,
	int length
);

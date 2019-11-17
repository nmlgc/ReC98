#include "th03/math/math.h"

// Vectors
// -------
// (different calling convention and parameter order than the TH03 one)
int pascal far vector1_at(int angle, int length, int origin);

int pascal near vector2_near(Point near *ret, int angle, int length);

int pascal far vector2_at(
	Point near *ret, int origin_x, int origin_y, int length, int angle
);
// -------

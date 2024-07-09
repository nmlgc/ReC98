#pragma option -zCSHARED

#include "th01/math/polar.hpp"
#include "th02/math/vector.hpp"

void pascal vector2(int &ret_x, int &ret_y, unsigned char angle, int length)
{
	ret_x = polar_x_fast(0, length, angle);
	ret_y = polar_y_fast(0, length, angle);
}

void pascal vector2_between_plus(
	int x1,
	int y1,
	int x2,
	int y2,
	unsigned char plus_angle,
	int &ret_x,
	int &ret_y,
	int length
)
{
	plus_angle = iatan2((y2 - y1), (x2 - x1)) + plus_angle;
	ret_x = polar_x_fast(0, length, plus_angle);
	ret_y = polar_y_fast(0, length, plus_angle);
}

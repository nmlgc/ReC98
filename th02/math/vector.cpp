#include "th02/math/vector.hpp"

void pascal vector2(int &ret_x, int &ret_y, unsigned char angle, int length)
{
	ret_x = (static_cast<long>(length) * CosTable8[angle]) >> 8;
	ret_y = (static_cast<long>(length) * SinTable8[angle]) >> 8;
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
	ret_x = (static_cast<long>(length) * CosTable8[plus_angle]) >> 8;
	ret_y = (static_cast<long>(length) * SinTable8[plus_angle]) >> 8;
}

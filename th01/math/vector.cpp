extern "C" {

#include <master.h>
#include "th01/math/vector.hpp"

void vector2_between(
	int x1, int y1, int x2, int y2, int& ret_x, int &ret_y, int length
)
{
	unsigned char angle = iatan2(y2 - y1, x2 - x1);
	ret_x = (static_cast<long>(length) * CosTable8[angle]) >> 8;
	ret_y = (static_cast<long>(length) * SinTable8[angle]) >> 8;
}

void vector2(int &ret_x, int &ret_y, int length, unsigned char angle)
{
	ret_x = (static_cast<long>(length) * CosTable8[angle]) >> 8;
	ret_y = (static_cast<long>(length) * SinTable8[angle]) >> 8;
}

}

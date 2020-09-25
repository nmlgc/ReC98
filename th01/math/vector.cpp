extern "C" {

#include <master.h>
#include "platform.h"
#include "pc98.h"
#include "th01/math/vector.hpp"

void vector2_between(
	int x1, int y1, int x2, int y2, int& ret_x, int &ret_y, int length
)
{
	unsigned char angle = iatan2(y2 - y1, x2 - x1);
	ret_x = polar_x_fast(0, length, angle);
	ret_y = polar_y_fast(0, length, angle);
}

void vector2(int &ret_x, int &ret_y, int length, unsigned char angle)
{
	ret_x = polar_x_fast(0, length, angle);
	ret_y = polar_y_fast(0, length, angle);
}

}

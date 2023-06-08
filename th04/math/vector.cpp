#pragma option -3

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/polar.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th04/math/vector.hpp"

extern "C" int pascal vector1_at(int origin, int length, int angle)
{
	return (((static_cast<long>(length) * angle) >> 8) + origin);
}

extern "C" void pascal vector2_at(
	SPPoint near &ret,
	subpixel_t origin_x,
	subpixel_t origin_y,
	subpixel_t length,
	int angle
)
{
	_BX = angle;
	#if (GAME == 5)
		_BH ^= _BH;
	#endif
	_BX += _BX; // *= sizeof(short)
	ret.x.v = polar_x_fast_unsafe(origin_x, length, _BX);
	ret.y.v = polar_y_fast_unsafe(origin_y, length, _BX);
}

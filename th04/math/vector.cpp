#pragma option -3

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th04/math/vector.hpp"

#define polar_by_offset(radius, table, offset) ( \
	static_cast<long>(radius) * *reinterpret_cast<const short *>( \
		reinterpret_cast<const int8_t*>(table) + offset \
	))

static inline pixel_t polar_x_fast_unsafe(
	pixel_t center, pixel_t &radius, size_t table_offset
) {
	return ((polar_by_offset(radius, CosTable8, table_offset) >> 8) + center);
}

static inline pixel_t polar_y_fast_unsafe(
	pixel_t center, pixel_t &radius, size_t table_offset
) {
	return ((polar_by_offset(radius, SinTable8, table_offset) >> 8) + center);
}

#undef polar_by_offset

int pascal vector1_at(int origin, int length, int angle)
{
	return (((static_cast<long>(length) * angle) >> 8) + origin);
}

void pascal vector2_at(
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

}

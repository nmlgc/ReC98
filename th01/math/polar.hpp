#include "libs/master.lib/master.hpp"
#include "pc98.h"

template <class P, class T> inline P polar_x(
	const P center, const P radius, T angle
) {
	return (((static_cast<long>(radius) * Cos8(angle)) >> 8) + center);
}

template <class P, class T> inline P polar_y(
	const P center, const P radius, T angle
) {
	return (((static_cast<long>(radius) * Sin8(angle)) >> 8) + center);
}

static inline pixel_t polar_x_fast(
	pixel_t center, pixel_t radius, unsigned char angle
) {
	return (((static_cast<long>(radius) * CosTable8[angle]) >> 8) + center);
}

static inline pixel_t polar_y_fast(
	pixel_t center, pixel_t radius, unsigned char angle
) {
	return (((static_cast<long>(radius) * SinTable8[angle]) >> 8) + center);
}

#define polar_by_offset(center, radius, table, offset) ( \
	(static_cast<long>(radius) * *reinterpret_cast<const short *>( \
		reinterpret_cast<const int8_t*>(table) + offset \
	) >> 8) + center \
)

static inline pixel_t polar_x_fast_unsafe(
	pixel_t center, pixel_t &radius, uint16_t table_offset
) {
	return polar_by_offset(center, radius, CosTable8, table_offset);
}

static inline pixel_t polar_y_fast_unsafe(
	pixel_t center, pixel_t &radius, uint16_t table_offset
) {
	return polar_by_offset(center, radius, SinTable8, table_offset);
}

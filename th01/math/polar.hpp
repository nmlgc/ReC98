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

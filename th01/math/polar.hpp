template <class T> inline pixel_t polar_x(
	pixel_t center, pixel_t radius, T angle
) {
	return (((static_cast<long>(radius) * Cos8(angle)) >> 8) + center);
}

template <class T> inline pixel_t polar_y(
	pixel_t center, pixel_t radius, T angle
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

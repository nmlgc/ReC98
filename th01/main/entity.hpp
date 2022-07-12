// Generic entity template
template <int Count> struct CEntities {
	screen_x_t left[Count];
	screen_y_t top[Count];

	static int count() {
		return Count;
	}
};

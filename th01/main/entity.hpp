// Single entity that is positioned in terms of its top-left coordinated. Does
// not occur in ZUN's original TH01 code, but should be used to improve the
// code. Note the semantic difference to a `screen_point_t`.
struct entity_topleft_t {
	screen_x_t left;
	screen_y_t top;
};

// Generic SoA entity template
template <int Count> struct EntitiesTopleft {
	screen_x_t left[Count];
	screen_y_t top[Count];

	static int count() {
		return Count;
	}
};

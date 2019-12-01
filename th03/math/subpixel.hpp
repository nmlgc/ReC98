// Fixed-point format for expressing world-space coordinates, with 4 bits of
// fractional resolution.

typedef int subpixel_t;

inline subpixel_t to_sp(float screen_v) {
	return static_cast<subpixel_t>(screen_v * 16.0f);
}

class Subpixel {
public:
	// Code generation will require direct access to v, if performing
	// arithmetic with a local variable...
	subpixel_t v;

	void operator +=(float screen_v) {
		this->v += to_sp(screen_v);
	}

	void operator -=(float screen_v) {
		this->v -= to_sp(screen_v);
	}

	void operator =(float screen_v) {
		v = to_sp(screen_v);
	}
};

struct SPPoint {
	Subpixel x, y;

	void set(float screen_x, float screen_y) {
		x = screen_x;
		y = screen_y;
	}
};

// Fixed-point format for expressing world-space coordinates, with 4 bits of
// fractional resolution.

typedef int subpixel_t;

#define TO_SP(v) \
	(v << 4)

inline subpixel_t to_sp(float screen_v) {
	return static_cast<subpixel_t>(screen_v * 16.0f);
}

template <class T> class SubpixelBase {
public:
	// Code generation will require direct access to v, if performing
	// arithmetic with a local variable...
	T v;

	subpixel_t operator -(const SubpixelBase<T> &other) {
		return (this->v - other.v);
	}

	void operator +=(float screen_v) {
		this->v += static_cast<T>(to_sp(screen_v));
	}

	void operator -=(float screen_v) {
		this->v -= static_cast<T>(to_sp(screen_v));
	}

	void operator =(float screen_v) {
		v = static_cast<T>(to_sp(screen_v));
	}

	void operator =(const T &screen_v) {
		v = TO_SP(screen_v);
	}

	T to_screen() const {
		return v >> 4;
	}
};

template <class T> struct SPPointBase {
	T x, y;

	void set(float screen_x, float screen_y) {
		x = screen_x;
		y = screen_y;
	}

	void set(const T &screen_x, const T &screen_y) {
		x = screen_x;
		y = screen_y;
	}
};

// 16-bit (Q12.4)
typedef SubpixelBase<subpixel_t> Subpixel;
typedef SPPointBase<Subpixel> SPPoint;
// 8-bit (Q4.4)
typedef SubpixelBase<unsigned char> SubpixelLength8;
typedef SubpixelBase<char> Subpixel8;
typedef SPPointBase<Subpixel8> SPPoint8;

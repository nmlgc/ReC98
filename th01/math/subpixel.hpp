// Fixed-point format for expressing world-space coordinates, with 4 bits of
// fractional resolution.

#define SUBPIXEL_HPP

#define PIXEL_NONE (-999)

typedef int subpixel_t;

#define TO_SP(v) \
	(v << 4)

#define TO_PIXEL(v) \
	(v >> 4)

// In-place conversion to a pixel. Ugly, and should not exist.
#define TO_PIXEL_INPLACE(v) \
	(v >>= 4)

inline subpixel_t to_sp(float pixel_v) {
	return static_cast<subpixel_t>(pixel_v * 16.0f);
}

inline unsigned char to_sp8(float pixel_v) {
	return static_cast<unsigned char>(to_sp(pixel_v));
}

template <class SubpixelType, class PixelType> class SubpixelBase {
public:
	typedef SubpixelBase<SubpixelType, PixelType> SelfType;

	// Code generation will require direct access to v, if performing
	// arithmetic with a local variable...
	SubpixelType v;

	SubpixelType operator +(float pixel_v) const {
		return (this->v + static_cast<SubpixelType>(to_sp(pixel_v)));
	}

	SubpixelType operator -(const SelfType &other) const {
		return (this->v - other.v);
	}

	void operator +=(float pixel_v) {
		this->v += static_cast<SubpixelType>(to_sp(pixel_v));
	}

	void operator -=(float pixel_v) {
		this->v -= static_cast<SubpixelType>(to_sp(pixel_v));
	}

	// No overloads of `operator =()`, since the class needs to be trivially
	// copyable.
	void set(float pixel_v) {
		v = static_cast<SubpixelType>(to_sp(pixel_v));
	}

	void set(const PixelType &pixel_v) {
		v = static_cast<SubpixelType>(TO_SP(pixel_v));
	}

	PixelType to_pixel() const {
		return static_cast<PixelType>(TO_PIXEL(v));
	}

	PixelType to_pixel_slow() const { // MODDERS: Delete
		return (v / 16);
	}

	operator SubpixelType() const {
		return v;
	}

	static SubpixelType None() {
		return static_cast<SubpixelType>(TO_SP(PIXEL_NONE));
	}
};

template <class T> struct SPPointBase {
	T x, y;

	void set(float screen_x, float screen_y) {
		x.set(screen_x);
		y.set(screen_y);
	}
};

// 16-bit (Q12.4)
typedef SubpixelBase<subpixel_t, pixel_t> Subpixel;
typedef SPPointBase<Subpixel> SPPoint;
// 8-bit (Q4.4)
typedef SubpixelBase<unsigned char, unsigned char> SubpixelLength8;
typedef SubpixelBase<char, char> Subpixel8;
typedef SPPointBase<Subpixel8> SPPoint8;

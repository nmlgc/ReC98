// Fixed-point format for expressing world-space coordinates, with 4 bits of
// fractional resolution.
// -------------------------------------------------------------------------

#ifndef TH01_MATH_SUBPIXEL_HPP
#define TH01_MATH_SUBPIXEL_HPP

#include "pc98.h"

#define PIXEL_NONE (-999)

typedef uint8_t subpixel_length_8_t;
typedef int subpixel_t;

static const subpixel_t SUBPIXEL_FACTOR = 16;
static const char SUBPIXEL_BITS = 4;

#define TO_SP(v) \
	((v) << SUBPIXEL_BITS)

#define TO_PIXEL(v) \
	((v) >> SUBPIXEL_BITS)

// ZUN bloat: In-place conversions between pixels and subpixels. Ugly, and
// should not exist.
#define TO_PIXEL_INPLACE(v) \
	((v) >>= SUBPIXEL_BITS)
#define TO_SP_INPLACE(v) \
	((v) <<= SUBPIXEL_BITS)

inline subpixel_t to_sp(float pixel_v) {
	return static_cast<subpixel_t>(pixel_v * SUBPIXEL_FACTOR);
}

inline subpixel_length_8_t to_sp8(float pixel_v) {
	return static_cast<subpixel_length_8_t>(to_sp(pixel_v));
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

struct SPPoint : public SPPointBase<Subpixel> {
	void set_long(subpixel_t subpixel_x, subpixel_t subpixel_y) {
		reinterpret_cast<uint32_t &>(x) = (
			subpixel_x | (static_cast<uint32_t>(subpixel_y) << 16)
		);
	}
};

// 8-bit (Q4.4)
typedef SubpixelBase<subpixel_length_8_t, pixel_length_8_t> SubpixelLength8;
typedef SubpixelBase<char, pixel_delta_8_t> Subpixel8;
typedef SPPointBase<Subpixel8> SPPoint8;
// -------------------------------------------------------------------------

// Subpixels with one decimal digit of fractional resolution?! Sure, if you
// absolutely want those precise multiples of 0.1 in your movement code...
// -------------------------------------------------------------------------

typedef int decimal_subpixel_t;

struct DecimalSubpixel {
	decimal_subpixel_t v;

	pixel_t to_pixel() const {
		return static_cast<pixel_t>(v / 10);
	}
};

inline decimal_subpixel_t to_dsp(float pixel_v) {
	return static_cast<decimal_subpixel_t>(pixel_v * 10);
}

#endif /* TH01_MATH_SUBPIXEL_HPP */
// -------------------------------------------------------------------------

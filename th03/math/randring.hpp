#include "th02/math/randring.h"

uint16_t pascal near randring1_next16(void);
uint16_t pascal near randring1_next16_and(uint16_t mask);
uint16_t pascal near randring2_next16_and(uint16_t mask);
uint16_t pascal near randring2_next16_mod(uint16_t mask);

/// Constrained random numbers
/// --------------------------
/// These limit the next random number between [min] inclusive and [max]
/// exclusive, via either AND or MOD. Typically, you'd just use the non-AND
/// version, which automatically picks the AND variant if the range is a power
/// of 2.
/// (Sadly, ZUN also uses *_and() if the range is *not* a power of two. That's
/// the whole reason while we have to keep these separate *_and_*() functions.)

inline uint8_t randring1_next8_and_ge_lt(uint8_t min, uint8_t max) {
	return (min + randring1_next16_and((max - min) - 1));
}

inline int16_t randring1_next16_and_ge_lt(int16_t min, int16_t max) {
	return (min >= 0)
		? (min + randring1_next16_and((max - min) - 1))
		: (randring1_next16_and(max + -min - 1) - (-min));
}

inline uint8_t randring2_next8_and_ge_lt(uint8_t min, uint8_t max) {
	return (min + randring2_next16_and((max - min) - 1));
}

inline uint8_t randring2_next8_ge_lt(uint8_t min, uint8_t max) {
	// Use the AND form if the range is a power of 2.
	if((max - min) & ((max - min) - 1) == 0) {
		return randring2_next8_and_ge_lt(min, max);
	}
	return (static_cast<int8_t>(min) >= 0)
		? (min + randring2_next16_mod(max - min))
		: (randring2_next16_mod(max + -static_cast<int8_t>(min)) - (-min));
}

inline int16_t randring2_next16_and_ge_lt(int16_t min, int16_t max) {
	return (min + randring2_next16_and((max - min) - 1));
}

inline int16_t randring2_next16_ge_lt(int16_t min, int16_t max) {
	// Use the AND form if the range is a power of 2.
	if((max - min) & ((max - min) - 1) == 0) {
		return randring2_next16_and_ge_lt(min, max);
	}
	return (min + randring2_next16_mod(max - min));
}

#ifdef SUBPIXEL_HPP
	inline subpixel_t randring1_next8_and_ge_lt_sp(float min, float max) {
		return randring1_next8_and_ge_lt(to_sp8(min), to_sp8(max));
	}

	inline subpixel_t randring1_next16_and_ge_lt_sp(float min, float max) {
		return randring1_next16_and_ge_lt(to_sp(min), to_sp(max));
	}

	inline subpixel_t randring2_next8_and_ge_lt_sp(float min, float max) {
		return randring2_next8_and_ge_lt(to_sp8(min), to_sp8(max));
	}

	inline subpixel_t randring2_next16_ge_lt_sp(float min, float max) {
		return randring2_next16_ge_lt(to_sp(min), to_sp(max));
	}
#endif
/// --------------------------

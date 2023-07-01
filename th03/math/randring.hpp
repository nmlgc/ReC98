#include "th02/math/randring.hpp"

uint16_t near randring1_next16(void);
uint16_t pascal near randring1_next16_and(uint16_t mask);
uint16_t pascal near randring2_next16_and(uint16_t mask);
uint16_t pascal near randring2_next16_mod(uint16_t mask);

/// Constrained random numbers
/// --------------------------
/// These limit the next random number between [min] inclusive and [max]
/// exclusive, via either AND or MOD. Typically, you'd just use the non-AND
/// version, which automatically picks the AND variant if the range is a power
/// of 2.
/// Sadly, ZUN also uses *_and() if the range is *not* a power of two, and
/// *_mod() if the range *is* a power of two. That's why we still have to keep
/// separate *_and_*() and *_mod_*() functions.

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

// ZUN bloat
inline uint8_t randring2_next8_mod_ge_lt(uint8_t min, uint8_t max) {
	return (static_cast<int8_t>(min) >= 0)
		? (min + randring2_next16_mod(max - min))
		: (randring2_next16_mod(max + -static_cast<int8_t>(min)) - (-min));
}

inline uint8_t randring2_next8_ge_lt(uint8_t min, uint8_t max) {
	if(is_range_a_power_of_two(min, max)) {
		return randring2_next8_and_ge_lt(min, max);
	}
	return randring2_next8_mod_ge_lt(min, max);
}

inline int16_t randring2_next16_and_ge_lt(int16_t min, int16_t max) {
	return (min + randring2_next16_and((max - min) - 1));
}

// ZUN bloat
inline int16_t randring2_next16_mod_ge_lt(int16_t min, int16_t max) {
	return (min + randring2_next16_mod(max - min));
}

inline int16_t randring2_next16_ge_lt(int16_t min, int16_t max) {
	if(is_range_a_power_of_two(min, max)) {
		return randring2_next16_and_ge_lt(min, max);
	}
	return randring2_next16_mod_ge_lt(min, max);
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

	// ZUN bloat
	inline subpixel_t randring2_next16_mod_ge_lt_sp(float min, float max) {
		return randring2_next16_mod_ge_lt(to_sp(min), to_sp(max));
	}

	inline subpixel_t randring2_next16_ge_lt_sp(float min, float max) {
		return randring2_next16_ge_lt(to_sp(min), to_sp(max));
	}
#endif
/// --------------------------

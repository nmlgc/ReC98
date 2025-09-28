#include "platform.h"

#define max_macro(a, b) ( \
	(a > b) ? a : b \
)

// Yes, these are exactly what every tutorial presents as a bad example of C
// macros, especially if they are nested within each other.
// MODDERS: Turn into template functions.
#define clamp_max(v, max) ((v) < max ? (v) : max)
#define clamp_min(v, min) ((v) > min ? (v) : min)
#define clamp_max_2(v, max) ((v) > max ? max : (v))
#define clamp_min_2(v, min) ((v) < min ? min : (v))
#define clamp_max_2_ge(v, max) ((v) >= max ? max : (v))

#define clamp_minmax(v, min, max) { \
	if(v < min) { \
		v = min; \
	} else if(v > max) { \
		v = max; \
	} \
}

#define clamp_inc(v, max) \
	(v)++; \
	if((v) > (max)) { \
		(v) = (max); \
	}

#define clamp_dec(v, min) \
	(v)--; \
	if((v) < (min)) { \
		(v) = (min); \
	}

#ifdef __cplusplus
// This is, in fact, the only way to circumvent 16-bit promotion inside
// comparisons between two 8-bit values in C++. I kid you not.
static inline char ring_min() {
	return 0;
}
#else
#define ring_min() 0
#endif

#define ring_inc_range(val, ring_min, ring_max) { \
	(val)++; \
	if((val) > (ring_max)) { \
		(val) = (ring_min); \
	} \
}
#define ring_inc(val, ring_end) ring_inc_range(val, 0, ring_end)

#define ring_inc_ge(val, ring_end) \
	(val)++; \
	if((val) >= (ring_end)) { \
		(val) = 0; \
	}

#define ring_inc_ge_range(val, ring_min, ring_max) { \
	(val)++; \
	if((val) >= ((ring_max) + 1)) { \
		(val) = (ring_min); \
	} \
}

#if (GAME >= 4)
#define ring_dec_range(val, ring_min, ring_max) { \
	if(val == (ring_min)) { \
		(val) = ((ring_max) + 1); \
	} \
	(val)--; \
}
#else
#define ring_dec_range(val, ring_min, ring_max) { \
	if(val == (ring_min)) { \
		(val) = (ring_max); \
	} else { \
		(val)--; \
	} \
}
#endif

#define ring_dec(val, ring_end) \
	(val)--; \
	if(val < ring_min()) { \
		(val) = ring_end; \
	}

#define ring_dec_16(val, ring_end) \
	(val)--; \
	if(val < 0) { \
		(val) = ring_end; \
	}

#define ring_step(var, delta, min, max) { \
	uint8_t var_prev = var; \
	var = ((delta < 0) \
		? ((var_prev <= min) ? max : (var_prev + delta)) \
		: ((var_prev == max) ? min : (var_prev + delta)) \
	); \
}

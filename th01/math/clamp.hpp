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

#define ring_inc(val, ring_end) \
	(val)++; \
	if((val) > (ring_end)) { \
		(val) = 0; \
	}

#define ring_inc_ge(val, ring_end) \
	(val)++; \
	if((val) >= (ring_end)) { \
		(val) = 0; \
	}

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

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

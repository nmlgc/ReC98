// Yes, these are exactly what every tutorial presents as a bad example of C
// macros, especially if they are nested within each other.
// MODDERS: Turn into template functions.
#define clamp_max(v, max) ((v) < max ? (v) : max)
#define clamp_min(v, min) ((v) > min ? (v) : min)

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

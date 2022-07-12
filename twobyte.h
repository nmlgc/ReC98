// Used by various (dumb) pieces of code that require byte-wise access to
// 16-bit values.
typedef union {
	struct {
		int8_t lo, hi;
	} byte;
	uint8_t u[2];
	int16_t v;
} twobyte_t;

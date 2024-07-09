#include "platform.h"

// Equivalent to sprintf(str, "%*u", width, val).
void pascal str_right_aligned_from_uint16(
	char *str, uint16_t val, uint16_t width
);

// Equivalent to sprintf(str, "%d", val), if that function glitched out for
// negative numbers.
void pascal str_from_positive_int16(char *str, int16_t val);

#include "th01/math/str_val.hpp"

void str_right_aligned_from_uint16(char *str, uint16_t val, uint16_t width)
{
	uint16_t divisor = 10000;
	unsigned int i = width;
	bool past_leading_zeroes = false;

	while(i < 5) {
		divisor /= 10;
		i++;
	}
	for(i = 0; i < width; i++) {
		if(val / divisor) {
			past_leading_zeroes = true;
		}
		if(past_leading_zeroes) {
			str[i] = (val / divisor) + '0';
		} else {
			str[i] = ' ';
		}
		val %= divisor;
		divisor /= 10;
	}
	str[width] = '\0';
}

void str_from_positive_int16(char *str, int16_t val)
{
	int16_t divisor = 10000;
	int i;
	unsigned int str_p = 0;
	bool past_leading_zeroes = false;

	for(i = 0; i < 5; i++) {
		if(val / divisor) {
			past_leading_zeroes = true;
		}
		if(past_leading_zeroes) {
			str[str_p++] = (val / divisor) + '0';
		}
		val %= divisor;
		divisor /= 10;
	}
	str[str_p] = '\0';
}

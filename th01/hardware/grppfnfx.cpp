#include "th01/shiftjis/fwnum.hpp"

void graph_putfwnum_fx(
	screen_x_t left, vram_y_t top, int16_t col_and_fx, int digits,
	long num, long num_prev, bool16 put
)
{
	screen_x_t x = left;
	int divisor_i;
	int digit;
	int digit_prev;
	unsigned long divisor = 1;
	const shiftjis_t* FULLWIDTH_NUMERAL[10] = FULLWIDTH_NUMERALS;

	for(divisor_i = 0; divisor_i < digits; divisor_i++) {
		divisor *= 10;
	}
	do {
		divisor /= 10;
		if(x > (RES_X - GLYPH_FULL_W)) {
			return;
		}

		digit = ((num / divisor) % 10);
		digit_prev = ((num_prev / divisor) % 10);

		if(digit != 0) {
			put = true;
		}
		if(put && ((digit != digit_prev) || !num_prev)) {
			graph_putsa_fx(x, top, col_and_fx, FULLWIDTH_NUMERAL[digit]);
		}
		x += GLYPH_FULL_W;
	} while(divisor > 1);
}

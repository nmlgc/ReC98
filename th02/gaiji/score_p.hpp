#include "th02/score.h"

// ZUN bloat: The divisor can never be 0. This separate function is just meant
// to work around the resulting `Condition is always true/false` and
// `Unreachable code` warnings.
#ifndef gaiji_score_put
inline score_t gaiji_score_divide(
	const score_t& score, const score_t& divisor, bool check_divisor
) {
	if(check_divisor) {
		return (divisor ? ((score / divisor) % 10) : (score % 10));
	} else {
		return ((score / divisor) % 10);
	}
}
#endif

#define gaiji_score_put_update( \
	gaiji, past_leading_zeroes, divisor, digit, score, check_divisor \
) { \
	digit = gaiji_score_divide(score, divisor, check_divisor); \
	divisor /= 10; \
	gaiji = (gb_0_ + digit); \
	if(digit) { \
		past_leading_zeroes = true; \
	} \
}

#define gaiji_score_put(score, on_digit, check_divisor) { \
	/* ZUN bloat: Initialized inside the loop. */ \
	int gaiji = gb_0_; /* ACTUAL TYPE: gaiji_th02_t */ \
	\
	score_t divisor = 10000000; /* Must match SCORE_DIGITS! */ \
	score_t digit; \
	bool past_leading_zeroes = false; \
	for(int i = 0; i < SCORE_DIGITS; i++) { \
		gaiji_score_put_update( \
			gaiji, past_leading_zeroes, divisor, digit, score, check_divisor \
		); \
		if(past_leading_zeroes) { \
			on_digit(i, gaiji); \
		} \
	} \
}

// ZUN bloat: Could have been merged into the function above.
#define gaiji_score_put_digits(score, digits, on_digit) { \
	int i; \
	\
	/* ZUN bloat: Initialized inside the loop. */ \
	int gaiji = gb_0_; /* ACTUAL TYPE: gaiji_th02_t */ \
	\
	score_t divisor = 10000000; /* Must match SCORE_DIGITS! */ \
	score_t digit; \
	bool past_leading_zeroes = false; \
	\
	for(i = SCORE_DIGITS; i > digits; i--) { \
		divisor /= 10; \
	} \
	for(i = 0; i < digits; i++) { \
		gaiji_score_put_update( \
			gaiji, past_leading_zeroes, divisor, digit, score, false \
		); \
		if(i == (digits - 1)) { \
			past_leading_zeroes = true; \
		} \
		if(past_leading_zeroes) { \
			on_digit(i, gaiji); \
		} \
	} \
}

// ZUN bloat: Also equivalent to the first function.
#define gaiji_score_put_to(left, score, on_digit_at) { \
	int gaiji; /* ACTUAL TYPE: gaiji_th02_t */ \
	score_t divisor = 10000000; /* Must match SCORE_DIGITS! */ \
	score_t digit; \
	bool past_leading_zeroes = false; \
	tram_x_t x = left; \
	while(x < (left + (SCORE_DIGITS * GAIJI_TRAM_W))) { \
		gaiji_score_put_update( \
			gaiji, past_leading_zeroes, divisor, digit, score, false \
		); \
		if(past_leading_zeroes) { \
			on_digit_at(x, gaiji); \
		} \
		x += GAIJI_TRAM_W; \
	} \
}

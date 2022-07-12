#include "th02/score.h"

typedef union {
	unsigned char continues_used;
	unsigned char digits[SCORE_DIGITS];
} score_lebcd_t;

extern score_lebcd_t score;

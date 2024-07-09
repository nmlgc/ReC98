#ifndef TH04_SCORE_H
#define TH04_SCORE_H

#include "th02/score.h"

typedef union {
	unsigned char continues_used;
	unsigned char digits[SCORE_DIGITS];
} score_lebcd_t;

extern score_lebcd_t score;

#endif /* TH04_SCORE_H */

#include "planar.h"

// Using the same naming convention as for the gaiji characters...
typedef enum {
	pl_F = 0,
	pl_M = 1,
	pl_1 = 2,
	pl_2 = 3,
	pl_3 = 4,
	pl_4 = 5,
	pl_5 = 6,
	pl_S = 7,
	pl_G = 8,
	pl_COUNT,
} piano_label_t;

#define PIANO_LABEL_FONT_W 8
#define PIANO_LABEL_FONT_H 8

extern const dot_rect_t(
	PIANO_LABEL_FONT_W, PIANO_LABEL_FONT_H
) sPIANO_LABEL_FONT[pl_COUNT];

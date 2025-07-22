// Fork banner
// -----------

#include "pc98.h"

static const uint16_t FBA_LEFT   = 0x0;
static const uint16_t FBA_RIGHT  = 0x1;
static const uint16_t FBA_TOP    = 0x0;
static const uint16_t FBA_BOTTOM = 0x2;

void pascal forkbanner_put(
	screen_x_t x, screen_y_t y, uint16_t align, int16_t col_and_fx
);

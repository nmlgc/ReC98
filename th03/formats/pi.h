#include "th02/formats/pi.h"

#define PI_MASK_COUNT 4
#define PI_MASK_H 4
extern const dots16_t PI_MASKS[PI_MASK_COUNT][PI_MASK_H];

// Like pi_put_8(), but only displays every second row in the given PI.
void pascal pi_put_interlace_8(screen_x_t left, vram_y_t top, int slot);

// Like pi_put_8(), but only displays the n-th 320x200 [quarter], counted
// from the top left, of the PI image in slot #[slot] at ([left], [top]).
void pascal pi_put_quarter_8(
	screen_x_t left, vram_y_t top, int slot, int quarter
);

static const pixel_t PI_QUARTER_W = (PI_W / 2);
static const pixel_t PI_QUARTER_H = (PI_H / 2);

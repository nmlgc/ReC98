#include "th02/formats/pi.h"

#define PI_MASK_COUNT 4
#define PI_MASK_H 4
extern const dots16_t PI_MASKS[PI_MASK_COUNT][PI_MASK_H];

// Like pi_put(), but only displays every second row in the given PI.
int pascal pi_put_interlace(screen_x_t left, vram_y_t top, int slot);

// Like pi_put(), but only displays the n-th 320x200 [quarter], counted
// from the top left, of the PI image in slot #[slot] at ([left], [top]).
int pascal pi_put_quarter(
	screen_x_t left, vram_y_t top, int slot, int quarter
);

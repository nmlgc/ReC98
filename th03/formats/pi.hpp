#include "th02/formats/pi.h"
#include "planar.h"

// Like pi_put_8(), but only displays every second row in the given PI.
void pascal pi_put_interlace_8(screen_x_t left, vram_y_t top, int slot);

// Like pi_put_8(), but only displays the n-th 320x200 [quarter], counted
// from the top left, of the PI image in slot #[slot] at ([left], [top]).
void pascal pi_put_quarter_8(
	screen_x_t left, vram_y_t top, int slot, int quarter
);

#include "th02/formats/pi.h"
#include "planar.h"

// Like pi_put_8(), but only displays every second row in the given PI.
void pascal pi_put_interlace_8(screen_x_t left, vram_y_t top, int slot);

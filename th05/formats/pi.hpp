#include "th03/formats/pi.hpp"

#undef pi_free
void pascal pi_free(int slot);

// Like pi_put_8() and pi_put_quarter_8(), but applying the mask with the given
// ID while blitting.
void pascal pi_put_masked_8(
	screen_x_t left, vram_y_t top, int slot, int mask_id
);
void pascal pi_put_quarter_masked_8(
	screen_x_t left, vram_y_t top, int slot, int quarter, int mask_id
);

#include "th03/formats/pi.h"

#undef pi_free
int pascal pi_free(int slot);

// Like pi_put_8() and pi_put_quarter_8(), but applying the mask with the given
// ID while blitting.
int pascal pi_put_masked_8(
	screen_x_t left, vram_y_t top, int slot, int mask_id
);
int pascal pi_put_quarter_masked_8(
	screen_x_t left, vram_y_t top, int slot, int quarter, int mask_id
);

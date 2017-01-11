#include "th03/formats/pi.h"

int pascal pi_free(int slot);

// Like pi_put() and pi_put_quarter(), but applying the mask with the given ID
// while blitting.
int pascal pi_put_mask(screen_x_t left, vram_y_t top, int slot, int mask_id);
int pascal pi_put_quarter_mask(
	screen_x_t left, vram_y_t top, int slot, int quarter, int mask_id
);

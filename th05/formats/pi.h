#include "th03/formats/pi.h"

int pascal pi_free(int slot);

#undef pi_load_put_8_free

static inline void pi_load_put_8_free(int slot, const char *fn) {
	pi_load(slot, fn);
	pi_palette_apply(slot);
	pi_put_8(0, 0, slot);
	pi_free(0);
}

// Like pi_put_8() and pi_put_quarter_8(), but applying the mask with the given
// ID while blitting.
int pascal pi_put_mask_8(screen_x_t left, vram_y_t top, int slot, int mask_id);
int pascal pi_put_quarter_mask_8(
	screen_x_t left, vram_y_t top, int slot, int quarter, int mask_id
);

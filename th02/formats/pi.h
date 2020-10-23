#include "defconv.h"

#if GAME == 5
# define PI_SLOT_COUNT 8
#else
# define PI_SLOT_COUNT 6
#endif

// Global PI file slots.
extern PiHeader pi_headers[PI_SLOT_COUNT];
extern void far *pi_buffers[PI_SLOT_COUNT];

// ≥TH03 free any previously loaded PI in the given slot before loading [fn].
int DEFCONV pi_load(int slot, const char *fn);

void DEFCONV pi_palette_apply(int slot);

// Displays the PI image in slot #[slot] at (⌊left/8⌋*8, top). Horizontally,
// the image is cut off at 640 pixels; vertically, it is wrapped if it exceeds
// the clipping frame defined via grc_setclip().
void DEFCONV pi_put_8(screen_x_t left, vram_y_t top, int slot);

#define pi_load_put_8_free(slot, fn) \
	pi_load(slot, (fn)); \
	pi_palette_apply(slot); \
	pi_put_8(0, 0, slot); \
	graph_pi_free(&pi_headers[slot], pi_buffers[slot]);

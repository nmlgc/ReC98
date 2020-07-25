#include "defconv.h"

#if GAME == 5
# define PI_COUNT 8
#else
# define PI_COUNT 6
#endif

// Global PI file slots.
extern PiHeader pi_slot_headers[PI_COUNT];
extern void far *pi_slot_buffers[PI_COUNT];

// ≥TH03 free any previously loaded PI in the given slot before loading [fn].
int DEFCONV pi_slot_load(int slot, const char *fn);

void DEFCONV pi_slot_palette_apply(int slot);

// Displays the PI image in slot #[slot] at ([left], [top]). Horizontally, the
// image is cut off at 640 pixels; vertically, it is wrapped if it exceeds the
// clipping frame defined via grc_setclip().
void DEFCONV pi_slot_put(int left, int top, int slot);

#define pi_load_put_free(slot, fn) \
	pi_slot_load(slot, (fn)); \
	pi_slot_palette_apply(slot); \
	pi_slot_put(0, 0, slot); \
	graph_pi_free(&pi_slot_headers[slot], pi_slot_buffers[slot]);

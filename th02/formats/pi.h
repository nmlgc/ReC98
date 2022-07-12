#include "defconv.h"

#if GAME == 5
	#define PI_SLOT_COUNT 8
#else
	#define PI_SLOT_COUNT 6
#endif

#define PI_W RES_X
#define PI_H RES_Y

// Global PI file slots.
extern PiHeader pi_headers[PI_SLOT_COUNT];
extern void far *pi_buffers[PI_SLOT_COUNT];

// ≥TH03 free any previously loaded PI in the given slot before loading [fn].
int DEFCONV pi_load(int slot, const char *fn);

void DEFCONV pi_palette_apply(int slot);

#define pi_free(slot) \
	graph_pi_free(&pi_headers[slot], pi_buffers[slot]);

// Displays the PI image in slot #[slot] at (⌊left/8⌋*8, top). Horizontally,
// the image is cut off at 640 pixels; vertically, it is wrapped if it exceeds
// the clipping frame defined via grc_setclip().
void DEFCONV pi_put_8(screen_x_t left, vram_y_t top, int slot);

#define pi_load_put_8_free(slot, fn) \
	pi_load(slot, (fn)); \
	pi_palette_apply(slot); \
	pi_put_8(0, 0, slot); \
	pi_free(slot); \

// .PI row pointer arithmetic
// --------------------------

typedef uint8_t far *pi_buffer_p_t;

#define pi_buffer_p_init(p, slot) \
	p = reinterpret_cast<pi_buffer_p_t>(pi_buffers[slot]);

#define pi_buffer_p_offset(p, x, y) \
	p += (((y * PI_W) + x) / 2);

#define pi_buffer_p_normalize(p) \
	p = reinterpret_cast<pi_buffer_p_t>(MK_FP( \
		(seg_t)(reinterpret_cast<uint32_t>(p) >> 16) + (FP_OFF(p) >> 4), \
		(FP_OFF(p) & 0xF) \
	));

#define pi_buffer_p_next_row(p, slot) \
	pi_buffer_p_offset(p, pi_headers[slot].xsize, 0);
// --------------------------

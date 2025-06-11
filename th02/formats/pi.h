#include "libs/master.lib/pc98_gfx.hpp"
#include "defconv.h"

static const int PI_SLOT_COUNT = ((GAME == 5) ? 8 : 6);

#define PI_W RES_X
#define PI_H RES_Y

#if ((GAME <= 3) && (BINARY == 'M'))
// Global PI file slots.
extern PiHeader pi_headers[PI_SLOT_COUNT];
extern void far *pi_buffers[PI_SLOT_COUNT];

#define pi_free(slot) \
	graph_pi_free(&pi_headers[slot], pi_buffers[slot]);
#else
void pascal pi_free(int slot);
#undef DEFCONV
#define DEFCONV pascal
#endif

// ≥TH03 free any previously loaded PI in the given slot before loading [fn].
int DEFCONV pi_load(int slot, const char *fn);

// Temporary wrapper around line-skipped surface loading.
int pascal pi_load_lineskip(int slot, const char *fn);

void DEFCONV pi_palette_apply(int slot);

// Displays the PI image in slot #[slot] at (⌊left/8⌋*8, top). Horizontally,
// the image is cut off at 640 pixels; vertically, it is wrapped if it exceeds
// the clipping frame defined via grc_setclip().
void DEFCONV pi_put_8(screen_x_t left, vram_y_t top, int slot);

// .PI row pointer arithmetic
// --------------------------

typedef uint8_t far *pi_buffer_p_t;

#define pi_buffer_p_init(p, slot) \
	p = reinterpret_cast<pi_buffer_p_t>(pi_buffers[slot]);

#define pi_buffer_p_offset(p, x, y) \
	/* Carefully avoiding overflows… */ \
	p += ((y * (PI_W / 2u)) + (x / 2u));

#define pi_buffer_p_normalize(p) \
	p = reinterpret_cast<pi_buffer_p_t>(MK_FP( \
		(seg_t)(reinterpret_cast<uint32_t>(p) >> 16) + (FP_OFF(p) >> 4), \
		(FP_OFF(p) & 0xF) \
	));

#define pi_buffer_p_next_row(p, slot) \
	pi_buffer_p_offset(p, pi_headers[slot].xsize, 0);
// --------------------------

#undef DEFCONV
#include "defconv.h"

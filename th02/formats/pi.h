#include "libs/master.lib/pc98_gfx.hpp"
#include "defconv.h"

static const int PI_SLOT_COUNT = ((GAME == 5) ? 8 : 6);

#define PI_W RES_X
#define PI_H RES_Y

static const int PI_QUARTER_COUNT = 4;
static const pixel_t PI_QUARTER_W = (PI_W / 2);
static const pixel_t PI_QUARTER_H = (PI_H / 2);

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

#define pi_fullres_load_put_free(slot, fn) { \
	pi_load(slot, fn); \
	pi_put_8(0, 0, slot); \
	pi_free(slot); \
}

#define pi_fullres_load_palette_apply_put_free(slot, fn) { \
	pi_load(slot, fn); \
	pi_palette_apply(slot); \
	pi_put_8(0, 0, slot); \
	pi_free(slot); \
}

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

#define pi_buffer_p_init_quarter(p, slot, quarter) { \
	pi_buffer_p_init(p, slot); \
	if(quarter == 1) { \
		pi_buffer_p_offset(p, PI_QUARTER_W, 0); \
	} else if(quarter == 2) { \
		pi_buffer_p_offset(p, 0, PI_QUARTER_H); \
	} else if(quarter == 3) { \
		pi_buffer_p_offset(p, PI_QUARTER_W, PI_QUARTER_H); \
	} \
	pi_buffer_p_normalize(p); \
}
// --------------------------

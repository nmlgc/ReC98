// High-level overview of the differences between the three games that can't be
// easily abstracted away:
//
// 1) TH03 and TH04 allocate dedicated memory for backing up the text box area
//    in VRAM ([box_bg]), TH05 uses the bgimage system instead.

#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "master.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
#if (GAME == 5)
	#include "th01/hardware/egc.h"
	#include "th05/formats/pi.hpp"
#elif (GAME == 4)
	#include "th03/formats/pi.hpp"
#else
	#include "th03/formats/pi.hpp"
#endif
}
#include "th03/cutscene/cutscene.hpp"

// Constants
// ---------

static const pixel_t PIC_W = PI_QUARTER_W;
static const pixel_t PIC_H = PI_QUARTER_H;

static const vram_byte_amount_t PIC_VRAM_W = (PIC_W / BYTE_DOTS);

static const int PIC_SLOT = 0;
// ---------

// State
// -----

#if (GAME >= 4)
	// Statically allocated. MODDERS: TH03's dynamic allocation was better than
	// hardcoding a maximum size...
	extern unsigned char script[8192];

	extern unsigned char near *script_p;
#else
	// Dynamically allocated.
	extern unsigned char far *script;

	#define script_p script
#endif

extern uint4_t text_col;
extern uint8_t text_fx; // TH04 and TH05 directly set [graph_putsa_fx_func].
extern int script_number_param_default;
// -----

// Function ordering fails
// -----------------------

#if (GAME == 5)
	// Waits the given amount of frames (0 = forever) for the OK, Shot, or
	// Cancel button to be pressed, while showing the ⏎ Return key animation
	// in a blocking way.
	void pascal near box_wait_animate(int frames_to_wait = 0);
#else
	void near box_bg_allocate_and_snap(void);
	void near box_bg_free(void);
#endif
#if (GAME >= 4)
	// Crossfades the text box area from VRAM page 1 to VRAM page 0, spending
	// [text_interval] frames on each step.
	void near box_1_to_0_animate(void);
#endif
// -----------------------

bool16 pascal near cutscene_script_load(const char* fn)
{
	cutscene_script_free();

	if(!file_ropen(fn)) {
		return true;
	}
	size_t size = file_size();
	#if (GAME >= 4)
		// PORTERS: Required for TH03 on flat memory models as well.
		// ZUN bug: Missing an error check if [size] >= sizeof(script);
		script_p = static_cast<unsigned char near *>(script);
	#else
		script = reinterpret_cast<unsigned char far *>(hmem_allocbyte(size));
	#endif
	file_read(script_p, size);
	file_close();
	return false;
}

#if (GAME <= 4)
	void near cutscene_script_free(void)
	{
		#if (GAME == 3)
			if(script) {
				HMem<unsigned char>::free(script);
				script = nullptr;
			}
		#endif
	}
#endif

// ZUN bloat: Turn into a single global inline function.
#define egc_start_copy	near egc_start_copy
#include "th01/hardware/egcstart.cpp"
#undef egc_start_copy

#if (GAME == 5)
	#define pic_copy_to_other(left, top) { \
		egc_copy_rect_1_to_0_16(left, top, PIC_W, PIC_H); \
	}

	void pascal near pic_put_both_masked(
		screen_x_t left, vram_y_t top, int quarter, int mask_id
	)
	{
		graph_accesspage(1);
		pi_put_quarter_masked_8(left, top, PIC_SLOT, quarter, mask_id);
		pic_copy_to_other(left, top);
	}
#else
	void pascal near pic_copy_to_other(screen_x_t left, vram_y_t top)
	{
		vram_offset_t vo = vram_offset_shift(left, top);
		pixel_t y;
		vram_byte_amount_t vram_x;

		egc_start_copy();

		// Faster than TH01's very slow end_pic_show() version, but still not
		// as optimal as you can get within the EGC's limited 16-dot tile
		// register.
		y = 0;
		while(y < PIC_H) {
			vram_x = 0;
			while(vram_x < PIC_VRAM_W) {
				egc_temp_t tmp;

				graph_accesspage(0);	tmp = egc_chunk(vo);
				graph_accesspage(1);	egc_chunk(vo) = tmp;

				vram_x += EGC_REGISTER_SIZE;
				vo += EGC_REGISTER_SIZE;
			}
			y++;
			vo += (ROW_SIZE - PIC_VRAM_W);
		}
		egc_off();

		// ZUN bloat: All blitting operations in this module access the
		// intended page before they blit. That's why preliminary state
		// changes like this one are completely redundant, thankfully.
		graph_accesspage(0);
	}

	void pascal near pic_put_both_masked(
		screen_x_t left, vram_y_t top, int quarter, int mask_id
	)
	{
		enum {
			TEMP_ROW = RES_Y,
		};

		vram_word_amount_t vram_word;
		vram_offset_t vo_temp;
		pi_buffer_p_t row_p;

		pi_buffer_p_init_quarter(row_p, PIC_SLOT, quarter);

		graph_showpage(1);
		vram_offset_t vo = vram_offset_shift(left, top);
		graph_accesspage(0);
		for(pixel_t y = 0; y < PIC_H; y++) {
			// This might actually be faster than clearing the masked pixels
			// using the GRCG and doing an unaccelerated 4-plane VRAM OR.
			graph_pack_put_8_noclip(0, TEMP_ROW, row_p, PIC_W);
			egc_start_copy();
			egc_setup_copy_masked(PI_MASKS[mask_id][y & (PI_MASK_COUNT - 1)]);
			vo_temp = vram_offset_shift(0, TEMP_ROW);
			vram_word = 0;
			while(vram_word < (PIC_W / EGC_REGISTER_DOTS)) {
				egc_chunk(vo) = egc_chunk(vo_temp);
				vram_word++;
				vo += EGC_REGISTER_SIZE;
				vo_temp += EGC_REGISTER_SIZE;
			}
			egc_off();

			vo += (ROW_SIZE - PIC_VRAM_W);
			pi_buffer_p_offset(row_p, PI_W, 0);
			pi_buffer_p_normalize(row_p);
		}
		graph_showpage(0);
		pic_copy_to_other(left, top);
	}

	#define box_bg_snap_func(p, vo) { \
		(&box_bg->B)[p++] = VRAM_CHUNK(B, vo, 16); \
		(&box_bg->B)[p++] = VRAM_CHUNK(R, vo, 16); \
		(&box_bg->B)[p++] = VRAM_CHUNK(G, vo, 16); \
		(&box_bg->B)[p++] = VRAM_CHUNK(E, vo, 16); \
	}

	#define box_bg_put_func(p, vo) { \
		VRAM_CHUNK(B, vo, 16) = (&box_bg->B)[p++]; \
		VRAM_CHUNK(R, vo, 16) = (&box_bg->B)[p++]; \
		VRAM_CHUNK(G, vo, 16) = (&box_bg->B)[p++]; \
		VRAM_CHUNK(E, vo, 16) = (&box_bg->B)[p++]; \
	}

	#define box_bg_loop(func) /* No braces due to local variable layout */ \
		size_t p; \
		vram_y_t src_y; \
		screen_x_t src_x; \
		pixel_t dst_y; \
		vram_byte_amount_t dst_byte; \
		vram_offset_t vo; \
		\
		p = 0; \
		src_y = BOX_TOP; \
		dst_y = 0; \
		while(dst_y < BOX_H) { \
			src_x = BOX_LEFT; \
			dst_byte = 0; \
			while(dst_byte < BOX_VRAM_W) { \
				vo = vram_offset_shift(src_x, src_y); \
				func(p, vo); \
				dst_byte += static_cast<vram_byte_amount_t>(sizeof(dots16_t)); \
				src_x += 16; \
			} \
			dst_y++; \
			src_y++; \
		}

	void near box_bg_allocate_and_snap(void)
	{
		box_bg_free();
		graph_accesspage(0);
		box_bg = HMem< Planar<dots16_t> >::alloc(
			((BOX_VRAM_W * BOX_H) / sizeof(dots16_t))
		);
		box_bg_loop(box_bg_snap_func);
	}

	void near box_bg_free(void)
	{
		if(box_bg) {
			HMem< Planar<dots16_t> >::free(box_bg);
			box_bg = nullptr;
		}
	}

	void near box_bg_put(void)
	{
		box_bg_loop(box_bg_put_func);
	}
#endif

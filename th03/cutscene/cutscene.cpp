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
}
#include "th03/formats/pi.hpp"
#include "th03/cutscene/cutscene.hpp"

// Constants
// ---------

static const pixel_t PIC_W = PI_QUARTER_W;
static const pixel_t PIC_H = PI_QUARTER_H;

static const vram_byte_amount_t PIC_VRAM_W = (PIC_W / BYTE_DOTS);
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

#if (GAME <= 4)
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
#endif

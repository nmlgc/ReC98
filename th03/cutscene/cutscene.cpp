// High-level overview of the differences between the three games that can't be
// easily abstracted away:
//
// 1) TH03 and TH04 allocate dedicated memory for backing up the text box area
//    in VRAM ([box_bg]), TH05 uses the bgimage system instead.

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "master.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
}
#include "th03/cutscene/cutscene.hpp"

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

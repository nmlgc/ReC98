// High-level overview of the differences between the three games that can't be
// easily abstracted away:
//
// 1) TH03 and TH04 allocate dedicated memory for backing up the text box area
//    in VRAM ([box_bg]), TH05 uses the bgimage system instead.

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "master.hpp"

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

#if (GAME >= 4)
	// Crossfades the text box area from VRAM page 1 to VRAM page 0, spending
	// [text_interval] frames on each step.
	void near box_1_to_0_animate(void);
#endif
// -----------------------

// VBLANK operations
// -----------------

#include "platform.h"

// Returns `true` if the display is within its vertical blanking period.
bool pascal vblank_in(void);

// Runs [func] either right now if we're in VBLANK, or once after the next
// VSync.
void pascal vblank_run(func_t func);

// Removes any pending VBLANK function previously set with vblank_run().
void vblank_flush_func_queue(void);

// Sets master.lib's [PaletteTone] to 0 and clears TRAM.
// This is a very common operation to be run during VBLANK on screen
// transitions, so it deserves a central implementation here.
void pascal vblank_palette_black_and_tram_wipe(void);

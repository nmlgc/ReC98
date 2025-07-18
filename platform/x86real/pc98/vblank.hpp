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

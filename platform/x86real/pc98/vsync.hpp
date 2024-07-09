// VSync interrupts
// ----------------

#include "platform.h"

// Incremented by 1 on every VSync interrupt. Can be manually reset to 0 to
// simplify frame delay loops.
extern volatile uint16_t vsync_count_16;
extern volatile uint32_t vsync_count_32;

// Sets up a VSync interrupt that increments [vsync_count_16] and
// [vsync_count_32] every time it's called. Also registers vsync_exit() to be
// called at process termination.
void __cdecl vsync_init(void);

// Removes the VSync interrupt handler set up by vsync_init().
void __cdecl vsync_exit(void);

bool vsync_is_active(void);

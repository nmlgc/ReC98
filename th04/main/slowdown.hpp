#include "platform.h"

extern bool turbo_mode;

// Number of VSync events to wait for at the end of the current frame.
extern unsigned int slowdown_factor;

#if (GAME == 5)
// Only written to in Slow Mode.
extern bool slowdown_caused_by_bullets;
#endif

// Blocks until the number of VSync events given in [slowdown_factor] have
// occurred, then resets the [slowdown_factor] to 1.
void near slowdown_frame_delay(void);

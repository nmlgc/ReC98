#include "platform.h"

extern bool palette_changed;

// Updates the actual hardware palette at the end of the frame.
#define palette_settone_deferred(tone) { \
	PaletteTone = tone; \
	palette_changed = true; \
}

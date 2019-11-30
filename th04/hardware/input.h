#include "th04/hardware/inputvar.h"

// Resets and updates [key_det].
void input_reset_sense();

// ORs the current keyboard and joystick state into [key_det], and sets
// [shiftkey].
void input_sense();

// Waits ≥1 frames for all held inputs to be released, then waits the given
// number of [frames] for an input to be pressed. Set [frames] to 0 or 9999
// to wait forever.
void pascal input_wait_for_change(int frames);

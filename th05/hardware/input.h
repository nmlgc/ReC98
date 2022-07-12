#include "th04/hardware/inputvar.h"

// Resets, updates, and returns [key_det].
int16_t input_reset_sense();

// input_reset_sense() with accurate detection of held keyboard keys.
int16_t input_reset_sense_held();

// ORs the current keyboard and joystick state into [key_det], sets
// [shiftkey], and returns [key_det].
int16_t input_sense();

// Input sense function used in UIs
#define input_reset_sense_interface input_reset_sense_held

// Waits for all held inputs to be released, then waits the given number of
// [frames] for an input to be pressed. Set [frames] to 0 to wait forever.
// Returns garbage.
int16_t pascal input_wait_for_change(int frames);

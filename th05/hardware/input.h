#include "th04/hardware/inputvar.h"

#define INPUT_REPLAY_END (~INPUT_MOVEMENT)

// Resets, updates, and returns [key_det].
int input_reset_sense();

// input_reset_sense() with accurate detection of held keyboard keys.
int input_reset_sense_held();

// ORs the current keyboard and joystick state into [key_det], sets
// [shiftkey], and returns [key_det].
int input_sense();

// Waits for all held inputs to be released, then waits the given number of
// [frames] for an input to be pressed and returns [key_det].
// Set [frames] to 0 to wait forever.
int pascal input_wait_for_change(int frames);

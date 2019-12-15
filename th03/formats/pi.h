#include "th02/formats/pi.h"

// Like pi_slot_put(), but only displays every second row in the given PI.
int pascal pi_slot_put_interlace(int x, int y, int slot);

// Displays the n-th 320x200 [quarter], counted from the top left, of the PI
// image in slot #[slot] at ([x], [y]).
int pascal pi_slot_put_quarter(int x, int y, int slot, int quarter);

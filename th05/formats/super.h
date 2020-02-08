#include "th04/formats/super.h"

// Displays the alpha plane of the (non-tiny!) 16x16 sprite with the given
// [patnum] using the current GRCG tile/color.
#define z_super_roll_put_16x16_mono(left, top, patnum) \
	_AX = top; \
	_CX = left; \
	z_super_roll_put_16x16_mono_raw(patnum);
void z_pascal near z_super_roll_put_16x16_mono_raw(int patnum);

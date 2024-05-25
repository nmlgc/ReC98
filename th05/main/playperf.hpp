#include "th04/main/playperf.hpp"
#include "th01/math/subpixel.hpp"

#pragma codeseg BULLET_A_TEXT

extern "C" {
// Returns [speed] tuned based on [playperf].
subpixel_length_8_t __fastcall near playperf_speedtune(
	subpixel_length_8_t speed
);
}

#pragma codeseg

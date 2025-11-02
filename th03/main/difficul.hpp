// Values that determine the difficulty of a gameplay round. The original game
// sets these based on the selected difficulty level, and uses different values
// during demos.

#include "th01/math/subpixel.hpp"

// An increasing variable factored into various velocity calculations.
extern subpixel_length_8_t round_speed;

static const subpixel_length_8_t ROUND_SPEED_MAX = TO_SP(8);

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "th04/main/playfld.hpp"
#include "th04/main/bullet/bullet.hpp"
#include "th05/sprites/main_pat.h"

#pragma option -k-

// The function calculates a 16-bit return value, every call site assigns the
// result to a 16-bit variable, but ZUN still declared an 8-bit return type...
unsigned char pascal near bullet_patnum_for_angle(
	unsigned int patnum_base_, unsigned char angle
)
{
	#define angle_low  	static_cast<unsigned char>(_AL)
	#define angle_high 	static_cast<unsigned char>(_AH)
	#define angle_wide 	static_cast<unsigned int>(_AX)
	#define patnum_base	static_cast<unsigned int>(_BX)

	_BX = _SP;
	angle_low = peekb(_SS, (_BX + 2)); /* = */ (angle);
	patnum_base = peek(_SS, (_BX + 4)); /* = */ (patnum_base_);
	// Offset by half of the per-sprite angle
	angle_low += ((ANGLE_PER_SPRITE / 2) - 1);

	// Yes, this is intended to also cover Yumeko's swords, which start
	// at a patnum higher than PAT_BULLET16_V. Make sure it stays that way.
	sizeof(char[1 - 2*!(PAT_SWORD > PAT_BULLET16_V)]);
	if(patnum_base < PAT_BULLET16_V) {
		angle_low &= (0x80 - 1);
	}

	angle_high ^= angle_high;
	angle_low >>= 3; // /= ANGLE_PER_SPRITE;
	angle_wide += patnum_base;
	return angle_wide;

	#undef patnum_base
	#undef angle_wide
	#undef angle_high
	#undef angle_low
}
#pragma codestring "\x90"

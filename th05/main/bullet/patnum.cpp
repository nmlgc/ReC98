#include "th04/main/bullet/bullet.hpp"
#include "th05/sprites/main_pat.h"

#pragma option -k-

unsigned int pascal near bullet_patnum_for_angle(
	unsigned int patnum_base, unsigned char angle
)
{
	// Offset by half of the per-sprite angle
	angle += ((ANGLE_PER_SPRITE / 2) - 1);

	// Yes, this is intended to also cover Yumeko's swords, which start
	// at a patnum higher than PAT_BULLET16_V. Make sure it stays that way.
	static_assert(PAT_SWORD > PAT_BULLET16_V);
	if(patnum_base < PAT_BULLET16_V) {
		angle %= 0x80u;
	}

	return (patnum_base + (angle / ANGLE_PER_SPRITE));
}
#pragma codestring "\x90"

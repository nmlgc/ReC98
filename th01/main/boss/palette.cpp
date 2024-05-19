#include "platform.h"
#include "th01/hardware/palette.h"

#include "th01/main/boss/palette.hpp"

void boss_palette_snap(void)
{
	svc2 col;
	int comp;
	palette_copy(boss_palette, z_Palettes, col, comp);
}

void boss_palette_show(void)
{
	z_palette_set_all_show(boss_palette);
}

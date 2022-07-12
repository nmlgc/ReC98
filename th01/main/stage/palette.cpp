#include "th01/main/stage/palette.hpp"

void stage_palette_set(const Palette4 &pal)
{
	int col;
	int comp;
	palette_copy(stage_palette, pal, col, comp);
}

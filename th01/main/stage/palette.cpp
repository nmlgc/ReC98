#include "th01/main/stage/palette.hpp"

void stage_palette_set(const Palette4 &pal)
{
	for(int col = 0; col < COLOR_COUNT; col++) {
		for(int comp = 0; comp < COMPONENT_COUNT; comp++) {
			stage_palette[col].v[comp] = pal[col].v[comp];
		}
	}
}

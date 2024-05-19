#pragma option -zPmain_01

#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th04/main/playfld.hpp"
#include "th04/main/scroll.hpp"
#include "th04/main/tile/tile.hpp"

void pascal tile_ring_set_vo(
	subpixel_t x_, subpixel_t y_, vram_offset_t image_vo
)
{
	pixel_t x = x_;
	vram_y_t y = y_;

	x = (x >> SUBPIXEL_BITS);

	// ZUN bloat: Might as well just call scroll_subpixel_y_to_vram_always(),
	// even though it's in another segment.
	bool scroll_active_saved = scroll_active;
	scroll_active = true;

	y = scroll_subpixel_y_to_vram_seg1(to_sp(PLAYFIELD_TOP) + y);
	tile_ring[y / TILE_H][x / TILE_W] = image_vo;

	scroll_active = scroll_active_saved;
}

#include "th03/main/player/exatt.hpp"

void pascal exatt_add(Subpixel center_x_, Subpixel center_y_, pid_t pid)
{
	// ZUN bloat: Bloat within bloat!
	subpixel_t center_x = center_x_;
	subpixel_t center_y = center_y_;

	static_assert(PLAYER_COUNT == 2);
	if(pid == 0) {
		exatt_funcs[0].add(center_x, center_y, 0);
	} else {
		exatt_funcs[1].add(center_x, center_y, 1);
	}
}

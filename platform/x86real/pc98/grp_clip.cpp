// PC-98 VRAM clipping region
// --------------------------

#include "platform/grp_clip.hpp"

LTRB<vram_x_t, screen_y_t> GrpClip = { 0, 0, ROW_SIZE, RES_Y };

void Grp_SetClip(const LTRB<screen_x_t, screen_y_t> *region)
{
	if(!region) {
		GrpClip.left = 0;
		GrpClip.top = 0;
		GrpClip.right = ROW_SIZE;
		GrpClip.bottom = RES_Y;
	} else {
		GrpClip.left = (region->left >> BYTE_BITS);
		GrpClip.top = region->top;
		GrpClip.right = (region->right >> BYTE_BITS);
		GrpClip.bottom = region->bottom;
	}
}

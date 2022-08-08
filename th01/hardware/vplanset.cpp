#pragma option -zCSHARED

#include "platform.h"
#include "pc98.h"
#include "planar.h"
extern "C" {
#include "th01/hardware/vplanset.h"
}

void vram_planes_set(void)
{
	VRAM_PLANE_B = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_B);
	VRAM_PLANE_R = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_R);
	VRAM_PLANE_G = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_G);
	VRAM_PLANE_E = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_E);
}

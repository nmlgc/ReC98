#include "th04/main/frames.h"
#include "th04/main/null.hpp"
#include "th04/main/midboss/midboss.hpp"

void midboss_reset(void)
{
	midboss_invalidate = nullfunc_near;
	midboss_render = nullfunc_near;
	midboss_update = nullfunc_far;
	#if (GAME == 4)
		midboss_active = false;
	#endif
	midboss.hp = 0;
}

void midboss_activate_if_stage_frame_is_midboss_start_frame(void)
{
	_asm {
		nop; nop; nop; nop; nop; nop; nop; nop; nop;
		nop; nop; nop; nop; nop; nop; nop; nop; nop;
		nop; nop; nop; nop; nop; nop; nop; nop; nop;
		nop; nop; nop; nop; nop; nop; nop; nop; nop;
		nop; nop; nop; nop; nop; nop; nop; nop; nop;
	}
}

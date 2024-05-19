#include "platform.h"
#include "pc98.h"
#include "th04/main/frames.h"
#include "th04/main/null.hpp"
#include "th04/main/playfld.hpp"
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
	if(midboss.frames_until == stage_frame) {
		midboss_invalidate = midboss_invalidate_func;
		midboss_render = midboss_render_func;
		midboss_update = midboss_update_func;
		midboss.phase = 0;
		midboss.phase_frame = 0;
		midboss_active = true;
	}
}

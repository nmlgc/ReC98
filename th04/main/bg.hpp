// Background rendering function pointers.

#include "platform.h"

extern nearfunc_t_near bg_render_not_bombing;
extern nearfunc_t_near bg_render_bombing;

// Must be kept in sync with [bg_render_not_bombing] outside a bomb animation.
extern nearfunc_t_near bg_render_bombing_func;

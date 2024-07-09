#include "platform.h"

// First HP point in the respective color section. Assumes
// [hud_hp_first_redwhite] < [hud_hp_first_white].
// Also, these should be even, due to a landmine in hud_hp_decrement()...
extern unsigned int hud_hp_first_white;
extern unsigned int hud_hp_first_redwhite;

// Actually does three different things, indicated by [func]. Use the concrete
// inlined macros below instead.
bool16 hud_hp_render(int hp_total, int func);

#define HUD_HP_FUNC_DECREMENT 999
#define HUD_HP_FUNC_RERENDER -1

// Unblits the displayed hit point at ([hp_total_new] + 1). Only really works
// for decrementing the HP by 1 or 2 compared to the previous value displayed
// by the bar, which explains the name. Always returns false.
#define hud_hp_decrement(hp_total_new) \
	hud_hp_render(hp_total_new, HUD_HP_FUNC_DECREMENT)

// Reinitializes the background used for unblitting individual hit points from
// VRAM, then re-renders the HP bar with the given number of hit points. Used
// if the background changed after hud_hp_increment(), e.g. in the Sariel
// fight. Always returns false.
#define hud_hp_rerender(hp_total) \
	hud_hp_render(hp_total, HUD_HP_FUNC_RERENDER)

// Initializes the background used for unblitting the hit point at [hp_cur]
// (0-based), then renders this one point. Returns true if this was the last
// hit point (([hp_total] - 1) <= hp_cur), false otherwise.
//
// ZUN bug: Will lead to heap corruption if ([hp_cur] > (HP_MAX / 2)].
#define hud_hp_increment(hp_total, hp_cur) \
	hud_hp_render(hp_total, hp_cur)

// Renders the HP bar increment animation until [done].
#define hud_hp_increment_render(done, hp_total, frame) { \
	if(!done) { \
		done = hud_hp_increment(hp_total, frame); \
	} \
}

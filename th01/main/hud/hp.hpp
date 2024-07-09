#include "platform.h"

// First HP point in the respective color section. Assumes
// [hud_hp_first_redwhite] < [hud_hp_first_white].
extern unsigned int hud_hp_first_white;
extern unsigned int hud_hp_first_redwhite;

// Unblits the displayed hit point at ([hp_total_new] + 1). Only really works
// for decrementing the HP by 1 or 2 compared to the previous value displayed
// by the bar, which explains the name.
void hud_hp_decrement(int hp_total_new);

// Reinitializes the background used for unblitting individual hit points from
// VRAM, then re-renders the HP bar with the given number of hit points. Used
// if the background changed after hud_hp_increment(), e.g. in the Sariel
// fight.
void hud_hp_rerender(int hp_total);

// Renders the HP bar increment animation until [done], initializing the
// backgrounds used for unblitting the individual points along the way.
void hud_hp_increment_render(bool& done, int hp_total, int hp_cur);

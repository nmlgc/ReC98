#include "th02/main/hud/hud.h"

// Low-level
// ---------
// Renders the "Enemy!!" caption and the HP bar, showing the given [bar_value]
// between 0 and BAR_MAX.
void pascal hud_hp_put(int bar_value);
// ---------

// High-level
// ----------
// Renders the HP bar at the fraction of ([hp_cur] / [hp_max]), or instead
// takes asingle fill step if the previous bar value was lower.
void pascal hud_hp_update_and_render(int hp_cur, int hp_max);
// ----------

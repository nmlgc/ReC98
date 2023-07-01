#include "th02/main/hud/hud.hpp"

#define BAR_MAX 128

// Low-level
// ---------

// Renders the "Enemy!!" caption and the HP bar, showing the given [bar_value]
// between 0 and BAR_MAX.
void pascal hud_hp_put(int bar_value);

#if (GAME == 5)
	// Prints [points] using the bold gaiji font, right-aligned at
	// 	([left+8], [y]),
	// in white, using up to 7 digits (8 if the "continue" digit is included).
	// Larger numbers will overflow the most significant digit into the A-Z
	// range.
	void pascal hud_points_put(
		utram_x_t left, utram_y_t y, unsigned long points
	);
#endif
// ---------

// High-level
// ----------

// Renders the HP bar at the fraction of ([hp_cur] / [hp_max]), or instead
// fills up the bar by a single fill step if its previous value was lower.
void pascal near hud_hp_update_and_render(int hp_cur, int hp_max);

static const int HUD_HP_FILL_FRAMES = BAR_MAX;

// Displays [stage_graze] in the graze row.
void hud_graze_put();
// ----------

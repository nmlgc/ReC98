/// Relatively static HUD elements
/// ------------------------------

#include "th03/common.h"

// Fills the playfield area on the text RAM with transparent spaces, and the
// surrounding area with black.
void hud_wipe(void);

void pascal hud_static_halfhearts_put(pid_t pid);
void pascal hud_static_bombs_put(pid_t pid);
void pascal near hud_static_rounds_won_put(pid_t pid);

// No parameter because it only applies to P1.
void near hud_static_story_lives_put(void);

// Renders the gauge and boss attack levels.
void pascal hud_static_gauge_levels_put(pid2 pid);

// Renders all of the above for both players. (Except, of course, the Story
// Mode lives because they only apply to P1.)
void hud_static_put(void);

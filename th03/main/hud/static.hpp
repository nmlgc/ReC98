/// Relatively static HUD elements
/// ------------------------------

#include "th03/common.h"

// Fills the playfield area on the text RAM with transparent spaces, and the
// surrounding area with black.
void hud_wipe(void);

void pascal hud_static_halfhearts_put(pid_t pid);
void pascal hud_static_bombs_put(pid_t pid);

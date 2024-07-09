/// TH04-specific stage functions
/// -----------------------------

#include "th01/math/subpixel.hpp"

// Stage 4
// -------

// Renders the Mugenkan corridor carpet lighting effect for the first 30
// seconds of Stage 4.
void pascal near stage4_render(void);
// -------

// Stage 5
// -------

#define STAGE5_STAR_COUNT 3

// In playfield space.
extern Subpixel stage5_star_center_y[STAGE5_STAR_COUNT];

void pascal near stage5_render(void);
void pascal near stage5_invalidate(void);
// -------

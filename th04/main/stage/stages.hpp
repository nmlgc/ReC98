/// TH04-specific stage functions
/// -----------------------------

// Stage 5
// -------

#define STAGE5_STAR_COUNT 3

// In playfield space.
extern Subpixel stage5_star_center_y[STAGE5_STAR_COUNT];

void pascal near stage5_render(void);
void pascal near stage5_invalidate(void);
// -------

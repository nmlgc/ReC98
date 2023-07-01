// Significant, internal digits. An additional 0 is appended to the on-screen
// representation.
static const int POINTNUM_DIGITS = 4;

// ZUN landmine: [points] is not limited to POINTNUM_DIGITS. Larger values will
// be truncated to their least significant POINTNUM_DIGITS, with their first
// digit being rendered as a glitched sprite.
void pascal near pointnums_add(
	screen_x_t left, screen_y_t top, uint16_t points
);

// These are called from the respective item functions.
void near pointnums_init_for_rank_and_reset(void);
void near pointnums_invalidate(void);
void near pointnums_update_and_render(void);

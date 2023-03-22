void near pointnums_init_for_rank_and_reset(void);

// Blits the given point[num] sprite to the given position. Assumptions:
// • ES is already be set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
void pascal near pointnum_put(
	screen_x_t left, vram_y_t top, unsigned int num
);

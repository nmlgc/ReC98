// Displays a pellet delay cloud [cel] in the given [col] at
// (⌊left/8⌋*8, top).
void pellet_cloud_put_8(screen_x_t left, vram_y_t top, vc2 col, int cel);

// Restores the pixels of the given pellet delay cloud [cel], starting at
// (⌊left/8⌋*8, top), from VRAM page 1, effectively removing a cloud that was
// previously blitted to that position.
void pellet_cloud_unput_8(screen_x_t left, vram_y_t top, int cel);

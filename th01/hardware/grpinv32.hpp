// Inverts the 32×32 square at (⌊left/8⌋*8, top) on the given VRAM [plane].
// Returns true if the square is not fully within the boundaries of VRAM and
// was not inverted, false otherwise.
bool16 graph_invert_32x32_8(screen_x_t left, vram_y_t top, dots8_t far *plane);

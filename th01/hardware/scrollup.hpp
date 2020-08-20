// Waits until VSync, then sets the GDC's hardware scroll registers so that
// the given line will appear at the top of the screen for all subsequent
// frames.
void z_vsync_wait_and_scrollup(vram_y_t line_on_top);

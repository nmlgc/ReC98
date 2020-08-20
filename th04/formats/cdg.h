// ORs a single plane of the CDG image in the given [slot] into the given
// VRAM destination plane at (⌊left/8⌋*8, top), wrapped vertically.
void pascal cdg_put_plane_roll(
	screen_x_t left,
	vram_y_t top,
	int slot,
	vram_plane_t plane_src,
	void __seg *plane_dst
);

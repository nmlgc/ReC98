// ORs a single plane of the CDG image in the given [slot] into the given
// VRAM destination plane at (⌊x/8⌋*8, y), wrapped vertically.
void pascal cdg_put_plane_roll(
	int x, int y, int slot, vram_plane_t plane_src, void __seg *plane_dst
);

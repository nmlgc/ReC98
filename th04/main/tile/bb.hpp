// The monochrome animations loaded from the ST*.BB and BB*.BB files, shown as
// one colored 16×16 tile per bit. Used for the flashy transitions from regular
// stage backgrounds to the bomb and boss backgrounds.

#define TILES_BB_CELS 8

extern unsigned char tiles_bb_col;

extern bb_tiles8_t __seg *tiles_bb_seg;

// Fills the playfield tile starting at (⌊left/8⌋*8, top) with the current
// GRCG tile. Assumes that the GRCG is set to TDW mode.
void __fastcall near grcg_tile_bb_put_8(screen_x_t left, vram_y_t top);

// Renders the given animation [cel] in [tiles_bb_seg] to the playfield area
// in VRAM. All tiles with a corresponding 1 bit are filled with the
// [tiles_bb_col].
inline void tiles_bb_put(bb_tiles8_t __seg *&seg, unsigned char &cel) {
	void pascal near tiles_bb_put_raw(int cel);

	tiles_bb_seg = seg;
	tiles_bb_put_raw(cel);
}

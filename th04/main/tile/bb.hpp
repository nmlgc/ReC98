// Fills the playfield tile starting at (⌊left/8⌋*8, top) with the current
// GRCG tile. Assumes that the GRCG is set to TDW mode.
void fastcall near grcg_tile_bb_put_8(screen_x_t left, vram_y_t top);

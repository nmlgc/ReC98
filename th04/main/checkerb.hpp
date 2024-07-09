/// Rendering a two-color checkerboard inside the playfield
/// -------------------------------------------------------

// Renders the checkerboard at its current internal position with GRCG colors
// 0 (dark squares) and 1 (bright squares), then scrolls it up for the next
// frame. Assumes that the GRCG is active and set to TDW mode.
void near playfield_checkerboard_grcg_tdw_update_and_render(void);

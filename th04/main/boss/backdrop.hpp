// Flood-fills the area around a certain backdrop image. Called with the GRCG
// in TDW mode and the tile register set to the intended color.
extern nearfunc_t_near boss_backdrop_colorfill;

// Renders the boss battle background image at the given screen position,
// surrounded by the given background [col].
void pascal near boss_backdrop_render(
	screen_x_t left, vram_y_t top, uint4_t col
);

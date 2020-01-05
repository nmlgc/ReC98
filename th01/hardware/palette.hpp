extern Palette4 z_Palettes;

// Sets the given hardware [col] to the given RGB value.
void z_palette_show_single(uint4_t col, uint4_t r, uint4_t g, uint4_t b);

// Clamps #[r][g][b] to the 4-bit 0-15 range, then sets the given [col] in
// both z_Palettes and the hardware palette to that value.
void z_palette_set_show(uint4_t col, int r, int g, int b);

// Sets all hardware colors to #000, without touching z_Palettes.
void z_palette_black(void);

// Sets all hardware colors to #FFF, without touching z_Palettes.
void z_palette_white(void);

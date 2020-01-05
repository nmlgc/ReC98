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

/// Resident palette
/// ----------------
// Copies the resident palette to z_Palettes and sets all hardware colors.
// Returns 1 on success, 0 on failure.
int z_respal_get_show(void);
// Copies z_Palettes to the resident palette. Returns 1 on success, 0 on
// failure.
int z_respal_set(void);
/// ----------------

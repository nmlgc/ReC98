/// Current palette
/// ---------------
extern Palette4 z_Palettes;

// Sets the given hardware [col] to the given RGB value.
#define UINT4 int
void z_palette_show_single(uint4_t col, UINT4 r, UINT4 g, UINT4 b);
#define z_palette_show_single_col(col, rgb) \
	z_palette_show_single(col, rgb.c.r, rgb.c.g, rgb.c.b);
#undef UINT4

// Clamps #[r][g][b] to the 4-bit 0-15 range, then sets the given [col] in
// both z_Palettes and the hardware palette to that value.
void z_palette_set_show(uint4_t col, int r, int g, int b);

// Sets all hardware colors to #000, without touching z_Palettes.
void z_palette_black(void);

// Sets all hardware colors to #FFF, without touching z_Palettes.
void z_palette_white(void);

// Fades all hardware colors from #000 or #FFF to their value in z_Palettes.
void z_palette_black_in(void);
void z_palette_white_in(void);

// Fades all hardware colors from their value in z_Palettes to #000 or #FFF,
// without modifiying z_Palettes;
void z_palette_black_out(void);
void z_palette_white_out(void);

// Fades each hardware palette color from the given RGB value to its
// respective value in z_Palettes, blocking [step_ms] milliseconds at each of
// the 16 fade steps. If [keep] is nonzero for a specific color number, that
// color is excluded from the fade calculation and will stay at its z_Palettes
// value throughout the function.
void z_palette_fade_from(
	uint4_t from_r, uint4_t from_g, uint4_t from_b,
	int keep[COLOR_COUNT],
	unsigned int step_ms
);
/// ---------------

/// Resident palette
/// ----------------
// Copies the resident palette to z_Palettes and sets all hardware colors.
// Returns 1 on success, 0 on failure.
int z_respal_get_show(void);
// Copies z_Palettes to the resident palette. Returns 1 on success, 0 on
// failure.
int z_respal_set(void);
/// ----------------

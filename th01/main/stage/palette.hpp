// The intended palette for a stage, with no effects applied. Used as the
// reference palette for undoing the palette changes during the bomb animation
// and the Pause menu.
extern Palette4 stage_palette;

// Sets [stage_palette] to [pal].
void stage_palette_set(const Palette4 &pal);

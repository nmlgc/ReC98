// 16-color VRAM palette
// ---------------------

// Sets the given hardware [col] to the given RGB value.
void palette_show_single(vc_t col, const RGB4& c);

// Calls palette_show_single() for all colors in [pal].
void palette_show(const Palette4& pal);

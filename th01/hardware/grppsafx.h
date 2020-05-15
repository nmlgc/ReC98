// Puts the given [str] onto the graphics RAM at the given position, applying
// the given effect.
#define FX(color, weight, spacing) \
	((color) | (weight & 3) << 4 | (spacing & 7) << 6)
void graph_putsa_fx(int left, int top, int fx, const unsigned char *str);

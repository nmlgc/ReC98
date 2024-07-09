// Animated transitions between VRAM pages 0 and 1
// -----------------------------------------------

#include "pc98.h"

// Transitions VRAM page 0 to the contents of VRAM page 1, using 8×8 squares
// that diagonally move from the top-left and bottom-right corners of VRAM,
// which combine the pixels of both pages. Spends [step_ms] milliseconds on
// each animation frame.
void pagetrans_diagonal_8x8(unsigned int step_ms);
void pagetrans_diagonal_8x8_with_palette(
	unsigned int step_ms, Palette4 &pal_cur, const Palette4 &pal_target
);
// -----------------------------------------------

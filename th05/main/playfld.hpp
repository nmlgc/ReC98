#include "th04/main/playfld.hpp"

// Fills the entire playfield with hardware palette color #0.
void near playfield_fill_col_0(void);

// These fill the VRAM playfield area around the given [left]_[top]_[w]_[h]
// coordinates with the given hardware palette color.
void near playfield_fillm_0_0_384_240_col_0(void);

// Like above, but using the current GRCG tile rather than a set color. The
// GRCG is assumed to be set to TDW mode.
void pascal near playfield_fillm_32_0_320_192(void);
void pascal near playfield_fillm_0_0_384_192__2(void);
void pascal near playfield_fillm_0_205_384_163(void);
void pascal near playfield_fillm_64_56_256_256(void);
void pascal near playfield_fillm_0_0_384_192__1(void);
void pascal near playfield_fillm_0_104_384_192(void);

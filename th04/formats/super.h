/// Micro-optimized, vertically-wrapped sprite display functions
/// ------------------------------------------------------------
// All of these assume that the caller
// • has set ES to the beginning of a VRAM plane (e.g. 0xA800)
// • and has set the GRCG to RMW mode. Consequently, the GRCG also isn't
//   turned off before returning from any of these functions.

// Displays the tiny-format 16×16 sprite with the given [patnum], wrapped
// vertically. (Identical to master.lib's super_roll_put_tiny().)
#define z_super_roll_put_tiny_16x16(left, top, patnum) \
	_DX = top; \
	_AX = left; \
	z_super_roll_put_tiny_16x16_raw(patnum);
void pascal near z_super_roll_put_tiny_16x16_raw(int patnum);

// Like z_super_roll_put_tiny_16x16(), but adapted for 32×32 sprites.
#define z_super_roll_put_tiny_32x32(left, top, patnum) \
	_DX = top; \
	_AX = left; \
	z_super_roll_put_tiny_32x32_raw(patnum);
void pascal near z_super_roll_put_tiny_32x32_raw(int patnum);
/// ------------------------------------------------------------

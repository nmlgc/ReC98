#include "pc98.h"

#define BB_SIZE 2048

// Bitmap format, storing 1-bit values for 8 tiles in one byte.
typedef uint8_t bb_tiles8_t;

// Blocky boss entrance animations
// -------------------------------

extern bb_tiles8_t __seg *bb_boss_seg;

// Loads the .BB file with the given name into memory, and sets [bb_boss_seg]
// to the newly allocated segment. Does not attempt to free [bb_boss_seg], and
// will leak memory if it is not a nullptr.
void pascal near bb_boss_load(const char far *fn);

// Frees any previously allocated [bb_boss_seg].
#if (GAME == 5)
	void near bb_boss_free(void);
#else
	void far bb_boss_free(void);
#endif
// -------------------------------

/// Text dissolve circles
/// ---------------------

#define BB_TXT_W 32
#define BB_TXT_H 32
#define BB_TXT_VRAM_W (BB_TXT_W / BYTE_DOTS)

#define BB_TXT_IN_SPRITE 16
#define BB_TXT_IN_CELS 8
#define BB_TXT_OUT_SPRITE 0
#define BB_TXT_OUT_CELS 16

// Puts the given TXT*.BB sprite at (⌊left/8⌋*8, top). Assumptions:
// • ES is already set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
#define bb_txt_put_8(left, top, sprite) \
	_CX = sprite; \
	bb_txt_put_8_raw(left, top);
void __fastcall near bb_txt_put_8_raw(uscreen_x_t left, uvram_y_t top);
/// ---------------------

#define BB_SIZE 2048

typedef char __seg* bb_seg_t;

void pascal near bb_stage_load(const char far* fn);

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
// • ES is already be set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
#define bb_txt_put_8(left, top, sprite) \
	_CX = sprite; \
	bb_txt_put_8_raw(left, top);
void __fastcall near bb_txt_put_8_raw(unsigned int left, unsigned int top);
/// ---------------------

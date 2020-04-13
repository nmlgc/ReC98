// Blits the given point[num] sprite to the given position. Assumptions:
// • ES is already be set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
// Returns _DX (= left) advanced by the width of the numeral.
#define pointnum_put(left, top, numeral) \
	_CX = numeral; \
	pointnum_put_raw(patnum);
void __fastcall near pointnum_put_raw(int top, int left);

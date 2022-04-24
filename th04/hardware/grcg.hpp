// Redefined versions of master.lib's grcg_setmode() and grcg_setcolor().
void near grcg_setmode_rmw_seg1(void);
void near grcg_setmode_tdw(void);

// In contrast to master.lib's own grcg_setcolor(), these keep the current
// GRCG mode, and reenable interrupts before returning.
#define grcg_setcolor_direct_seg1(col) \
	_AH = col; \
	grcg_setcolor_direct_seg1_raw();
void near grcg_setcolor_direct_seg1_raw(void);
void near grcg_setcolor_direct_seg3_raw(void);

// Implementation macros
// ---------------------

#define grcg_setmode_rmw_inlined() { \
	outportb2(0x7C, 0xC0); \
}

// Builds the contents of a GRCG tile register from the x86 carry flag by
// extending its value to a full byte (CF=0 → 0x00, CF=1 → 0xFF).
//
// (Technically returns a dots8_t, but why add a planar.h dependency just for
// one type.)
inline uint8_t tile_register_from_carry(uint8_t unused)  {
	__emit__(0x1A, 0xC0); // SBB AL, AL
	return _AL;
}

// And this is why [col] is stored in AH: x86 simply only supports AL as the
// source operand for OUT. By shifting each successive bit of [col] into the
// carry flag and using the function above, we get the minimum of three
// instructions (SHR, SBB, OUT) per bitplane, with no register spills. Quite a
// beautiful optimization!
#define grcg_setcolor_direct_inlined(col) { \
	disable(); \
	_DX = 0x7E; \
	/* Just in case people want to call this with an immediate color value… */ \
	_AH = col; \
	outportb(_DX, tile_register_from_carry(_AH >>= 1)); \
	outportb(_DX, tile_register_from_carry(_AH >>= 1)); \
	outportb(_DX, tile_register_from_carry(_AH >>= 1)); \
	outportb(_DX, tile_register_from_carry(_AH >>= 1)); \
	enable(); \
}
// ---------------------

// Redefined versions of master.lib's grcg_setmode() and grcg_setcolor().
void near grcg_setmode_rmw(void);
void near grcg_setmode_tdw(void);

// In contrast to master.lib's own grcg_setcolor(), these keep the current
// GRCG mode, and reenable interrupts before returning.
#define grcg_setcolor_direct(col) \
	_AH = col; \
	grcg_setcolor_direct_raw();
void near grcg_setcolor_direct_raw(void);
void near grcg_setcolor_direct_seg3_raw(void);

// Implementation macros
// ---------------------

inline void grcg_setmode_rmw_inlined(void) {
	_outportb_(0x7C, 0xC0);
}

// And this is why [col] is stored in AH: x86 simply only supports AL as the
// source operand for OUT.
#define grcg_setcolor_direct_inlined(col) { \
	disable(); \
	_DX = 0x7E; \
	/* Just in case people want to call this with an immediate color value… */ \
	_AH = col; \
	\
	/* Same algorithm as in platform/x86real/pc98/grcg.cpp. */ \
	outportb(_DX, tile_register_from_carry(_AH >>= 1)); \
	outportb(_DX, tile_register_from_carry(_AH >>= 1)); \
	outportb(_DX, tile_register_from_carry(_AH >>= 1)); \
	outportb(_DX, tile_register_from_carry(_AH >>= 1)); \
	enable(); \
}

// Perfectly inlines if [col] is a compile-time constant.
inline void grcg_setcolor_direct_constant(uint4_t col) {
	disable();
	_DX = 0x7E;

	// Same algorithm as in platform/x86real/pc98/grcg.cpp. Only replaces
	// `MOV AL, 0` with `XOR AL, AL` by making both the XOR and the reuse
	// explicit.
	outportb(_DX, ((col & 0x1) ? 0xFF : (_AL ^= _AL)));
	outportb(_DX, ((col & 0x2) ? 0xFF : ((col & 0x1) ? (_AL ^= _AL) : _AL)));
	outportb(_DX, ((col & 0x4) ? 0xFF : ((col & 0x2) ? (_AL ^= _AL) : _AL)));
	outportb(_DX, ((col & 0x8) ? 0xFF : ((col & 0x4) ? (_AL ^= _AL) : _AL)));
	enable();
}
// ---------------------

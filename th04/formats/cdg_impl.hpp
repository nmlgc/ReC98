// Shared parts of the cdg_put_*() functions.

#include "platform/x86real/flags.hpp"
#include "decomp.hpp"

inline CDG near* cdg_slot_offset(const int &slot) {
	_SI = slot;
	_SI <<= 4;	// MODDERS: Should be sizeof(CDG);
	_SI += FP_OFF(cdg_slots);
	return reinterpret_cast<CDG near *>(_SI);
}

// Returns (vram_offset_shift(left, 0) + cdg->offset_at_bottom_left).
// [top] is calculated into the segment later, by cdg_dst_segment().
// (Since ROW_SIZE is a multiple of 16, this always works.)
#define cdg_dst_offset(ret, cdg, left) \
	/* Sneaky! That's how we can pretend this is an actual function that */ \
	/* returns a value. */ \
	ret; \
	ret = left; \
	ret >>= 3; \
	ret += cdg->offset_at_bottom_left;

// Returns (SEG_PLANE_B + (top * (ROW_SIZE / 16))).
#define cdg_dst_segment(ret, top, tmp) \
	ret; /* Sneaky again */ \
	_AX = top; \
	tmp = _AX; \
	ret = (((_AX * 4) + tmp) + SEG_PLANE_B);

#define cdg_put_plane_raw(dst_seg, dst_off, src_seg, src_off, dword_w) \
	/* _ES = dst_seg; // wouldn't be optimized away */ \
	/* _DS = src_seg; // wouldn't be optimized away */ \
	_DI = dst_off; \
	_SI = src_off; \
	do { \
		_CX = dword_w; \
		REP MOVSD; \
		_DI -= stride; \
	} while(!FLAGS_SIGN);

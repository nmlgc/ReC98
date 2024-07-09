#include "platform.h"
#include "x86real.h"
#include "planar.h"
#include "platform/x86real/pc98/egc.hpp"
#include "platform/x86real/pc98/grcg.hpp"
#include "platform/x86real/pc98/page.hpp"

enum egc_register_t {
	EGC_ACTIVEPLANEREG = 0x04A0,
	EGC_READPLANEREG   = 0x04A2,
	EGC_MODE_ROP_REG   = 0x04A4,
	EGC_FGCOLORREG     = 0x04A6,
	EGC_MASKREG        = 0x04A8,
	EGC_BGCOLORREG     = 0x04AA,
	EGC_ADDRRESSREG    = 0x04AC,
	EGC_BITLENGTHREG   = 0x04AE,
};

EGCCopy::EGCCopy()
{
	// The EGC does in fact require an active GRCG.
	// (See PC-9801 Programmers' Bible, p. 456)
	_outportb_(0x7C, GC_TDW);

	graph_egc_on();
	outport(EGC_ACTIVEPLANEREG, 0xFFF0);
	outport(EGC_READPLANEREG, 0x00FF);
	outport(EGC_MASKREG, 0xFFFF);
	outport(EGC_ADDRRESSREG, 0);
	outport(EGC_MODE_ROP_REG, 0x29F0);
}

EGCCopy::~EGCCopy()
{
	graph_egc_off();
	_outportb_(0x7C, GC_OFF);
}

// Rectangle blitting
// ------------------
// The EGC automatically reinitializes its internal shifter after copying the
// number of dots indicated in the bit length register. This makes it ideal to
// be used in rectangular loops, as nothing needs to be reinitialized for
// successive row loops.

inline uvram_offset_t vram_offset_even(
	const uvram_word_amount_t& x, const uvram_y_t& y
) {
	return (vram_offset_shift(0, y) + (x * EGC_REGISTER_SIZE));
}

inline vram_byte_amount_t copy_width(
	const pixel_t& w, const upixel_t& dst_first
) {
	return ((
		(dst_first + w + EGC_REGISTER_MASK) / EGC_REGISTER_DOTS
	) * EGC_REGISTER_SIZE);
}

void EGCCopy::rect(
	screen_x_t src_left,
	vram_y_t src_top,
	screen_x_t dst_left,
	vram_y_t dst_top,
	pixel_t w,
	pixel_t h
)
{
	if(w <= 0) {
		return;
	}
	_SI = (vram_offset_shift(src_left, src_top) & ~1);
	_DI = (vram_offset_shift(dst_left, dst_top) & ~1);
	const upixel_t src_first = (src_left & EGC_REGISTER_MASK);
	const upixel_t dst_first = (dst_left & EGC_REGISTER_MASK);
	const register vram_byte_amount_t vram_w = copy_width(w, dst_first);
	outport(EGC_ADDRRESSREG, (src_first | (dst_first << 4)));
	outport(EGC_BITLENGTHREG, (w - 1));
	_ES = SEG_PLANE_B;
	if(src_first > dst_first) {
		for(pixel_t y = 0; y < h; y++) {
			// Need to read one additional word to prefill the tile register.
			_AX = *reinterpret_cast<egc_temp_t __es *>(_SI);
			_SI += EGC_REGISTER_SIZE;

			for(_BX = 0; _BX < vram_w; _BX += EGC_REGISTER_SIZE) {
				_AX = *reinterpret_cast<egc_temp_t __es *>(_SI + _BX);
				*reinterpret_cast<egc_temp_t __es *>(_DI + _BX) = _AX;
			}
			_SI += (ROW_SIZE - EGC_REGISTER_SIZE);
			_DI += ROW_SIZE;
		}
	} else {
		for(pixel_t y = 0; y < h; y++) {
			for(_BX = 0; _BX < vram_w; _BX += EGC_REGISTER_SIZE) {
				_AX = *reinterpret_cast<egc_temp_t __es *>(_SI + _BX);
				*reinterpret_cast<egc_temp_t __es *>(_DI + _BX) = _AX;
			}
			_SI += ROW_SIZE;
			_DI += ROW_SIZE;
		}
	}
}

void EGCCopy::rect_interpage(
	screen_x_t src_left,
	vram_y_t src_top,
	screen_x_t dst_left,
	vram_y_t dst_top,
	pixel_t w,
	pixel_t h,
	page_t src_page
)
{
	if(w <= 0) {
		return;
	}
	_SI = (vram_offset_shift(src_left, src_top) & ~1);
	_DI = (vram_offset_shift(dst_left, dst_top) & ~1);
	const upixel_t src_first = (src_left & EGC_REGISTER_MASK);
	const upixel_t dst_first = (dst_left & EGC_REGISTER_MASK);
	const register vram_byte_amount_t vram_w = copy_width(w, dst_first);
	const bool dst_page = (src_page ^ 1);
	outport(EGC_BITLENGTHREG, (w - 1));
	outport(EGC_ADDRRESSREG, (src_first | (dst_first << 4)));
	_ES = SEG_PLANE_B;
	if(src_first > dst_first) {
		for(pixel_t y = 0; y < h; y++) {
			// Need to read one additional word to prefill the tile register.
			page_access(src_page);
			_AX = *reinterpret_cast<egc_temp_t __es *>(_SI);
			_SI += EGC_REGISTER_SIZE;

			for(_BX = 0; _BX < vram_w; _BX += EGC_REGISTER_SIZE) {
				page_access(src_page);
				_AX = *reinterpret_cast<egc_temp_t __es *>(_SI + _BX);
				page_access(dst_page);
				*reinterpret_cast<egc_temp_t __es *>(_DI + _BX) = _AX;
			}
			_SI += (ROW_SIZE - EGC_REGISTER_SIZE);
			_DI += ROW_SIZE;
		}
	} else {
		for(pixel_t y = 0; y < h; y++) {
			for(_BX = 0; _BX < vram_w; _BX += EGC_REGISTER_SIZE) {
				page_access(src_page);
				_AX = *reinterpret_cast<egc_temp_t __es *>(_SI + _BX);
				page_access(dst_page);
				*reinterpret_cast<egc_temp_t __es *>(_DI + _BX) = _AX;
			}
			_SI += ROW_SIZE;
			_DI += ROW_SIZE;
		}
	}
}

void EGCCopy::rect_interpage(
	screen_x_t left, vram_y_t top, pixel_t w, pixel_t h, page_t src_page
)
{
	if(w <= 0) {
		return;
	}
	uvram_offset_t vo = (vram_offset_shift(left, top) & ~1);
	const upixel_t first = (left & EGC_REGISTER_MASK);
	const register vram_byte_amount_t vram_w = copy_width(w, first);
	const bool dst_page = (src_page ^ 1);
	outport(EGC_ADDRRESSREG, (first | (first << 4)));
	outport(EGC_BITLENGTHREG, (w - 1));
	_ES = SEG_PLANE_B;
	for(pixel_t y = 0; y < h; y++) {
		for(_BX = 0; _BX < vram_w; _BX += EGC_REGISTER_SIZE) {
			page_access(src_page);
			_AX = *reinterpret_cast<egc_temp_t __es *>(vo + _BX);
			page_access(dst_page);
			*reinterpret_cast<egc_temp_t __es *>(vo + _BX) = _AX;
		}
		vo += ROW_SIZE;
	}
}
// ------------------

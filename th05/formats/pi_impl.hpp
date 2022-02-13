// Shared parts of the pi_put_*() functions.

#include "decomp.hpp"

inline void imul_di(int8_t factor) {
	__emit__(0x6B, 0xFF, factor);
}

#define pi_put_impl(left, top, slot, rowloop_func) \
	_SI = slot; \
	_DI = _SI; \
	_SI <<= 2;	/* *= sizeof(void far *) */  \
	_asm { les	si, pi_buffers[si]; } \
	imul_di(sizeof(PiHeader)); \
	rowloop_func

#define buffer_offset_off	_AX
#define buffer_offset_sgm	_DX
#define quarter_local    	_CL

#define pi_put_quarter_impl(left, top, slot, quarter, rowloop_func) \
	buffer_offset_off = 0; \
	buffer_offset_sgm = 0; \
	_SI = slot; \
	\
	quarter_local = quarter; \
	if(quarter_local & 1) { \
		buffer_offset_off = (PI_QUARTER_W / 2); \
	} \
	if(quarter_local & 2) { \
		/* Careful! Parenthesizing this naively leads to overflows, since */ \
		/* (PI_QUARTER * PI_W) doesn't fit into 16 bits. */\
		buffer_offset_sgm = ((PI_QUARTER_H / 2) * (PI_W / 16)); \
	} \
	_SI <<= 2;	/* *= sizeof(void far *) */ \
	_asm { les	si, pi_buffers[si]; } \
	_SI += buffer_offset_off; \
	_ES += buffer_offset_sgm; \
	rowloop_func

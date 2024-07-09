// Shared parts of the pi_put_*() functions.

#include "codegen.hpp"
#include "decomp.hpp"

#define pi_put_impl(slot, rowloop_func) \
	_SI = slot; \
	_DI = _SI; \
	_SI <<= 2;	/* *= sizeof(void far *) */  \
	asm { les	si, pi_buffers[si]; } \
	imul_reg_to_reg(_DI, _DI, sizeof(PiHeader)); \
	rowloop_func

#define buffer_offset_off	_AX
#define buffer_offset_seg	_DX
#define quarter_local    	_CL

#define pi_put_quarter_impl(slot, quarter, rowloop_func) \
	buffer_offset_off = 0; \
	buffer_offset_seg = 0; \
	_SI = slot; \
	\
	quarter_local = quarter; \
	if(quarter_local & 1) { \
		buffer_offset_off = (PI_QUARTER_W / 2); \
	} \
	if(quarter_local & 2) { \
		/* Careful! Parenthesizing this naively leads to overflows, since */ \
		/* (PI_QUARTER * PI_W) doesn't fit into 16 bits. */\
		buffer_offset_seg = ((PI_QUARTER_H / 2) * (PI_W / 16)); \
	} \
	_SI <<= 2;	/* *= sizeof(void far *) */ \
	asm { les	si, pi_buffers[si]; } \
	_SI += buffer_offset_off; \
	_ES += buffer_offset_seg; \
	rowloop_func

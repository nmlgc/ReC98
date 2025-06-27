// Shared parts of the pi_put_*() functions.

#include "codegen.hpp"
#include "decomp.hpp"

#define pi_put_impl(slot, rowloop_func) \
	_SI = slot; \
	_DI = _SI; \
	_SI <<= 2;	/* *= sizeof(void far *) */ \
	asm { les	si, pi_buffers[si]; } \
	imul_reg_to_reg(_DI, _DI, sizeof(PiHeader)); \
	rowloop_func

#include "decomp.hpp"

// Requires the EGC to have been activated before.
#define egc_setup_copy() { \
	outport2(EGC_ACTIVEPLANEREG, 0xFFF0); \
	outport2(EGC_READPLANEREG, 0x00FF); \
	/* EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD */ \
	outport2(EGC_MODE_ROP_REG, 0x3100); \
	outport2(EGC_MASKREG, 0xFFFF); \
	outport2(EGC_ADDRRESSREG, 0); \
	outport2(EGC_BITLENGTHREG, 0xF); \
}

// Requires the EGC to have been activated and set up for a copy before.
// ZUN bloat: Can be merged into egc_setup_copy().
#define egc_setup_copy_masked(mask) { \
	outport2(EGC_READPLANEREG, 0x00ff); \
	/* EGC_COMPAREREAD | EGC_WS_PATREG | EGC_RL_MEMREAD */ \
	outport2(EGC_MODE_ROP_REG, 0x3100); \
	outport2(EGC_BITLENGTHREG, 0xF); \
	outport(EGC_MASKREG, mask); \
}

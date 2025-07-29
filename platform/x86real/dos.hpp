// Internal DOS structures
// -----------------------
// Adapted from the following FreeDOS files:
//
// • `kernel/hdr/mcb.h` (dos_mcb_t)
// • `kernel/hdr/process.h` (dos_psp_t)
//
// The structures are limited up to the fields needed by other code.
// FreeDOS-specific declarations were replaced with reserved bytes.

#include "platform.h"

enum dos_alloc_strategy_t {
	FIRST_FIT = 0,
	BEST_FIT  = 1,
	LAST_FIT  = 2,

	_dos_alloc_strategy_t_FORCE_UINT16 = 0xFFFF
};

enum dos_mcb_type_t {
	MCB_NORMAL = 0x4d,
	MCB_LAST   = 0x5a,
};

// Program Segment Prefix
struct dos_psp_t {
	uint16_t exit;                	// 00 CP/M-like exit point: int 20
	uint16_t size;                	// 02 segment of first byte beyond memory
	/****************************/	// allocated to program
	uint8_t reserved_1;           	// 04 single char fill=0

	// CP/M-like entry point
	// offsets 5-9 are a far call to absolute address 0:00C0h encoded using 1MB
	// wrap form of address (e.g. 0F01D:FEF0h) for compatiblity with CP/M apps
	// that do a near call to psp:5 and expect size (KB) of allocated segment
	// in word at offset 6
	uint8_t farcall;              	// 05 far call opcode
	void (interrupt far* reentry);	// 06 re-entry point

	void (interrupt far* isv22);  	// 0a terminate address
	void (interrupt far* isv23);  	// 0e ctrl-break address
	void (interrupt far* isv24);  	// 12 critical error address
	dos_psp_t __seg* parent;      	// 16 parent psp segment
	uint8_t files[20];            	// 18 file table - 0xff is unused
	char __seg* environ;          	// 2c environment paragraph
};

// Memory Control Block
struct dos_mcb_t {
	uint8_t type;        	// 00 dos_mcb_type_t
	dos_psp_t __seg* psp;	// 01 owner id via psp segment
	uint16_t size;       	// 03 size of segment in paragraphs
	uint8_t fill[3];     	// 05 padding
	uint8_t name[8];     	// 08 owner name limited to 8 bytes
};

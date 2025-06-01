// ReC98 PiLoad fork
// -----------------

#define PILOADM

#include "libs/piloadc/piloadc.hpp"

// [read_func] returns the number of bytes actually read.

// Small / Tiny model
extern "C" int __cdecl near PiBlit(
	void __ds *buff,
	uint16_t Size,
	int X,
	int Y,
	int option,
	int (pascal near *read_func)(void far *buf, unsigned size)
);

// Large / Huge model
extern "C" int __cdecl far PiBlitL(
	void far *buff,
	uint16_t Size,
	int X,
	int Y,
	int option,
	int (pascal far *read_func)(void far *buf, unsigned size)
);

// Compact model
extern "C" int __cdecl near PiBlitC(
	void far *buff,
	uint16_t Size,
	int X,
	int Y,
	int option,
	int (pascal near *read_func)(void far *buf, unsigned size)
);

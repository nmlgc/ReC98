// ReC98 PiLoad fork
// -----------------

#define PILOADM

#include "libs/piloadc/piloadc.hpp"

// Small / Tiny model
extern "C" int __cdecl near PiLoad(
	const char __ds *name,
	void __ds *buff,
	uint16_t Size,
	int X,
	int Y,
	int option
);

// Large / Huge model
extern "C" int __cdecl far PiLoadL(
	const char far *name,
	void far *buff,
	uint16_t Size,
	int X,
	int Y,
	int option
);

// Compact model
extern "C" int __cdecl near PiLoadC(
	const char far *name,
	void far *buff,
	uint16_t Size,
	int X,
	int Y,
	int option
);

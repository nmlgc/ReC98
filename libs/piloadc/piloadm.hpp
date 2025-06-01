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

// Initializes PiLoad's internal state and [buff] with the header data from the
// .PI file read through [read_func]. Returns the amount of paragraphs required
// for the image data, or a negative value on error.
extern "C" int __cdecl near PiLoadHeader(
	void __ds *buff,
	uint16_t Size,
	int (pascal near *read_func)(void far *buf, unsigned size),
	uint8_t option
);
extern "C" int __cdecl far PiLoadHeaderL(
	void far *buff,
	uint16_t Size,
	int (pascal far *read_func)(void far *buf, unsigned size),
	uint8_t option
);
extern "C" int __cdecl near PiLoadHeaderC(
	void far *buff,
	uint16_t Size,
	int (pascal near *read_func)(void far *buf, unsigned size),
	uint8_t option
);

// Continues the .PI load process started by PiLoadHeader() by unpacking the
// .PI into a planar format to [plane_B]. Subsequent bitplanes are stored at
// paragraph-aligned positions relative to this segment; to access them, divide
// the size returned by PiLoadHeader() by 4 and add the resulting value to
// [plane_B].
// Always returns 0.
extern "C" int __cdecl near PiLoadPlanes(
	seg_t plane_B, void __ds *buff, uint16_t Size
);
extern "C" int __cdecl far PiLoadPlanesL(
	seg_t plane_B, void far *buff, uint16_t Size
);

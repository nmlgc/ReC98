// Option and error constants, according to PILOADC.DOC.

#include "platform.h"

#define PILOAD_OPT_COLORKEY(col) ((col << 8) | 0x40)

// PiLoad also returns values >0 to indicate DOS file I/O errors.
#define PILOAD_ERR_OK 0
#define PILOAD_ERR_BUFFER_TOO_SMALL -8
#define PILOAD_ERR_NO_PI -31
#define PILOAD_ERR_NOT_SUPPORTED -32

extern "C" int __cdecl near PiLoad(
	const char __ds *name,
	void __ds *buff,
	uint16_t Size,
	int X,
	int Y,
	int tone,
	int option
);
extern "C" int __cdecl far PiLoadL(
	const char far *name,
	void far *buff,
	uint16_t Size,
	int X,
	int Y,
	int tone,
	int option
);
extern "C" int __cdecl near PiLoadC(
	const char far *name,
	void far *buff,
	uint16_t Size,
	int X,
	int Y,
	int tone,
	int option
);

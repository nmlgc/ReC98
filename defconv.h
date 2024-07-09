// Common calling convention macro for some functions that originated in TH02
// as __cdecl, but were then changed to __pascal in TH03.
#ifndef GAME
	#error GAME not defined
#elif GAME >= 3
	#define DEFCONV __pascal
#else
	#define DEFCONV __cdecl
#endif

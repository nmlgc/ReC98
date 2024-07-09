// Remove C++ exception handler bloat on Borland compilers
// (see https://community.embarcadero.com/article/technical-articles/162/14700)
// ----------------------------------------------------------------------------

#pragma option -zC_TEXT

#if defined(__TURBOC__) && defined(__MSDOS__)

#include <malloc.h>
#include <new.h>
#include "platform.h"

extern "C" void __cdecl _ExceptInit(void)
{
}

new_handler _new_handler = nullptr;

new_handler __cdecl set_new_handler(new_handler p)
{
	new_handler t = _new_handler;
	_new_handler = p;
	return t;
}

void* __cdecl operator new(size_t size)
{
	void* p = nullptr;
	if(size == 0) {
		size = 1;
	}
	while(((p = malloc(size)) == nullptr) && (_new_handler != nullptr)) {
		_new_handler();
	}
	return p;
}

void far* __cdecl operator new(uint32_t size)
{
	void far* p = nullptr;
	if(size == 0) {
		size = 1;
	}
	while(((p = farmalloc(size)) == nullptr) && (_new_handler != nullptr)) {
		_new_handler();
	}
	return p;
}

#endif

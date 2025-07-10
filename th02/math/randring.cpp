#include <stddef.h>
#include "th02/math/randring.hpp"

#pragma option -k-

#ifndef RANDRING_INSTANCE
#error Define RANDRING_INSTANCE before including randring.cpp.
#endif

#define randring_func_(instance, name) randring##instance##_##name
#define randring_func(instance, name) randring_func_(instance, name)

inline size_t randring_index(void) {
	_BL = randring_p;
	randring_p++;
	_BH = 0;
	return _BX;
}

uint8_t near randring_func(RANDRING_INSTANCE, next8)(void)
{
	return randring[randring_index()];
}

uint8_t pascal near randring_func(RANDRING_INSTANCE, next8_and)(uint8_t mask)
{
	return randring[randring_index()] & mask;
}

uint16_t near randring_func(RANDRING_INSTANCE, next16)(void)
{
	return (reinterpret_cast<uint16_t &>(randring[randring_index()]));
}

#pragma option -k

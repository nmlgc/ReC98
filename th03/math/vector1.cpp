#pragma option -zCSHARED -3

#include "th03/math/vector.hpp"

extern "C" int vector1_at(int origin, int length, int angle)
{
	return (((static_cast<long>(length) * angle) >> 8) + origin);
}

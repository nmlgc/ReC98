#pragma option -zCSHARED -3

extern "C" {
#include "th03/math/vector.hpp"

int vector1_at(int origin, int length, int angle)
{
	return (((static_cast<long>(length) * angle) >> 8) + origin);
}

}

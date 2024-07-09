#pragma option -zCSHARED

#include "th03/math/polar.hpp"

int polar(int center, int radius, int ratio)
{
	return (((static_cast<long>(radius) * ratio) >> 8) + center);
}

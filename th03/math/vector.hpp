extern "C" {
#include "th02/math/vector.hpp"

#if GAME == 3
// (different calling convention than the TH04/TH05 one)
int __cdecl vector1_at(int origin, int length, int angle);
#endif
}

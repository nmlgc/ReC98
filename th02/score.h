#include "platform.h"

#define SCORE_DIGITS 8

// Later games use a binary-coded decimal representation.
#if (GAME == 2)
// A value that can be as large as the highest possible gameplay score.
// A few places in TH02's code do require this type to be signed.
typedef int32_t score_t;
#endif

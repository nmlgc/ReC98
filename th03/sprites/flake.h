#include "planar.h"

#define FLAKE_W 8
#define FLAKE_H 8
static const unsigned int FLAKE_CELS = 4;

// ZUN left an extra 16 pixels of room to load the rows using a single 16-bit
// `MOV`.
typedef dots16_t flake_dots_t;

extern const DotRect<flake_dots_t, FLAKE_H> near sFLAKE[FLAKE_CELS];

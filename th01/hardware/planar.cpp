#include "platform.h"
#include "pc98.h"
#include "planar.h"

// TODO: These pre-constructed pointers generate much smaller usage code than
// naive on-the-fly `far` pointer construction using the SEG_PLANE_* constants.
// Ultimately, we should measure which approach is faster.
dots8_t far* VRAM_PLANE_B = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_B);
dots8_t far* VRAM_PLANE_R = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_R);
dots8_t far* VRAM_PLANE_G = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_G);
dots8_t far* VRAM_PLANE_E = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_E);

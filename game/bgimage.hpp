// Common shared background surface
// --------------------------------
// In contrast to the original game's bgimage subsystem, we simply use a
// regular shared surface on this branch. This simplifies memory management in
// the usual case where we have a single background: Due to the low heap sizes
// on PC-98, we want to keep these 128 KB constantly allocated and only free
// them once we need the memory for something other than a background image.
// Otherwise, we run the risk of intermediate allocations fragmenting the heap
// so heavily that we can't allocate another 128 KB.

#include "platform/grp_surf.hpp"

extern GrpSurface_M4 pascal bgimage;

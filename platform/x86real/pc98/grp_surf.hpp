/// PC-98 sprite and image management
/// ---------------------------------

#include "pc98.h"

// Directly blits the given PI file to the top-left corner of VRAM and
// optionally returns its palette.
int pascal GrpSurface_BlitBackgroundPI(Palette8 *palette, const char *fn);

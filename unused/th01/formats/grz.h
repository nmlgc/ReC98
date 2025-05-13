/// Run-length encoded, 16-color + alpha, 640×400 image format
/// ----------------------------------------------------------
/// ZUN did not use the single-stream .GRX format.

#include "pc98.h"

// Loading
// -------

// Loads the given .GRX file, with all of its planar streams.
int grx_load(unsigned int slot, const char *fn);

// Loads only the RLE stream of the given .GRX file.
int grx_load_noplanar(unsigned int slot, const char *fn);
// -------

// Display
// -------

// Displays the planar stream with the given number of the image loaded into
// the given GRX [slot].
void grx_put_stream(unsigned int slot, int planar_stream);

// Renders only the RLE stream in the given [col] via the GRCG, using a 0xFF
// pattern for every 8 dots to be displayed.
void grx_put_col(unsigned int slot, vc_t col);
// -------

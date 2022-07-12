/// Run-length encoded, 16-color + alpha, 640×400 image format
/// ----------------------------------------------------------
/// In contrast to .GRF, .GRX decouples the RLE command stream from the pixel
/// data. This allows either multiple pixel streams (in Planar<dots8_t*>
/// format) to be used with the same RLE stream, or the RLE stream to be used
/// on its own for a monochrome byte-aligned pattern.

// RLE stream format
enum grx_rle_t {
	// Puts the next byte from the pixel data source. No parameters.
	GC_PUT = 0,
	// Followed by:
	// * a uint8_t with the length of this run in 8-dot units
	// * a uint8_t with the command to use for all runs (0 = put, everything
	//   else = skip)
	GC_RUN = 1,
};

// Static arrays
#define GRX_COUNT 16
#define PLANAR_STREAM_PER_GRX_COUNT 16

// File format limit
#define GRZ_IMAGE_COUNT 16

// Loading
// -------
// All of these load the file with the given [fn] into the given [slot],
// automatically freeing any previously loaded image in there, and return 0
// on success or 1 on failure.

// Loads the [n]th GRX image, with all of its planar streams, from a .GRZ
// file.
int grz_load_single(unsigned int slot, const char *fn, int n);

// Loads the given .GRX file, with all of its planar streams.
int grx_load(unsigned int slot, const char *fn);

// Loads only the RLE stream of the given .GRX file.
int grx_load_noplanar(unsigned int slot, const char *fn);
// -------

// Display
// -------
// Equivalent to grz_put_stream(slot, 0);
void grx_put(unsigned int slot);

// Displays the planar stream with the given number of the image loaded into
// the given GRX [slot].
void grx_put_stream(unsigned int slot, int planar_stream);

// Renders only the RLE stream in the given [col] via the GRCG, using a 0xFF
// pattern for every 8 dots to be displayed.
void grx_put_col(unsigned int slot, uint4_t col);
// -------

// Frees both the RLE and any planar streams in the given GRX [slot].
void grx_free(unsigned int slot);
/// ----------------------------------------------------------

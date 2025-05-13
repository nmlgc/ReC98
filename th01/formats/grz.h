/// Run-length encoded, 16-color + alpha, 640×400 image format
/// ----------------------------------------------------------
/// In contrast to .GRF, .GRX decouples the RLE command stream from the pixel
/// data. This allows either multiple pixel streams (in Planar<dots8_t*>
/// format) to be used with the same RLE stream, or the RLE stream to be used
/// on its own for a monochrome byte-aligned pattern.

#include "pc98.h"

// Static arrays
#define GRX_COUNT 16
#define PLANAR_STREAM_PER_GRX_COUNT 16

// File format limit
#define GRZ_IMAGE_COUNT 16

#define HGRZ_MAGIC "HGRZ"
#define HGRX_MAGIC "HGRX"

struct grz_header_t {
	char magic[sizeof(HGRZ_MAGIC) - 1];
	uint8_t image_count;
	int8_t padding[3];
	int32_t offsets[GRZ_IMAGE_COUNT];
	int32_t total_size; // including this header
	int8_t unknown[20];
};

struct grx_header_t {
	char magic[sizeof(HGRX_MAGIC) - 1];
	uint8_t planar_stream_count;
	int8_t unused_1[3];
	uint16_t rle_stream_size;
	uint16_t planar_stream_size;
	int8_t unused_2[4];
	Palette4 palette;
};

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

// Loading
// -------

// Loads the [n]th GRX image, with all of its planar streams, from a .GRZ
// file [fn] into the given [slot], automatically freeing any previously loaded
// image in there. Returns 0 on success or 1 on failure.
int grz_load_single(unsigned int slot, const char *fn, int n);
// -------

// Display
// -------

// Equivalent to grz_put_stream(slot, 0);
void grx_put(unsigned int slot);
// -------

// Frees both the RLE and any planar streams in the given GRX [slot].
void grx_free(unsigned int slot);
/// ----------------------------------------------------------

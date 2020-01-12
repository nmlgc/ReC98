/* ReC98
 * -----
 * Main include file
 */

#include <master.h>
#include <stddef.h>
#include "platform.h"
#include "pc98.h"

// master.lib extensions
// ---------------------
#define palette_entry_rgb_show(fn) \
	palette_entry_rgb(fn); \
	palette_show();

#ifdef __cplusplus
	// master.lib palettes use twice the bits per RGB component for more
	// toning precision
	typedef RGB<uint8_t> RGB8;
	typedef Palette<RGB8> Palette8;
#endif
// ---------------------

// Macros
// ------
#define CLAMP_INC(val, max) \
	(val)++; \
	if((val) > (max)) { \
		(val) = (max); \
	}

#define CLAMP_DEC(val, min) \
	(val)--; \
	if((val) < (min)) { \
		(val) = (min); \
	}

#define RING_INC(val, ring_end) \
	(val)++; \
	if((val) > (ring_end)) { \
		(val) = 0; \
	}

#define RING_DEC(val, ring_end) \
	(val)--; \
	if((val) < 0) { \
		(val) = ring_end; \
	}

// Resident structure
#define RES_ID_LEN sizeof(RES_ID)
#define RES_ID_STRLEN (RES_ID_LEN - 1)
#define RES_PARASIZE ((sizeof(resident_t) + 0xF) >> 4)
// ------

typedef union {
	struct {
		int8_t lo, hi;
	} byte;
	int16_t v;
} twobyte_t;

/// Typedefs
/// --------
// Generic callback function types. Note the difference between function
// distance (nearfunc / farfunc) and pointer variable distance
// (t_near / t_far).
typedef void (near pascal *near nearfunc_t_near)(void);
typedef void ( far pascal *near  farfunc_t_near)(void);
typedef void (near pascal * far  nearfunc_t_far)(void);
typedef void ( far pascal * far   farfunc_t_far)(void);
/// --------

// PC-98 VRAM planes
// -----------------
// Planar 1bpp types, describing horizontal lines of 8, 16, or 32 pixels.
typedef uint8_t planar8_t;
typedef uint16_t planar16_t;
typedef uint32_t planar32_t;
// ... and the same for the rare cases where ZUN's code used signed types.
typedef int8_t splanar8_t;
typedef int16_t splanar16_t;
typedef int32_t splanar32_t;

typedef enum {
	PL_B, PL_R, PL_G, PL_E, PL_COUNT
} vram_plane_t;

typedef struct {
	planar8_t B, R, G, E;
} vram_planar_8_pixels_t;

typedef struct {
	planar16_t B, R, G, E;
} vram_planar_16_pixels_t;

typedef struct {
	planar32_t B, R, G, E;
} vram_planar_32_pixels_t;

// Since array subscripts create slightly different assembly in places, we
// offer both variants.
extern planar8_t *VRAM_PLANE[PL_COUNT];
extern planar8_t *VRAM_PLANE_B;
extern planar8_t *VRAM_PLANE_G;
extern planar8_t *VRAM_PLANE_R;
extern planar8_t *VRAM_PLANE_E;

#define VRAM_OFFSET(x, y) ((x) >> 3) + (y << 6) + (y << 4)

#define VRAM_CHUNK(plane, offset, bit_count) \
	*(planar##bit_count##_t *)(VRAM_PLANE_##plane + offset)

#define VRAM_SNAP(dst, plane, offset, bit_count) \
	dst = VRAM_CHUNK(plane, offset, bit_count);

#define VRAM_SNAP_4(dst, offset, bit_count) \
	VRAM_SNAP(dst.B, B, offset, bit_count); \
	VRAM_SNAP(dst.R, R, offset, bit_count); \
	VRAM_SNAP(dst.G, G, offset, bit_count); \
	VRAM_SNAP(dst.E, E, offset, bit_count);

#define VRAM_PUT(plane, offset, src, bit_count) \
	VRAM_CHUNK(plane, offset, bit_count) = src;

#define VRAM_PUT_4(offset, src, bit_count) \
	VRAM_PUT(B, offset, src.B, bit_count); \
	VRAM_PUT(R, offset, src.R, bit_count); \
	VRAM_PUT(G, offset, src.G, bit_count); \
	VRAM_PUT(E, offset, src.E, bit_count);

#define PLANE_DWORD_BLIT(dst, src) \
	for(p = 0; p < PLANE_SIZE; p += (int)sizeof(planar32_t)) { \
		*(planar32_t*)((dst) + p) = *(planar32_t*)((src) + p); \
	}

void pascal vram_planes_set(void);
// -----------------

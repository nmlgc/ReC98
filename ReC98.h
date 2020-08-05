/* ReC98
 * -----
 * Main include file
 */

#ifndef REC98_H
#define REC98_H

#include <master.h>
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"

// master.lib extensions
// ---------------------
#define palette_entry_rgb_show(fn) \
	palette_entry_rgb(fn); \
	palette_show();

#ifdef __cplusplus
	// master.lib palettes use twice the bits per RGB component for more
	// toning precision
	typedef RGB<uint8_t, 256> RGB8;
	typedef Palette<RGB8> Palette8;
#endif

// A version of master.lib's Point without the constructor, even in C++
struct point_t {
	int x, y;
};
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

#endif /* REC98_H */

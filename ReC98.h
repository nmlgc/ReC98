/* ReC98
 * -----
 * Main include file
 */

#ifndef REC98_H
#define REC98_H

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"

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

#ifdef __cplusplus
	// This is, in fact, the only way to circumvent 16-bit promotion inside
	// comparisons between two 8-bit values in C++. I kid you not.
	static inline char ring_min() {
		return 0;
	}
#else
	#define ring_min() 0
#endif

#define RING_INC(val, ring_end) \
	(val)++; \
	if((val) > (ring_end)) { \
		(val) = 0; \
	}

#define RING_DEC(val, ring_end) \
	(val)--; \
	if(val < ring_min()) { \
		(val) = ring_end; \
	}

// Resident structure
#define RES_ID_STRLEN (sizeof(RES_ID) - 1)
#define RES_PARASIZE ((sizeof(resident_t) + 0xF) >> 4)
// ------

#endif /* REC98_H */

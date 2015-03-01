/* ReC98
 * -----
 * Some useful random constants and macros
 */

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
// ------

// PC-98 VRAM planes
// -----------------
typedef enum {
	PL_B, PL_R, PL_G, PL_E, PL_COUNT
} vram_plane_t;

// Since array subscripts create slightly different assembly in places, we
// offer both variants.
extern char *VRAM_PLANE[PL_COUNT];
extern char *VRAM_PLANE_B;
extern char *VRAM_PLANE_G;
extern char *VRAM_PLANE_R;
extern char *VRAM_PLANE_E;

// Parenthesizing it like this avoids a signed 16-bit overflow.
#define PLANE_SIZE (640 * (400 / 8))

#define PLANE_DWORD_BLIT(dst, src) \
	for(p = 0; p < PLANE_SIZE; p += 4) { \
		*(long*)((dst) + p) = *(long*)((src) + p); \
	}

#define VRAM_OFFSET(x, y) ((x) >> 3) + (y << 6) + (y << 4)
// -----------------

/* ReC98
 * -----
 * Main include file
 */

#include <master.h>

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

#define RES_X 640
#define RES_Y 400

// PC-98 VRAM planes
// -----------------
typedef enum {
	PL_B, PL_R, PL_G, PL_E, PL_COUNT
} vram_plane_t;

typedef struct {
	char B, R, G, E;
} vram_planar_8_pixels_t;

typedef struct {
	int B, R, G, E;
} vram_planar_16_pixels_t;

// Since array subscripts create slightly different assembly in places, we
// offer both variants.
extern char *VRAM_PLANE[PL_COUNT];
extern char *VRAM_PLANE_B;
extern char *VRAM_PLANE_G;
extern char *VRAM_PLANE_R;
extern char *VRAM_PLANE_E;

#define ROW_SIZE (RES_X / 8)
#define PLANE_SIZE (ROW_SIZE * RES_Y)

#define PLANE_DWORD_BLIT(dst, src) \
	for(p = 0; p < PLANE_SIZE; p += 4) { \
		*(long*)((dst) + p) = *(long*)((src) + p); \
	}

#define VRAM_OFFSET(x, y) ((x) >> 3) + (y << 6) + (y << 4)
// -----------------

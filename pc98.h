/* ReC98
 * -----
 * Some useful PC-98 hardware constants
 */

// VRAM planes
// -----------
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
// -----------

/* ReC98
 * -----
 * Declarations for planar 4bpp graphics
 */

// 1bpp types, describing horizontal lines of 8, 16, or 32 pixels.
typedef uint8_t dots8_t;
typedef uint16_t dots16_t;
typedef uint32_t dots32_t;
// ... and the same for the rare cases where ZUN's code used signed types.
typedef int8_t sdots8_t;
typedef int16_t sdots16_t;
typedef int32_t sdots32_t;

// Defines a hardcoded 1bpp sprite, pre-shifted to all 8 start X positions
// within a single VRAM byte.
#define PRESHIFT 8

typedef enum {
	PL_B, PL_R, PL_G, PL_E, PL_COUNT
} vram_plane_t;

typedef struct {
	dots8_t B, R, G, E;
} planar8_t;

typedef struct {
	dots16_t B, R, G, E;
} planar16_t;

typedef struct {
	dots32_t B, R, G, E;
} planar32_t;

// Abstracted dot and planar types, with their width defined by a macro.
#define dots_t_(x) dots##x##_t
#define dots_t(x) dots_t_(x)
#define sdots_t_(x) sdots##x##_t
#define sdots_t(x) sdots_t_(x)
#define planar_t_(x) planar##x##_t
#define planar_t(x) planar_t_(x)

// Since array subscripts create slightly different assembly in places, we
// offer both variants.
extern dots8_t *VRAM_PLANE[PL_COUNT];
// And no, expressing these as a struct won't generate the same ASM.
// Been there, tried that.
extern dots8_t *VRAM_PLANE_B;
extern dots8_t *VRAM_PLANE_G;
extern dots8_t *VRAM_PLANE_R;
extern dots8_t *VRAM_PLANE_E;

#define VRAM_OFFSET(x, y) ((x) >> 3) + (y << 6) + (y << 4)

#ifdef __cplusplus
static inline unsigned int vram_offset_shift(int x, int y)
{
	return VRAM_OFFSET(x, y);
}

static inline unsigned int vram_offset_muldiv(int x, int y)
{
	return (y * ROW_SIZE) + (x / 8);
}
#endif

#define VRAM_CHUNK(plane, offset, bit_count) \
	*(dots##bit_count##_t *)(VRAM_PLANE_##plane + offset)

#define VRAM_SNAP(dst, plane, offset, bit_count) \
	dst = VRAM_CHUNK(plane, offset, bit_count);

#define VRAM_SNAP_PLANAR(dst, offset, bit_count) \
	VRAM_SNAP(dst.B, B, offset, bit_count); \
	VRAM_SNAP(dst.R, R, offset, bit_count); \
	VRAM_SNAP(dst.G, G, offset, bit_count); \
	VRAM_SNAP(dst.E, E, offset, bit_count);

#define VRAM_PUT(plane, offset, src, bit_count) \
	VRAM_CHUNK(plane, offset, bit_count) = src;

#define VRAM_PUT_PLANAR(offset, src, bit_count) \
	VRAM_PUT(B, offset, src.B, bit_count); \
	VRAM_PUT(R, offset, src.R, bit_count); \
	VRAM_PUT(G, offset, src.G, bit_count); \
	VRAM_PUT(E, offset, src.E, bit_count);

#define PLANE_DWORD_BLIT(dst, src) \
	for(p = 0; p < PLANE_SIZE; p += (int)sizeof(dots32_t)) { \
		*(dots32_t*)((dst) + p) = *(dots32_t*)((src) + p); \
	}

void pascal vram_planes_set(void);

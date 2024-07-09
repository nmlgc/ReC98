/* ReC98
 * -----
 * Declarations for planar 4bpp graphics
 */

#ifndef PLANAR_H
#define PLANAR_H

#include "pc98.h"

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
#define PRESHIFT BYTE_DOTS

typedef enum {
	PL_B, PL_R, PL_G, PL_E,

	_vram_plane_t_FORCE_INT16 = 0x7FFF
} vram_plane_t;

// Abstracted dot and planar types, with their width defined by a macro.
#define dots_t_(x) dots##x##_t
#define dots_t(x) dots_t_(x)
#define sdots_t_(x) sdots##x##_t
#define sdots_t(x) sdots_t_(x)

#ifdef __cplusplus
	template <class T> struct Planar {
		T B, R, G, E;

		T& operator [](int plane) {
			return (&B)[plane];
		}

		const T& operator [](int plane) const {
			return (&B)[plane];
		}
	};

	// Base template for a 1bpp rectangle, with a custom per-row data type.
	template <class RowDots, pixel_t H> struct DotRect {
		typedef RowDots row_dots_t;

		row_dots_t row[H];

		row_dots_t& operator [](pixel_t y) {
			return row[y];
		}

		const row_dots_t& operator [](pixel_t y) const {
			return row[y];
		}

		static pixel_t w() {
			return (sizeof(row_dots_t) * 8);
		}

		static pixel_t h() {
			return H;
		}
	};

	#define dot_rect_t(w, h) DotRect<dots_t(w), h>
#endif

// Since array subscripts create slightly different assembly in places, we
// offer both variants.
extern dots8_t far *VRAM_PLANE[PLANE_COUNT];
// And no, expressing these as a struct won't generate the same ASM.
// Been there, tried that.
extern dots8_t far *VRAM_PLANE_B;
extern dots8_t far *VRAM_PLANE_R;
extern dots8_t far *VRAM_PLANE_G;
extern dots8_t far *VRAM_PLANE_E;

// Byte offset of an 8-pixel-aligned X/Y position on a VRAM bitplane,
// relative to the beginning (= top-left corner) of the plane.
typedef int16_t vram_offset_t;
// MODDERS: Delete (yes, this one, not the signed one above!)
typedef uint16_t uvram_offset_t;

#define VRAM_OFFSET_SHIFT(x, y) \
	(x >> BYTE_BITS) + (y << 6) + (y << 4)

// Adds [imm] to [vo] and rolls [vo] back to the top of VRAM if it crossed the
// bottom. Necessary with hardware scrolling.
#define vram_offset_add_and_roll(vo, imm) { \
	vo += imm; \
	if(static_cast<vram_offset_t>(vo) >= PLANE_SIZE) { \
		vo -= PLANE_SIZE; \
	} \
}

#ifdef __cplusplus
// MODDERS: Replace with a single function
static inline vram_offset_t vram_offset_shift(screen_x_t x, vram_y_t y) {
	return VRAM_OFFSET_SHIFT(x, y);
}

// Avoids a reload of [y] (= one MOV instruction) compared to the regular
// vram_offset_shift().
#define vram_offset_shift_fast(x, y) ( \
	(x >> BYTE_BITS) + (_DX = (y << 6)) + (_DX >> 2) \
)

// Required to get the specific instruction encodings sometimes seen in the
// original binaries.
#define vram_offset_shift_fast_asm(asm_ret, asm_x, c_y) { \
	asm { mov	ax, asm_x; } \
	static_cast<vram_offset_t>(_AX) >>= BYTE_BITS; \
	_DX = c_y; \
	_DX <<= 6; \
	asm { add	ax, dx; } \
	_DX >>= 2; \
	asm { add	ax, dx; } \
	asm { mov	asm_ret, ax; } \
}

static inline vram_offset_t vram_offset_muldiv(screen_x_t x, vram_y_t y) {
	return (y * ROW_SIZE) + (x / BYTE_DOTS);
}

template <class T> inline vram_offset_t vram_offset_divmul(T x, T y) {
	return (x / BYTE_DOTS) + (y * ROW_SIZE);
}

static inline vram_offset_t vram_offset_divmul_wtf(screen_x_t x, vram_y_t y) {
	return ((((x + RES_X) / BYTE_DOTS) + (y * ROW_SIZE)) - ROW_SIZE);
}

static inline vram_offset_t vram_offset_mulshift(screen_x_t x, vram_y_t y) {
	return (y * ROW_SIZE) + (x >> BYTE_BITS);
}

static inline vram_offset_t vram_offset_divshift_wtf(screen_x_t x, vram_y_t y) {
	return ((((x + RES_X) / BYTE_DOTS) + (y << 6) + (y << 4)) - ROW_SIZE);
}
#endif

#define VRAM_CHUNK(plane, offset, bit_count) \
	*(dots##bit_count##_t *)(VRAM_PLANE_##plane + offset)

#define VRAM_SNAP(dst, plane, offset, bit_count) \
	dst = VRAM_CHUNK(plane, offset, bit_count);

// And no, code generation prohibits these from being turned into nice
// templated class methods. Been there, tried that.
#define VRAM_SNAP_PLANAR(dst, offset, bit_count) \
	VRAM_SNAP(dst.B, B, offset, bit_count); \
	VRAM_SNAP(dst.R, R, offset, bit_count); \
	VRAM_SNAP(dst.G, G, offset, bit_count); \
	VRAM_SNAP(dst.E, E, offset, bit_count);

#define vram_snap_planar_masked(dst, offset, bit_count, mask) \
	dst.B = VRAM_CHUNK(B, offset, bit_count) & mask; \
	dst.R = VRAM_CHUNK(R, offset, bit_count) & mask; \
	dst.G = VRAM_CHUNK(G, offset, bit_count) & mask; \
	dst.E = VRAM_CHUNK(E, offset, bit_count) & mask;

#define VRAM_PUT(plane, offset, src, bit_count) \
	VRAM_CHUNK(plane, offset, bit_count) = src;

#define VRAM_PUT_PLANAR(offset, src, bit_count) \
	VRAM_PUT(B, offset, src.B, bit_count); \
	VRAM_PUT(R, offset, src.R, bit_count); \
	VRAM_PUT(G, offset, src.G, bit_count); \
	VRAM_PUT(E, offset, src.E, bit_count);

#define vram_or_emptyopt(plane, offset, src, bit_count) \
	if(src) { \
		VRAM_CHUNK(plane, offset, bit_count) |= src; \
	}

#define vram_or_masked_emptyopt(plane, offset, bit_count, src, mask) \
	if(src) { \
		VRAM_CHUNK(plane, offset, bit_count) |= (src & mask); \
	}

#define vram_or_planar(offset, src, bit_count) \
	VRAM_CHUNK(B, offset, bit_count) |= src.B; \
	VRAM_CHUNK(R, offset, bit_count) |= src.R; \
	VRAM_CHUNK(G, offset, bit_count) |= src.G; \
	VRAM_CHUNK(E, offset, bit_count) |= src.E;

#define vram_or_planar_masked(offset, src, bit_count, mask) \
	VRAM_CHUNK(B, offset, bit_count) |= (src.B & mask); \
	VRAM_CHUNK(R, offset, bit_count) |= (src.R & mask); \
	VRAM_CHUNK(G, offset, bit_count) |= (src.G & mask); \
	VRAM_CHUNK(E, offset, bit_count) |= (src.E & mask);

#define vram_or_planar_emptyopt(offset, src, bit_count) \
	vram_or_emptyopt(B, offset, src.B, bit_count); \
	vram_or_emptyopt(R, offset, src.R, bit_count); \
	vram_or_emptyopt(G, offset, src.G, bit_count); \
	vram_or_emptyopt(E, offset, src.E, bit_count);

// Converts the given ([x], [y]) position to an x86 segment inside the B plane.
// Only defined for paragraph-aligned values of [x], i.e., multiples of 128
// pixels.
#define grcg_segment(x, y) ( \
	static_assert((((y * ROW_SIZE) + (x / BYTE_DOTS)) % 16) == 0), \
	(SEG_PLANE_B + (((y * ROW_SIZE) + (x / BYTE_DOTS)) / 16)) \
)

#define grcg_chunk(vram_offset, bit_count) \
	VRAM_CHUNK(B, vram_offset, bit_count)

#define grcg_chunk_8(vram_offset) \
	peekb(SEG_PLANE_B, vram_offset)

#define grcg_put(offset, src, bit_count) \
	VRAM_PUT(B, offset, src, bit_count)

#define grcg_put_emptyopt(offset, src, bit_count) \
	if(src) { \
		grcg_put(offset, src, bit_count); \
	}

#define grcg_put_8(offset, src) \
	/* Nope, pokeb() doesn't generate the same code */ \
	*reinterpret_cast<dots8_t *>(MK_FP(SEG_PLANE_B, offset)) = src

// EGC
// ---

// ZUN bloat: Dummy value returned from an EGC copy read. Can be replaced with
// a pseudoregister to avoid one unnecessary store (for snapping) or load (for
// blitting) per EGC operation.
typedef dots16_t egc_temp_t;

#define egc_chunk(offset) \
	/* For code generation reasons, [offset] must NOT be parenthesized here */ \
	VRAM_CHUNK(B, offset, 16)
// ----------

#endif /* PLANAR_H */

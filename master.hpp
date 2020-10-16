/* ReC98
 * -----
 * C++ redeclarations and ReC98-specific extensions for master.lib.
 */

/// Types
/// -----

// A version of master.lib's Point without the constructor, even in C++
struct point_t {
	int x, y;
};

#ifdef PC98_H
	struct screen_point_t {
		screen_x_t x;
		screen_y_t y;
	};

	#if defined(__cplusplus)
	// master.lib palettes use twice the bits per RGB component for more
	// toning precision
	typedef RGB<uint8_t, 256> RGB8;
	typedef Palette<RGB8> Palette8;
	#endif
#endif
/// -----

/// Memory model definitions (adapted from master.h)
/// ------------------------------------------------
#if !defined(MASTER_NEAR) && !defined(MASTER_FAR) && !defined(MASTER_COMPACT) && !defined(MASTER_MEDIUM)
	#if defined(__SMALL__) || defined(__TINY__) || defined(M_I86SM) || defined(M_I86TM)
		#define MASTER_NEAR
	#elif defined(__COMPACT__) || defined(M_I86CM)
		#define MASTER_COMPACT
	#elif defined(__MEDIUM__) || defined(M_I86MM)
		#define MASTER_MEDIUM
	#elif defined(__LARGE__) || defined(__HUGE__) || defined(M_I86LM) || defined(M_I86HM)
		#define MASTER_FAR
	#endif
#endif

#if defined(MASTER_NEAR)
	#define MASTER_RET near pascal
	#define MASTER_CRET near cdecl
	#define MASTER_PTR near
#elif defined(MASTER_FAR)
	#define MASTER_RET far pascal
	#define MASTER_CRET far cdecl
	#define MASTER_PTR far
#elif defined(MASTER_COMPACT)
	#define MASTER_RET near pascal
	#define MASTER_CRET near cdecl
	#define MASTER_PTR far
#elif defined(MASTER_MEDIUM)
	#define MASTER_RET far pascal
	#define MASTER_CRET far cdecl
	#define MASTER_PTR near
#endif

#ifndef MASTER_RET
	#error Memory model for master.lib could not be determined?
#endif
/// ------------------------------------------------

/// Original functions (only contains those actually called from ZUN code)
/// ----------------------------------------------------------------------

// VSync
// -----

extern unsigned volatile int vsync_Count1, vsync_Count2;

#define vsync_reset1()	(vsync_Count1 = 0)
#define vsync_reset2()	(vsync_Count2 = 0)

void MASTER_RET vsync_start(void);
void MASTER_RET vsync_end(void);
// -----
/// ----------------------------------------------------------------------

/// Inlined extensions
/// ------------------
#define palette_entry_rgb_show(fn) \
	palette_entry_rgb(fn); \
	palette_show();
/// ------------------

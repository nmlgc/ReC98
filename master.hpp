/* ReC98
 * -----
 * C++ redeclarations and ReC98-specific extensions for master.lib.
 * Definitions that require types from `pc98.h` are guarded via `#ifdef`,
 * allowing this header to be used on its own if those aren't required.
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
/// TODO: Remove the `!defined(__MASTER_H)` branches once we've gotten rid of
/// of master.h.

// Graphics
// --------

#if !defined(__MASTER_H)
#define graph_showpage(p) \
	outportb(0xA4, p)

#define graph_accesspage(p) \
	outportb(0xA6, p)
#endif

extern unsigned graph_VramZoom;

void MASTER_RET graph_400line(void);
void MASTER_RET graph_200line(int tail);
void MASTER_RET graph_clear(void);
void MASTER_RET graph_show(void);
void MASTER_RET graph_hide(void);
void MASTER_RET graph_start(void);
int MASTER_RET graph_copy_page(int to_page);

#if !defined(__MASTER_H) && defined(PC98_H) && defined(__cplusplus)
	void MASTER_RET graph_gaiji_putc(int x, int y, int c, int color);
	void MASTER_RET graph_gaiji_puts(
		int x, int y, int step, const char MASTER_PTR *str, int color
	);

	// Clipping
	int MASTER_RET grc_setclip(int xl, int yt, int xr, int yb);
	int MASTER_RET grc_clip_polygon_n(
		screen_point_t MASTER_PTR *dest,
		int ndest,
		const screen_point_t MASTER_PTR *src,
		int nsrc
	);
#endif
// --------

// Palette
// -------

void MASTER_RET palette_show(void);

#if !defined(__MASTER_H)
#define palette_settone(tone) \
	(PaletteTone = (tone), palette_show())

#define palette_100() \
	palette_settone(100)

#define palette_black() \
	palette_settone(0)

#define palette_white() \
	palette_settone(200)
#endif

#if !defined(__MASTER_H) && defined(PC98_H) && defined(__cplusplus)
	#define palette_set(col, r, g, b) (\
		Palettes[col].v[0] = (uint8_t)(r), \
		Palettes[col].v[1] = (uint8_t)(g), \
		Palettes[col].v[2] = (uint8_t)(b) \
	)

	#define palette_set_all(m) \
		memcpy(Palettes, (m), sizeof(Palette8))

	extern Palette8 Palettes;
#endif

extern unsigned int PaletteTone;

int MASTER_RET palette_entry_rgb(const char MASTER_PTR *);
void MASTER_RET palette_black_in(unsigned speed);
void MASTER_RET palette_black_out(unsigned speed);
void MASTER_RET palette_white_in(unsigned speed);
void MASTER_RET palette_white_out(unsigned speed);
// -------

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

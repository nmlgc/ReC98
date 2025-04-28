// C++ declarations and ReC98-specific extensions for the PC-98 graphics subset
// of master.lib used by the original game code.

#ifndef MASTER_PC98_GFX_HPP
#define MASTER_PC98_GFX_HPP

#include "libs/master.lib/func.hpp"
#include "pc98.h"
#include "x86real.h"

// Types
// -----

// master.lib palettes use twice the bits per RGB component for more
// toning precision
typedef RGB<uint8_t, 256> RGB8;
typedef Palette<RGB8> Palette8;
/// -----

/// Original functions
/// ------------------

#ifdef __cplusplus
extern "C" {
#endif

// EGC
// ---

#define EGC_ACTIVEPLANEREG	0x04a0
#define EGC_READPLANEREG  	0x04a2
#define EGC_MODE_ROP_REG  	0x04a4
#define EGC_FGCOLORREG    	0x04a6
#define EGC_MASKREG       	0x04a8
#define EGC_BGCOLORREG    	0x04aa
#define EGC_ADDRRESSREG   	0x04ac
#define EGC_BITLENGTHREG  	0x04ae

#define EGC_COMPAREREAD	0x2000
#define EGC_WS_PATREG  	0x1000	/* WS = write source */
#define EGC_WS_ROP     	0x0800	/* parren reg, ans of rop, cpu data */
#define EGC_WS_CPU     	0x0000
#define EGC_SHIFT_CPU  	0x0400	/* input to shifter */
#define EGC_SHIFT_VRAM 	0x0000	/* cpu write, vram read */
#define EGC_RL_MEMWRITE	0x0200	/* RL = pattern Register Load */
#define EGC_RL_MEMREAD 	0x0100	/* ^at mem write, <-at mem read */
#define EGC_RL_NONE    	0x0000	/* no touch */

// TODO: Document and add helpful macros for the EGC raster ops

void MASTER_RET egc_on(void);
void MASTER_RET egc_off(void);
void MASTER_RET egc_start(void);

typedef void MASTER_RET egc_shift_func_t(
	screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2, pixel_t dots
);
void MASTER_RET egc_shift_down(
	screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2, pixel_t dots
);
void MASTER_RET egc_shift_left(
	screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2, pixel_t dots
);
void MASTER_RET egc_shift_left_all(pixel_t dots);
void MASTER_RET egc_shift_right(
	screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2, pixel_t dots
);
void MASTER_RET egc_shift_up(
	screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2, pixel_t dots
);
// ---

// Gaiji
// -----

void MASTER_RET gaiji_putca(unsigned x, unsigned y, unsigned c, unsigned atrb);
void MASTER_RET gaiji_putsa(
	unsigned x, unsigned y, const char MASTER_PTR *str, unsigned atrb
);

int MASTER_RET gaiji_backup(void);
int MASTER_RET gaiji_restore(void);
int MASTER_RET gaiji_entry_bfnt(const char MASTER_PTR *filename);
// -----

// Graphics
// --------

#define graph_showpage(p) \
	outportb(0xA4, p)

#define graph_accesspage(p) \
	outportb(0xA6, p)

extern unsigned graph_VramZoom;

void MASTER_RET graph_400line(void);
void MASTER_RET graph_200line(int tail);
void MASTER_RET graph_clear(void);
void MASTER_RET graph_show(void);
void MASTER_RET graph_hide(void);
void MASTER_RET graph_start(void);
int MASTER_RET graph_copy_page(int to_page);
void MASTER_RET graph_scrollup(unsigned line);

// master.lib bug: In all game-specific versions before TH04, these
// functions accidentally add the x86 carry flag on top of [c].
void MASTER_RET graph_gaiji_putc(screen_x_t left, vram_y_t top, int c, vc2 col);
void MASTER_RET graph_gaiji_puts(
	screen_x_t left,
	vram_y_t top,
	pixel_t step,
	const char MASTER_PTR *str,
	vc2 col
);

// Clipping
int MASTER_RET grc_setclip(int xl, int yt, int xr, int yb);
int MASTER_RET grc_clip_polygon_n(
	screen_point_t MASTER_PTR *dest,
	int ndest,
	const screen_point_t MASTER_PTR *src,
	int nsrc
);
// --------

// GRCG-accelerated graphics
// -------------------------

/* grcg_setcolor()や vgc_setcolor()に指定するアクセスプレーン指定 */
#define GC_B	0x0e	/* 青プレーンをアクセスする */
#define GC_R	0x0d
#define GC_BR	0x0c	/*	:  */
#define GC_G	0x0b	/*	:  */
#define GC_BG	0x0a	/*	:  */
#define GC_RG	0x09
#define GC_BRG	0x08	/*	:  */
#define GC_I	0x07
#define GC_BI	0x06
#define GC_RI	0x05
#define GC_BRI	0x04
#define GC_GI	0x03
#define GC_BGI	0x02
#define GC_RGI	0x01	/*	:  */
#define GC_BRGI	0x00	/* 全プレーンをアクセスする */

/* grcg_setcolor()の modeに設定する値 */
#define GC_OFF	0
#define GC_TDW	0x80	/* 書き込みﾃﾞｰﾀは無視して、ﾀｲﾙﾚｼﾞｽﾀの内容を書く */
#define GC_TCR	0x80	/* ﾀｲﾙﾚｼﾞｽﾀと同じ色のﾋﾞｯﾄが立って読み込まれる */
#define GC_RMW	0xc0	/* 書き込みﾋﾞｯﾄが立っているﾄﾞｯﾄにﾀｲﾙﾚｼﾞｽﾀから書く */

void MASTER_RET grcg_setcolor(int mode, vc2 color);
void MASTER_RET grcg_settile_1line(int mode, long tile);

// Just in case this is #included after `th01/hardware/grcg.hpp`...
#ifndef grcg_off
	void MASTER_RET grcg_off(void);
#endif

// Trapezoids
void MASTER_RET grcg_trapezoid(
	int y1, int x11, int x12, int y2, int x21, int x22
);

// Polygons
void MASTER_RET grcg_polygon_c(
	const screen_point_t MASTER_PTR *pts, int npoint
);
void MASTER_RET grcg_polygon_cx(
	const screen_point_t MASTER_PTR *pts, int npoint
);

// Triangles
void MASTER_RET grcg_triangle(int x1, int y1, int x2, int y2, int x3, int y3);

// Straight lines
void MASTER_RET grcg_hline(int x1, int x2, int y);
void MASTER_RET grcg_vline(int x, int y1, int y2);
void MASTER_RET grcg_line(
	screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2
);

// Rectangles
void MASTER_RET grcg_boxfill(int x1, int y1, int x2, int y2);
void MASTER_RET grcg_pset(int x, int y);
void MASTER_RET grcg_fill(void);
void MASTER_RET grcg_round_boxfill(int x1, int y1, int x2, int y2, unsigned r);
void MASTER_RET grcg_byteboxfill_x(
	vram_x_t left, vram_y_t top, vram_x_t right, vram_y_t bottom
);

// Circles
void MASTER_RET grcg_circle(
	screen_x_t center_x, vram_y_t center_y, unsigned r
);
void MASTER_RET grcg_circlefill(int x, int y, unsigned r);
// -------------------------

// Palette
// -------

inline char tone_black() { return   0; }
inline char tone_100()   { return 100; }
inline char tone_white() { return 200; }

void MASTER_RET palette_show(void);

#define palette_settone(tone) \
	(PaletteTone = (tone), palette_show())

#define palette_100() \
	palette_settone(100)

#define palette_black() \
	palette_settone(0)

#define palette_white() \
	palette_settone(200)

#define palette_set(col, r, g, b) (\
	Palettes[col].v[0] = (uint8_t)(r), \
	Palettes[col].v[1] = (uint8_t)(g), \
	Palettes[col].v[2] = (uint8_t)(b) \
)

#define palette_set_all(m) \
	memcpy( \
		reinterpret_cast<void *>(&Palettes), \
		reinterpret_cast<void *>(&m), \
		sizeof(Palette8) \
	);

extern Palette8 Palettes;

extern unsigned int PaletteTone;

int MASTER_RET palette_entry_rgb(const char MASTER_PTR *);
void MASTER_RET palette_black_in(unsigned speed);
void MASTER_RET palette_black_out(unsigned speed);
void MASTER_RET palette_white_in(unsigned speed);
void MASTER_RET palette_white_out(unsigned speed);
// -------

// .PI
// ---

struct PiHeader {
	char far *comment;	// graph_pi_load.*() sets this to a nullptr
	uint16_t commentlen;	//
	uint8_t mode;	//
	uint8_t n;	// aspect
	uint8_t m;	// aspect
	uint8_t plane;	// usually 4
	char machine[4];	//
	uint16_t maexlen;	// machine extend data length
	void far * maex;	// machine extend data
	uint16_t xsize;
	uint16_t ysize;
	Palette8 palette;
};

int MASTER_RET graph_pi_load_pack(
	const char MASTER_PTR *filename,
	struct PiHeader MASTER_PTR *header,
	void far *MASTER_PTR *bufptr
);
void MASTER_RET graph_pi_free(
	struct PiHeader MASTER_PTR *header, const void far* image
);
void MASTER_RET graph_pack_put_8(
	int x, int y, const void far *linepat, int len
);

// Copy of graph_pack_put_8() that does not clip the Y coordinate to
// the vertical grc_setclip() coordinates. Necessary for temporary blits to
// the 400th VRAM row.
void MASTER_RET graph_pack_put_8_noclip(
	screen_x_t left, screen_y_t top, const void far *linepat, pixel_t len
);
// ---

// Superimpose sprites
// -------------------

#define SUPER_MAXPAT  512

// pattern_plane
#define PATTERN_ERASE 0
#define PATTERN_BLUE  1
#define PATTERN_RED   2
#define PATTERN_GREEN 3
#define PATTERN_INTEN 4

// put_plane
#define PLANE_ERASE 0x00c0
#define PLANE_BLUE  0xffce
#define PLANE_RED   0xffcd
#define PLANE_GREEN 0xffcb
#define PLANE_INTEN 0xffc7

extern unsigned super_patnum;
extern unsigned super_patdata[SUPER_MAXPAT];
extern unsigned super_patsize[SUPER_MAXPAT];

// Ignores transparency
void MASTER_RET over_put_8(int x, int y, int num);

int MASTER_RET super_cancel_pat(int num);
void MASTER_RET super_clean(int min_pat, int max_pat);
int MASTER_RET super_entry_bfnt(const char MASTER_PTR *);
void MASTER_RET super_free(void);

int MASTER_RET super_convert_tiny(int num);
void MASTER_RET super_large_put(int x, int y, int num);
void MASTER_RET super_put(int x, int y, int num);
void MASTER_RET super_put_1plane(
	int x, int y, int num, int pattern_plane, unsigned put_plane
);
void MASTER_RET super_put_8(int x, int y, int num);

void MASTER_RET super_put_rect(int x, int y, int num);
void MASTER_RET super_roll_put(int x, int y, int num);
void MASTER_RET super_roll_put_1plane(
	int x, int y, int num, int pattern_plane, unsigned put_plane
);
void MASTER_RET super_zoom(int x, int y, int num, int zoom);

void MASTER_RET super_put_tiny_small(int x, int y, int num);
void MASTER_RET super_roll_put_tiny(int x, int y, int num);

void MASTER_RET super_wave_put(
	int x, int y, int num, int len, char amp, int ph
);
// -------------------

// Text RAM
// --------

#define text_width()  80
void MASTER_RET text_boxfilla(
	unsigned x1, unsigned y1, unsigned x2, unsigned y2, unsigned atrb
);
void MASTER_RET text_clear(void);
void MASTER_RET text_fillca(unsigned ch, unsigned atrb);
void MASTER_RET text_putca(unsigned x, unsigned y, unsigned ch, unsigned atrb);
void MASTER_RET text_puts(unsigned x, unsigned y, const char MASTER_PTR *str);
void MASTER_RET text_putsa(
	unsigned x, unsigned y, const char MASTER_PTR *str, unsigned atrb
);

void MASTER_RET text_cursor_hide(void);
void MASTER_RET text_cursor_show(void);
void MASTER_RET text_systemline_hide(void);
void MASTER_RET text_systemline_show(void);
void MASTER_RET text_show(void);
void MASTER_RET text_hide(void);

// Attributes
#define TX_BLACK    	0x01
#define TX_BLUE     	0x21
#define TX_RED      	0x41
#define TX_MAGENTA  	0x61
#define TX_GREEN    	0x81
#define TX_CYAN     	0xa1
#define TX_YELLOW   	0xc1
#define TX_WHITE    	0xe1
#define TX_BLINK    	2
#define TX_REVERSE  	4
#define TX_UNDERLINE	8
// --------

#ifdef __cplusplus
}
#endif
/// ------------------

/// Inlined extensions
/// ------------------

#define grcg_boxfill_8(left, top, right, bottom) \
	grcg_byteboxfill_x( \
		((left) / BYTE_DOTS), top, ((right) / BYTE_DOTS), bottom \
	)

#define palette_entry_rgb_show(fn) \
	palette_entry_rgb(fn); \
	palette_show();

// Generates a super_roll_put_1plane() [plane_put] constant for blitting the
// sprite in the single given color.
inline uint16_t super_plane(vc_t col, bool erase = false) {
	return (
		(erase ? PLANE_ERASE : (0xFF00 | GC_RMW)) + ((COLOR_COUNT - 1) - col)
	);
}
/// ------------------

#endif /* MASTER_PC98_GFX_HPP */

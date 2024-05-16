/* ReC98
 * -----
 * C++ declarations and ReC98-specific extensions for the subset of master.lib
 * used by the original game code.
 * Definitions that require types from `pc98.h` are guarded via `#ifdef`,
 * allowing this header to be used on its own if those aren't required.
 */

#ifndef MASTER_HPP
#define MASTER_HPP

/// Types
/// -----

#if (defined(PC98_H) && defined(__cplusplus))
	// master.lib palettes use twice the bits per RGB component for more
	// toning precision
	typedef RGB<uint8_t, 256> RGB8;
	typedef Palette<RGB8> Palette8;
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

#ifdef __cplusplus
extern "C" {
#endif

// "BGM" (only used for Beep sound effects)
// ----------------------------------------

int MASTER_RET bgm_init(int bufsiz);
void MASTER_RET bgm_finish(void);
int MASTER_RET bgm_read_sdata(const char MASTER_PTR *fn);
int MASTER_RET bgm_sound(int num);
// ----------------------------------------

// DOS
// ---
// These use INT 21h syscalls as directly as possible.

int MASTER_RET dos_getch(void);
void MASTER_RET dos_putch(int chr);
void MASTER_RET dos_puts(const char MASTER_PTR * str);
void MASTER_RET dos_puts2(const char MASTER_PTR *string);

void MASTER_RET dos_free(void __seg *seg);
int MASTER_RET dos_create(const char MASTER_PTR *filename, int attrib);
int MASTER_RET dos_close(int fh);
int MASTER_RET dos_write(int fh, const void far *buffer, unsigned len);
long MASTER_RET dos_seek(int fh, long offs, int mode);

long MASTER_RET dos_axdx(int axval, const char MASTER_PTR *strval);
// ---

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

void MASTER_RET egc_on(void);
void MASTER_RET egc_off(void);
void MASTER_RET egc_start(void);

#define egc_selectpat() \
	outport(EGC_READPLANEREG, 0x00ff)

// TODO: Document and add helpful macros for the EGC raster ops
#define egc_setrop(mode_rop) \
	outport(EGC_MODE_ROP_REG, mode_rop)

#ifdef PC98_H
	typedef void MASTER_RET egc_shift_func_t(
		screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2, pixel_t dots
	);
	void MASTER_RET egc_shift_down(
		screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2, pixel_t dots
	);
	void MASTER_RET egc_shift_left(
		screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2, pixel_t dots
	);
	void MASTER_RET egc_shift_right(
		screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2, pixel_t dots
	);
	void MASTER_RET egc_shift_up(
		screen_x_t x1, vram_y_t y1, screen_x_t x2, vram_y_t y2, pixel_t dots
	);
#endif
// ---

// EMS
// ---

unsigned MASTER_RET ems_allocate(unsigned long len);
int MASTER_RET ems_exist(void);
int MASTER_RET ems_read(unsigned handle, long offset, void far *mem, long size);
int MASTER_RET ems_setname(unsigned handle, const char MASTER_PTR * name);
unsigned long MASTER_RET ems_space(void);
int MASTER_RET ems_write(
	unsigned handle, long offset, const void far *mem, long size
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

#if defined(PC98_H) && defined(__cplusplus)
	// master.lib bug: In all game-specific versions before TH04, these
	// functions accidentally add the x86 carry flag on top of [c].
	void MASTER_RET graph_gaiji_putc(
		screen_x_t left, vram_y_t top, int c, vc2 col
	);
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
#endif
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

#ifdef PC98_H
	void MASTER_RET grcg_setcolor(int mode, vc2 color);
#endif
void MASTER_RET grcg_settile_1line(int mode, long tile);

// Just in case this is #included after `th01/hardware/grcg.hpp`...
#ifndef grcg_off
	void MASTER_RET grcg_off(void);
#endif

#if defined(PC98_H) && defined(__cplusplus)
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
	void MASTER_RET grcg_triangle(
		int x1, int y1, int x2, int y2, int x3, int y3
	);

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
	void MASTER_RET grcg_round_boxfill(
		int x1, int y1, int x2, int y2, unsigned r
	);
	void MASTER_RET grcg_byteboxfill_x(
		vram_x_t left, vram_y_t top, vram_x_t right, vram_y_t bottom
	);

	// Circles
	void MASTER_RET grcg_circle(
		screen_x_t center_x, vram_y_t center_y, unsigned r
	);
	void MASTER_RET grcg_circlefill(int x, int y, unsigned r);
#endif
// -------------------------

// Joystick
// --------

extern int js_bexist;
extern unsigned js_stat[2];

int MASTER_RET js_start();	// ZUN removed the [force] parameter

void MASTER_RET js_end(void);
int MASTER_RET js_sense(void);
// --------

// Keyboard
// --------

void MASTER_RET key_start(void);
void MASTER_RET key_end(void);

void MASTER_RET key_beep_on(void);
void MASTER_RET key_beep_off(void);
int MASTER_RET key_sense(int keygroup);

unsigned MASTER_RET key_sense_bios(void);
// --------

// Heap
// ----

void MASTER_RET mem_assign(unsigned top_seg, unsigned parasize);
void MASTER_RET mem_assign_all(void);
int MASTER_RET mem_unassign(void);
int MASTER_RET mem_assign_dos(unsigned parasize);

// Regular
void __seg* MASTER_RET hmem_allocbyte(unsigned bytesize);
void MASTER_RET hmem_free(void __seg* memseg);
// Fast
unsigned MASTER_RET smem_wget(unsigned bytesize);
void MASTER_RET smem_release(unsigned memseg);
// ----

// Machine identification
// ----------------------

extern const unsigned Machine_State;

unsigned MASTER_RET get_machine(void);

#define PC_AT        	0x0010
#define PC9801       	0x0020
#define FMR          	0x0080	/* 0.23追加 */
#define DOSBOX       	0x8000	/* 0.22k追加 */

#define DESKTOP      	0x0001
#define EPSON        	0x0002
#define PC_MATE      	0x0004
#define HIRESO       	0x0008

#define LANG_US      	0x0001
#define PC_TYPE_MASK 	0x000e
#define PS55         	0x0000
#define DOSV         	0x0002
#define PC_AX        	0x0004
#define J3100        	0x0006
#define DR_DOS       	0x0008
#define MSDOSV       	0x000a
#define VTEXT        	0x0240	/* 0.23追加 */
#define DOSVEXTENTION	0x0040	/* 0.22d追加 */
#define SUPERDRIVERS 	0x0200	/* 0.23追加 */
#define ANSISYS      	0x0100	/* 0.22d追加 */
// ----------------------

// Math
// ----

extern const short __cdecl SinTable8[256], CosTable8[256];
extern long __cdecl random_seed;

#define Sin8(t) SinTable8[(t) & 0xff]
#define Cos8(t) CosTable8[(t) & 0xff]

int MASTER_RET iatan2(int y, int x);
int MASTER_RET isqrt(long x);
int MASTER_RET ihypot(int x, int y);

#define irand_init(seed) \
	(random_seed = (seed))
int MASTER_RET irand(void);
// ----

// Optionally buffered single-file I/O
// -----------------------------------

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

int MASTER_RET file_ropen(const char MASTER_PTR *filename);
int MASTER_RET file_read(void far *buf, unsigned wsize);
long MASTER_RET file_size(void);
int MASTER_RET file_create(const char MASTER_PTR *filename);
int MASTER_RET file_append(const char MASTER_PTR *filename);
int MASTER_RET file_write(const void far *buf, unsigned wsize);
void MASTER_RET file_seek(long pos, int dir);
void MASTER_RET file_close(void);
int MASTER_RET file_exist(const char MASTER_PTR *filename);
int MASTER_RET file_delete(const char MASTER_PTR *filename);
// -----------------------------------

// Packfiles
// ---------

extern unsigned char pfkey; // 復号化キー
extern unsigned bbufsiz;    // バッファサイズ

void MASTER_RET pfstart(const unsigned char MASTER_PTR *parfile);
void MASTER_RET pfend(void);
#define pfsetbufsiz(bufsiz) \
	bbufsiz = bufsiz;
// ---------

// Palette
// -------

#ifdef __cplusplus
	inline char tone_black() { return   0; }
	inline char tone_100()   { return 100; }
	inline char tone_white() { return 200; }
#endif

void MASTER_RET palette_show(void);

#define palette_settone(tone) \
	(PaletteTone = (tone), palette_show())

#define palette_100() \
	palette_settone(100)

#define palette_black() \
	palette_settone(0)

#define palette_white() \
	palette_settone(200)

#if defined(PC98_H) && defined(__cplusplus)
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
#endif

extern unsigned int PaletteTone;

int MASTER_RET palette_entry_rgb(const char MASTER_PTR *);
void MASTER_RET palette_black_in(unsigned speed);
void MASTER_RET palette_black_out(unsigned speed);
void MASTER_RET palette_white_in(unsigned speed);
void MASTER_RET palette_white_out(unsigned speed);
// -------

// .PI
// ---

#if defined(__cplusplus) && defined(PC98_H)
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
#endif
// ---

// Resident data
// -------------

void __seg* MASTER_RET resdata_exist(
      const char MASTER_PTR *id, unsigned idlen, unsigned parasize
);
void __seg* MASTER_RET resdata_create(
      const char MASTER_PTR *id, unsigned idlen, unsigned parasize
);

#define resdata_free(seg) \
	dos_free(seg)
// -------------

// Resident palettes
// -----------------

int MASTER_RET respal_exist(void);
int MASTER_RET respal_create(void);
void MASTER_RET respal_get_palettes(void);
void MASTER_RET respal_set_palettes(void);
void MASTER_RET respal_free(void);
// -----------------

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

// VSync
// -----

// Incremented by 1 on every VSync interrupt. Can be manually reset to 0 to
// simplify frame delay loops.
extern __cdecl volatile unsigned int vsync_Count1, vsync_Count2;

void MASTER_RET vsync_start(void);
void MASTER_RET vsync_end(void);
// -----
#ifdef __cplusplus
}
#endif
/// ----------------------------------------------------------------------

/// Inlined extensions
/// ------------------
#define grcg_boxfill_8(left, top, right, bottom) \
	grcg_byteboxfill_x( \
		((left) / BYTE_DOTS), top, ((right) / BYTE_DOTS), bottom \
	)

#define palette_entry_rgb_show(fn) \
	palette_entry_rgb(fn); \
	palette_show();

#ifdef __cplusplus
	// Type-safe hmem_* memory allocation
	template<class T> struct HMem {
		static T __seg* alloc(unsigned int size_in_elements) {
			return reinterpret_cast<T __seg *>(hmem_allocbyte(
				size_in_elements * sizeof(T)
			));
		}

		static void free(T *&block) {
			hmem_free(reinterpret_cast<void __seg *>(block));
		}

		static void free(T __seg *&block) {
			hmem_free(reinterpret_cast<void __seg *>(block));
		}
	};

	// Type-safe resident structure allocation and retrieval
	template <class T> struct ResData {
		static unsigned int id_len() {
			return (sizeof(reinterpret_cast<T *>(0)->id) - 1);
		}

		static T __seg* create(const char MASTER_PTR *id) {
			return reinterpret_cast<T __seg *>(resdata_create(
				id, id_len(), ((sizeof(T) + 0xF) >> 4)
			));
		}

		static T __seg* exist(const char MASTER_PTR *id) {
			return reinterpret_cast<T __seg *>(resdata_exist(
				id, id_len(), ((sizeof(T) + 0xF) >> 4)
			));
		}

		// Workarounds for correct code generation
		static T __seg* create_with_id_from_pointer(const char *&id) {
			return reinterpret_cast<T __seg *>(resdata_create(
				id, id_len(), ((sizeof(T) + 0xF) >> 4)
			));
		}

		static T __seg* exist_with_id_from_pointer(const char *&id) {
			return reinterpret_cast<T __seg *>(resdata_exist(
				id, id_len(), ((sizeof(T) + 0xF) >> 4)
			));
		}
	};

	#ifdef PC98_H
		// Generates a super_roll_put_1plane [plane_put] constant for blitting
		// the sprite in the single given color.
		inline uint16_t super_plane(vc_t col, bool erase = false) {
			return (
				(erase ? PLANE_ERASE : (0xFF00 | GC_RMW)) +
				((COLOR_COUNT - 1) - col)
			);
		}
	#endif
#endif
/// ------------------

#endif /* MASTER_HPP */

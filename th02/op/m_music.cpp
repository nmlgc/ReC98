#if (GAME == 2)
	#pragma option -2 // ZUN bloat
#endif

#include <mem.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "libs/kaja/kaja.h"
#include "libs/master.lib/master.hpp"
#include "game/coords.hpp"
#include "th02/v_colors.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/formats/musiccmt.hpp"
#if (GAME == 5)
	#include "th05/hardware/input.h"
#elif (GAME == 4)
	#include "th04/hardware/input.h"
#elif (GAME == 3)
	#include "th03/hardware/input.h"
#else
	#include "th02/hardware/input.hpp"
#endif
#if (GAME >= 4)
	#include "th01/hardware/grcg.hpp"
	#include "th04/hardware/bgimage.hpp"
	#include "th04/hardware/grppsafx.h"
	#include "th04/snd/snd.h"
#else
	#include "th01/hardware/grppsafx.h"
	#include "th02/snd/snd.h"
#endif
#if (GAME >= 3)
	#include "th03/formats/cdg.h"
	#include "th03/math/polar.hpp"
#else
	#include "th01/math/polar.hpp"
#endif
#include "th02/op/m_music.hpp"
#if (GAME == 5)
	#include "th01/math/clamp.hpp"
	#include "th05/formats/pi.hpp"
	#include "th05/op/piano.hpp"
	#include "th05/shiftjis/fns.hpp"
	#include "th05/shiftjis/music.hpp"

	int game_sel = (GAME_COUNT - 1);
	const int TRACK_COUNT[GAME_COUNT] = { 14, 18, 24, 28, 23 };
#else
	#include "th02/formats/pi.h"
	#if (GAME == 4)
		#include "th04/shiftjis/music.hpp"
	#elif (GAME == 3)
		#include "th03/shiftjis/music.hpp"
	#elif (GAME == 2)
		#include "th02/shiftjis/music.hpp"
	#endif
	static const size_t TRACK_COUNT = (
		sizeof(MUSIC_FILES) / sizeof(MUSIC_FILES[0])
	);
#endif

// Colors
// ------
// The Music Room only redraws text whenever it changes, but fully redraws the
// B plane on every frame – first by blitting [nopoly_B], then by drawing the
// polygons on top. This places the following constraints on text colors:
// 1) Colors 0 or 1 can't be used, because those don't include any of the bits
//    that can stay constant between frames.
// 2) The hardware palette colors should be identical regardless of the state
//    of the lowest bit to make the text show up on top of the polygons. That
//    is, if a color is 5 *or* 6, hardware colors 5 *and* 6 should be
//    identical. (TH04 and TH05 rely on this.)
// 3) TH02, TH03, and TH04 populate [nopoly_B] *after* they've blitted the
//    constant tracklist, thereby including all of the text pixels in the B
//    plane. TH02 and TH03 also update [nopoly_B] with the B plane from VRAM
//    every time they blit a new comment. This allows the tracklist (TH04)
//    and/or comment colors (TH02/TH03/TH04) to simply be odd, even if 2) would
//    not apply. In that case, that lowest/least significant bit will always be
//    set when blitting back [nopoly_B], and the polygons can't affect it.
//    Together with the other constant color bits, the text then appears on top
//    of the polygons, and in the defined color. (TH02 and TH03 rely on this.)

static const vc_t COL_TRACKLIST_SELECTED = ((GAME >= 4) ? 3 : V_WHITE);
static const vc_t COL_TRACKLIST          = ((GAME >= 4) ? 5 : 3);
static const vc_t COL_CMT_TRACK          = ((GAME >= 4) ? 7 : V_WHITE);
static const vc_t COL_CMT_COMMENT        = ((GAME >= 4) ? 7 : 13);
// ------

// Coordinates
// -----------

static const screen_x_t TRACKLIST_LEFT = ((GAME == 5) ? 12 : 16);
#if (GAME == 5)
	static const int TRACKLIST_VISIBLE_COUNT = 12;

	static const screen_y_t TRACKLIST_TOP = 96;
	static const pixel_t TRACKLIST_H = (TRACKLIST_VISIBLE_COUNT * GLYPH_H);

	static const screen_y_t LABEL_GAME_TOP = 32;
	static const screen_y_t LABEL_UP_TOP = (TRACKLIST_TOP - GLYPH_H);
	static const screen_y_t LABEL_DOWN_TOP = (TRACKLIST_TOP + TRACKLIST_H);
#else
	inline screen_y_t track_top(uint8_t sel) {
		#if (GAME == 4)
			return (8 + (sel * GLYPH_H));
		#elif (GAME == 3)
			return (40 + (sel * GLYPH_H));
		#elif (GAME == 2)
			return ((static_cast<tram_y_t>(sel) + 6) * GLYPH_H);
		#endif
	}

	inline int16_t track_fx(vc_t col) {
		if(GAME >= 4) {
			return col;
		} else {
			return (col | FX_WEIGHT_BOLD);
		}
	}
#endif

static const pixel_t CMT_LINE_W = (CMT_LINE_LENGTH * GLYPH_HALF_W);
static const vram_byte_amount_t CMT_LINE_VRAM_W = (CMT_LINE_W / BYTE_DOTS);
static const pixel_t CMT_COMMENT_H = (CMT_COMMENT_LINES * GLYPH_H);

static const screen_x_t CMT_TITLE_LEFT = (
	/**/ (GAME >= 3)  ? (RES_X - GLYPH_FULL_W - CMT_LINE_W) :
	/*   (GAME == 2) */ ((RES_X / 2) - (CMT_LINE_W / 2))
);
static const screen_y_t CMT_TITLE_TOP = ((GAME == 5) ? 32 : 64);
static const screen_x_t CMT_TITLE_RIGHT = (CMT_TITLE_LEFT + CMT_LINE_W);
static const screen_y_t CMT_TITLE_BOTTOM = (CMT_TITLE_TOP + GLYPH_H);

static const screen_x_t CMT_COMMENT_LEFT = (RES_X - GLYPH_FULL_W - CMT_LINE_W);
#if (GAME == 5)
	static const screen_y_t CMT_COMMENT_TOP = (PIANO_BOTTOM + 8);
#else
	static const screen_y_t CMT_COMMENT_TOP = CMT_TITLE_BOTTOM;
#endif
static const screen_x_t CMT_COMMENT_RIGHT = (CMT_COMMENT_LEFT + CMT_LINE_W);
static const screen_x_t CMT_COMMENT_BOTTOM = (CMT_COMMENT_TOP + CMT_COMMENT_H);
// -----------

// ZUN bloat
#if (GAME == 5)
	static int8_t unused[104];
#elif (GAME == 4)
	static int8_t unused[56];
#endif

// Polygon state
// -------------

struct polygon_point_t {
	pixel_t x;
	Subpixel y;
};

static const unsigned int POLYGON_COUNT = 16;

// ZUN quirk: This has to be intentional.
static const unsigned int POLYGONS_RENDERED = (
	(GAME == 5) ? (POLYGON_COUNT - 2) : POLYGON_COUNT
);

bool polygons_initialized = false;

// ZUN bloat: Could have been local to polygons_update_and_render().
static screen_point_t points[10];

static polygon_point_t center[POLYGON_COUNT];
static polygon_point_t velocity[POLYGON_COUNT];
static unsigned char angle[POLYGON_COUNT];
static unsigned char angle_speed[POLYGON_COUNT];
// -------------

// Selection state
// ---------------

#if (GAME <= 4)
	uint8_t track_playing = 0;
#endif
uint8_t music_sel;
page_t music_page;
#if (GAME >= 4)
	// The initial comment is displayed immediately, without a fade-in
	// animation.
	bool cmt_shown_initial;
	static int8_t unused_byte; // ZUN bloat
#endif
// ---------------

// Backgrounds
// -----------

// B plane of the background image as loaded from the .PI file, without any
// polygons drawn on top of it.
#if (GAME >= 3)
	dots8_t __seg* nopoly_B;
#else
	dots8_t* nopoly_B;
#endif

// ZUN bloat: Unused in TH04 and TH05 which use the bgimage system for that,
// but still present in the binary.
Planar<dots8_t far *> cmt_bg;
// -----------

struct cmt_line_t {
	shiftjis_t c[CMT_LINE_SIZE];
};
cmt_line_t cmt[CMT_LINES];

#if (GAME == 5)
	// TH05 selection state
	// --------------------

	int track_id_at_top;
	int track_playing;
	int track_count_cur;
	// --------------------

	void pascal near track_unput_or_put(uint8_t track_sel, bool16 put)
	{
		enum {
			CURSOR_LEFT = TRACKLIST_LEFT,
			CURSOR_RIGHT = (CURSOR_LEFT + TRACKLIST_W),
			CURSOR_TOP = TRACKLIST_TOP,
			CURSOR_BOTTOM = (TRACKLIST_TOP + GLYPH_H - 1),
		};

		const shiftjis_t* choice;
		vc_t col = COL_TRACKLIST;

		// ZUN bloat: The code could have been a lot simpler if [TRACKLIST_TOP]
		// was added here rather than just before graph_putsa_fx(). Then, [top]
		// could have been a `screen_y_t`.
		pixel_t top = ((track_sel - track_id_at_top) * GLYPH_H);
		if((top < 0) || (top >= TRACKLIST_H)) {
			return;
		}
		if(put) {
			grcg_setcolor(GC_RMW, COL_TRACKLIST);
			grcg_hline(CURSOR_LEFT, CURSOR_RIGHT, (CURSOR_TOP + top));
			grcg_hline(CURSOR_LEFT, CURSOR_RIGHT, (CURSOR_BOTTOM + top));
			grcg_vline(CURSOR_LEFT, (CURSOR_TOP + top), (CURSOR_BOTTOM + top));
			grcg_vline(CURSOR_RIGHT, (CURSOR_TOP + top), (CURSOR_BOTTOM + top));
			grcg_off();
		} else {
			// ZUN bloat: Blitting [TRACKLIST_W] pixels starting at
			// [TRACKLIST_LEFT] is enough.
			bgimage_put_rect_16(0, (CURSOR_TOP + top), 320, GLYPH_H);
		}
		if(track_sel == track_playing) {
			col = COL_TRACKLIST_SELECTED;
		}

		choice = MUSIC_CHOICES[game_sel][track_sel];
		top += TRACKLIST_TOP;
		graph_putsa_fx(TRACKLIST_LEFT, top, col, choice);
	}

	void pascal near tracklist_put(uint8_t sel)
	{
		for(int i = 0; i < (track_count_cur + 2); i++) {
			track_unput_or_put(i, (i == sel));
		}
		graph_putsa_fx(TRACKLIST_LEFT, LABEL_UP_TOP, COL_TRACKLIST, LABEL_UP);
		graph_putsa_fx(
			TRACKLIST_LEFT, LABEL_DOWN_TOP, COL_TRACKLIST, LABEL_DOWN
		);
		graph_putsa_fx(
			TRACKLIST_LEFT,
			LABEL_GAME_TOP,
			COL_TRACKLIST_SELECTED,
			LABEL_GAME[game_sel]
		);
	}
#else
	void pascal near track_put(uint8_t sel, vc_t col)
	{
		page_t other_page = (1 - music_page);
		graph_accesspage(other_page);
		graph_putsa_fx(
			TRACKLIST_LEFT, track_top(sel), track_fx(col), MUSIC_CHOICES[sel]
		);
		graph_accesspage(music_page);
		graph_putsa_fx(
			TRACKLIST_LEFT, track_top(sel), track_fx(col), MUSIC_CHOICES[sel]
		);
	}

	void pascal near tracklist_put(uint8_t sel)
	{
		int i;
		for(i = 0; i < sizeof(MUSIC_CHOICES) / sizeof(MUSIC_CHOICES[0]); i++) {
			track_put(i, ((i == sel) ? COL_TRACKLIST_SELECTED : COL_TRACKLIST));
		}
	}
#endif

void near nopoly_B_snap(void)
{
	nopoly_B = HMem<dots8_t>::alloc(PLANE_SIZE);
	for(vram_offset_t p = 0; p < PLANE_SIZE; p += int(sizeof(dots32_t))) {
		*reinterpret_cast<dots32_t *>(nopoly_B + p) = VRAM_CHUNK(B, p, 32);
	}
}

void near nopoly_B_free(void)
{
	HMem<dots8_t>::free(nopoly_B);
}

void near nopoly_B_put(void)
{
	#if (GAME >= 3)
		// ZUN bloat: This doesn't even compile to a 32-wide memcpy().
		asm { push ds; }
		_ES = SEG_PLANE_B;
		_AX = FP_SEG(nopoly_B);
		_DS = _AX;
		__memcpy__(MK_FP(_ES, 0), MK_FP(_DS, 0), PLANE_SIZE);
		asm { pop ds; }
	#else
		for(vram_offset_t p = 0; p < PLANE_SIZE; p += int(sizeof(dots32_t))) {
			VRAM_CHUNK(B, p, 32) = (
				*reinterpret_cast<dots32_t *>(nopoly_B + p)
			);
		}
	#endif
}

void pascal near polygon_build(
	screen_point_t near* points,
	screen_x_t center_x,
	space_changing_pixel_t center_y,
	pixel_t radius,
	int point_count,
	unsigned char plus_angle
)
{
	int i;

	// ZUN bloat: center_y.pixel = center_y.sp.to_pixel();
	center_y.sp.v >>= SUBPIXEL_BITS;

	for(i = 0; i < point_count; i++) {
		unsigned char point_angle = (((i << 8) / point_count) + plus_angle);
		#if (GAME >= 3)
			points[i].x = polar_x(center_x, radius, point_angle);
			points[i].y = polar_y(center_y.pixel, radius, point_angle);
		#else
			points[i].x = polar_x_fast(center_x, radius, point_angle);
			points[i].y = polar_y_fast(center_y.pixel, radius, point_angle);
		#endif
	}
	points[i].x = points[0].x;
	points[i].y = points[0].y;
}

#define polygon_init(i, center_y, velocity_x) { \
	center[i].x = (irand() % RES_X); \
	center[i].y.v = center_y; \
	velocity[i].x = velocity_x; \
	if(velocity[i].x == 0) { \
		velocity[i].x = 1; \
	} \
	velocity[i].y.v = (to_sp(2.0f) + TO_SP(irand() & 3)); \
	angle[i] = irand(); \
	angle_speed[i] = (0x04 - (irand() & 0x07)); \
	if(angle_speed[i] == 0x00) { \
		angle_speed[i] = 0x04; \
	} \
}

inline int polygon_vertex_count(int polygon_index) {
	return ((polygon_index / 4) + 3);
}

void near polygons_update_and_render(void)
{
	int i;
	if(!polygons_initialized) {
		for(i = 0; i < POLYGONS_RENDERED; i++) {
			polygon_init(i, (irand() % to_sp(RES_Y)), (4 - (irand() & 7)));
		}

		// ZUN quirk: This is never reset.
		polygons_initialized = true;
	}
	for(i = 0; i < POLYGONS_RENDERED; i++) {
		polygon_build(
			points,
			center[i].x,
			reinterpret_cast<space_changing_pixel_t &>(center[i].y),
			(((i & 3) * 16) + 64),
			polygon_vertex_count(i),
			angle[i]
		);
		center[i].x += velocity[i].x;
		center[i].y.v += velocity[i].y.v;
		angle[i] += angle_speed[i];
		if((center[i].x <= 0) || (center[i].x >= (RES_X - 1))) {
			velocity[i].x *= -1;
		}

		// Enough to cover the maximum possible radius of 96.
		if(center[i].y >= to_sp(RES_Y + 100.0f)) {
			polygon_init(i, to_sp(-100.0f), (8 - (irand() & 15)));
		}

		grcg_polygon_c(points, polygon_vertex_count(i));
	}
}

// ZUN bloat
#if ((GAME == 3) || (GAME == 4))
	#define frame_delay frame_delay_2
#endif

void near music_flip(void)
{
	nopoly_B_put();
	#if (GAME == 5)
		piano_render();
	#endif

	// Draw the polygons via the GRCG by setting all bits in all tile registers
	// but restricting blitting to the B plane. Technically, using the GRCG
	// wouldn't be necessary and is in fact a slower way of regularly writing
	// pixels to just the B plane, but all master.lib polygon drawing functions
	// write to VRAM using `=` (MOV) rather than `|=` (OR), and thus expect the
	// GRCG to be enabled.
	grcg_setcolor((GC_RMW | GC_B), 0xF);
	polygons_update_and_render();
	grcg_off();

	// This is the correct position for a VSync delay. frame_delay() returns
	// immediately after a VSync interrupt and at the beginning of the vertical
	// blanking interval, which is the safest point to flip pages.
	#if (GAME == 5)
		frame_delay(1);
	#endif

	graph_showpage(music_page);
	music_page = (1 - music_page);
	graph_accesspage(music_page);

	// ZUN landmine: Waiting for VSync *after* flipping, however, means that we
	// almost certainly *don't* flip within the vertical blanking interval, but
	// somewhere *within* a frame while the beam is still traveling across the
	// screen. This ensures a tearing line on all but the fastest PC-98
	// systems, with the pixels above always being one frame behind.
	#if (GAME <= 4)
		frame_delay(1);
	#endif
}

#if (GAME <= 3)
	#define cmt_bg_blit_planar(cmt_bg_p, vo, x, dst, dst_p, src, src_p) \
		size_t cmt_bg_p = 0; \
		screen_y_t y; \
		for(y = CMT_TITLE_TOP; y < CMT_TITLE_BOTTOM; y++) { \
			for(x = CMT_TITLE_LEFT; x < CMT_TITLE_RIGHT; x += 32) { \
				vo = vram_offset_shift(x, y); \
				*(dots32_t *)(dst[0] + dst_p) = *(dots32_t *)(src[0] + src_p); \
				*(dots32_t *)(dst[1] + dst_p) = *(dots32_t *)(src[1] + src_p); \
				*(dots32_t *)(dst[2] + dst_p) = *(dots32_t *)(src[2] + src_p); \
				*(dots32_t *)(dst[3] + dst_p) = *(dots32_t *)(src[3] + src_p); \
				cmt_bg_p += sizeof(dots32_t); \
			} \
		} \
		for(y = CMT_COMMENT_TOP; y < CMT_COMMENT_BOTTOM; y++) { \
			for(x = CMT_COMMENT_LEFT; x < CMT_COMMENT_RIGHT; x += 32) { \
				vo = vram_offset_shift(x, y); \
				*(dots32_t *)(dst[0] + dst_p) = *(dots32_t *)(src[0] + src_p); \
				*(dots32_t *)(dst[1] + dst_p) = *(dots32_t *)(src[1] + src_p); \
				*(dots32_t *)(dst[2] + dst_p) = *(dots32_t *)(src[2] + src_p); \
				*(dots32_t *)(dst[3] + dst_p) = *(dots32_t *)(src[3] + src_p); \
				cmt_bg_p += sizeof(dots32_t); \
			} \
		}

	void near cmt_bg_snap(void)
	{
		screen_x_t x;
		vram_offset_t vo;
		for(int i = 0; i < PLANE_COUNT; i++) {
			cmt_bg[i] = HMem<dots8_t>::alloc(
				(GLYPH_H * CMT_LINE_VRAM_W) + (CMT_COMMENT_H * CMT_LINE_VRAM_W)
			);
		}
		cmt_bg_blit_planar(cmt_bg_p, vo, x, cmt_bg, cmt_bg_p, VRAM_PLANE, vo);
	}
#endif

void pascal near cmt_load(int track)
{
	#if (GAME == 5)
		char* FN = "_MUSIC0.TXT";

		FN[6] = ('0' + game_sel);
		file_ropen(FN);
	#elif (GAME == 4)
		file_ropen("_MUSIC.TXT");
	#else
		file_ropen("MUSIC.TXT");
	#endif
	file_seek((track * int(sizeof(cmt))), SEEK_SET);
	file_read(cmt, sizeof(cmt));
	file_close();
	for(int i = 0; i < CMT_LINES; i++) {
		cmt[i].c[CMT_LINE_LENGTH] = '\0';
	}
}

// ZUN bloat: TH05 has the most straightforward version of this code.
#define cmt_put_macro(fx) \
	graph_putsa_fx( \
		CMT_TITLE_LEFT, CMT_TITLE_TOP, (COL_CMT_TRACK | fx), cmt[0].c \
	); \
	for(int line = 1; line < CMT_LINES; line++) { \
		if((GAME >= 4) && (cmt[line].c[0] == ';')) { \
			continue; \
		} \
		graph_putsa_fx( \
			CMT_COMMENT_LEFT, \
			((line + ((CMT_COMMENT_TOP - 1) / GLYPH_H)) * GLYPH_H), \
			(COL_CMT_COMMENT | fx), \
			cmt[line].c \
		); \
	}

#if (GAME >= 4)
	void near cmt_put(void)
	{
		#if (GAME == 5)
			graph_putsa_fx(
				CMT_TITLE_LEFT, CMT_TITLE_TOP, COL_CMT_TRACK, cmt[0].c
			);
			const cmt_line_t near* cmt_p = &cmt[1];
			int line = 1;
			screen_y_t top = CMT_COMMENT_TOP;
			while(line < CMT_LINES) {
				if(cmt_p->c[0] != ';') {
					graph_putsa_fx(
						CMT_COMMENT_LEFT, top, COL_CMT_COMMENT, cmt_p->c
					);
				}
				line++;
				top += GLYPH_H;
				cmt_p++;
			}
		#else
			cmt_put_macro(0);
		#endif
	}

	void near cmt_fadein_both_animate(void)
	{
		int func; // ACTUAL TYPE: graph_putsa_fx_func_t
		for(func = FX_MASK; func < FX_MASK_END; func++) {
			graph_putsa_fx_func = static_cast<graph_putsa_fx_func_t>(func);
			cmt_put();	music_flip();
			cmt_put();	music_flip();
		}
		graph_putsa_fx_func = FX_WEIGHT_BOLD;
		cmt_put();	music_flip();
		cmt_put();
	}

	inline void cmt_unput(void) {
		enum {
			W = (RES_X - CMT_TITLE_LEFT), // ZUN bloat: [CMT_LINE_W] is enough.
		};
		#if (GAME == 5)
			bgimage_put_rect_16(CMT_TITLE_LEFT, CMT_TITLE_TOP, W, GLYPH_H);
			bgimage_put_rect_16(
				CMT_COMMENT_LEFT,
				CMT_COMMENT_TOP,
				W,
				(CMT_COMMENT_LINES * GLYPH_H)
			);
		#else
			bgimage_put_rect_16(
				CMT_TITLE_LEFT, CMT_TITLE_TOP, W, (CMT_LINES * GLYPH_H)
			);
		#endif
	}

	void near cmt_unput_both_animate(void)
	{
		// ZUN bloat: Not related to unblitting.
		graph_putsa_fx_func = FX_WEIGHT_BOLD;

		cmt_unput();
		music_flip();
		cmt_unput();
	}

	void pascal near cmt_load_unput_and_put_both_animate(int track)
	{
		if(cmt_shown_initial) {
			cmt_unput_both_animate();
		}
		cmt_load(track);

		// ZUN bloat: These calls are never needed. Either we're rendering the
		// first track and there's nothing to be unblitted, or we already
		// unblitted the previous track title and comment in the call above.
		// In fact, they have no effect at all, which is why TH05 can put these
		// nonsensical coordinates and ZUN never noticed anything.
		nopoly_B_put();
		bgimage_put_rect_16(
			CMT_TITLE_LEFT,
			((GAME == 5) ? 64 : CMT_TITLE_TOP),
			(RES_X - CMT_TITLE_LEFT),
			((GAME == 5) ? 256 : (CMT_LINES * GLYPH_H))
		);

		if(cmt_shown_initial) {
			cmt_fadein_both_animate();
		} else {
			cmt_shown_initial = true;
			cmt_put();
			music_flip();
			cmt_put();
		}

		// ZUN bloat: Redundant; this is the first thing done in music_flip(),
		// which runs almost immediately after this function on every code
		// path.
		nopoly_B_put();
	}
#else
	void near cmt_bg_free(void)
	{
		HMem<dots8_t>::free(cmt_bg.B);
		HMem<dots8_t>::free(cmt_bg.R);
		HMem<dots8_t>::free(cmt_bg.G);
		HMem<dots8_t>::free(cmt_bg.E);
	}

	void near cmt_unput(void)
	{
		screen_x_t x;
		vram_offset_t vo;
		cmt_bg_blit_planar(cmt_bg_p, vo, x, VRAM_PLANE, vo, cmt_bg, cmt_bg_p);
	}

	void pascal near cmt_load_unput_and_put(int track)
	{
		// ZUN bloat: This function is called once per VRAM page, but we only
		// need to load the track once.
		cmt_load(track);

		nopoly_B_put();
		cmt_unput();
		cmt_put_macro(FX_WEIGHT_HEAVY);

		// Update [nopoly_B] to match the B plane of the comment we just
		// blitted into the respective area. Since this buffer is reblitted
		// every frame, updating it here preserves the lowest bit of the
		// comment text pixels regardless of the polygons rendered on top.
		// This allows comment colors to have any odd value, just like the
		// tracklist colors.
		//
		// ZUN bloat: Same as above – the second call overwrites the previously
		// snapped contents with the exact same pixels from the other page.
		// ZUN bloat: Also, limiting it to just the comment area would have
		// been enough.
		for(vram_offset_t p = 0; p < PLANE_SIZE; p += int(sizeof(dots32_t))) {
			*reinterpret_cast<dots32_t *>(nopoly_B + p) = VRAM_CHUNK(B, p, 32);
		}
	}
#endif

// Input wrappers
// --------------
// The Music Room is the only piece of UI that is more or less the same across
// 4 of the 5 games. Therefore, it makes sense to define these here rather than
// adding more complexity to the headers.

#if (GAME == 3)
	#define key_det input_sp
#endif

// Same game-specific branches as in the TH03/TH04/TH05 cutscene system, but
// with a different, much smaller effect here.
//
// ZUN quirk: After processing an input, the Music Room loop wants to prevent
// held keys from having any effect by spinning in a different loop until all
// keys have been released. However, due to the different sensing functions,
// the actual handling of held keys differs depending on the game:
//
// • TH02 and TH04 use raw input sensing functions that don't address the
//   hardware quirk documented in the `Research/HOLDKEY` example. Therefore,
//   the eventual key release scancode for a held key is not filtered and gets
//   through to [key_det], breaking the spinning loop despite the key still
//   being held.
// • In TH03 and TH05, this eventual key release scancode is accurately
//   detected and filtered. Thus, held keys truly don't have any effect, but at
//   the cost of an additional 614.4 µs for every call to this function.
inline void music_input_sense(void) {
	#if (GAME == 5)
		input_reset_sense_held();
	#elif (GAME == 4)
		input_reset_sense();
	#elif (GAME == 3)
		input_mode_interface();
	#else
		input_reset_sense();
	#endif
}
// --------------

#define wait_for_key_release_animate() { \
	while(1) { \
		music_input_sense(); \
		if(key_det) { \
			music_flip(); \
		} else { \
			break; \
		} \
	} \
}

#if (GAME == 5)
	void pascal near tracklist_unput_and_put_both_animate(int sel)
	{
		bgimage_put_rect_16(0, LABEL_GAME_TOP, CMT_TITLE_LEFT, GLYPH_H);
		bgimage_put_rect_16(0, TRACKLIST_TOP, CMT_TITLE_LEFT, TRACKLIST_H);
		tracklist_put(sel);
		music_flip();
		bgimage_put_rect_16(0, LABEL_GAME_TOP, CMT_TITLE_LEFT, GLYPH_H);
		bgimage_put_rect_16(0, TRACKLIST_TOP, CMT_TITLE_LEFT, TRACKLIST_H);
		tracklist_put(sel);
	}

	inline void track_unput_and_put_both_animate(
		const uint8_t& sel_prev, const uint8_t& sel_new
	) {
		track_unput_or_put(sel_prev, false);
		track_unput_or_put(sel_new, true);
		music_flip();
		track_unput_or_put(sel_prev, false);
		track_unput_or_put(sel_new, true);
	}

	inline void game_switch(void) {
		music_sel = 0;
		track_playing = 0;
		track_id_at_top = 0;
		track_count_cur = TRACK_COUNT[game_sel];
		tracklist_unput_and_put_both_animate(0);
		snd_kaja_func(KAJA_SONG_FADE, 32);
		cmt_load_unput_and_put_both_animate(0);
		snd_load(MUSIC_FILES[game_sel][0], SND_LOAD_SONG);
		snd_kaja_func(KAJA_SONG_PLAY, 0);
	}
#endif

void MUSICROOM_DISTANCE musicroom_menu(void)
{
	#if (GAME == 5)
		int frames_since_last_input = 0;
		uint8_t sel_prev;
		track_id_at_top = 0;
		track_playing = 0;
		music_sel = 0;
		track_count_cur = TRACK_COUNT[game_sel];
		#define SEL_QUIT track_count_cur
	#else
		enum {
			SEL_QUIT = (TRACK_COUNT + 1),
		};
	#endif

	#if (GAME >= 4)
		cmt_shown_initial = false;
	#endif

	// ZUN bloat: The call site would have been a better place for this.
	#if (GAME >= 4)
		cdg_free_all();
		text_clear();
	#elif (GAME == 3)
		for(int i = 0; i < CDG_SLOT_COUNT; i++) {
			cdg_free(i);
		}
		super_free();
		text_clear();
	#endif

	music_page = 1;

	palette_black();
	graph_showpage(0);

	// ZUN bloat: We copy page 1 to page 0 below anyway. The hardware palette
	// is also entirely black, so no one will ever see a difference.
	graph_accesspage(0);
	graph_clear();

	graph_accesspage(1);

	#if (GAME >= 4)
		pi_fullres_load_palette_apply_put_free(0, "music.pi");
	#else
		pi_fullres_load_palette_apply_put_free(0, "op3.pi");
	#endif

	#if (GAME == 5)
		piano_setup_and_put_initial();
		nopoly_B_snap();
		bgimage_snap();
	#else
		music_sel = track_playing;
	#endif
	tracklist_put(music_sel);
	graph_copy_page(0);

	#if (GAME == 4)
		bgimage_snap();
	#endif
	graph_accesspage(1);
	graph_showpage(0);

	#if (GAME == 5)
		pfend();
		pfstart("music.dat");
		cmt_load_unput_and_put_both_animate(music_sel);
	#else
		nopoly_B_snap();
		#if (GAME >= 4)
			cmt_load_unput_and_put_both_animate(track_playing);
		#else
			cmt_bg_snap();
			graph_accesspage(1);	cmt_load_unput_and_put(track_playing);
			graph_accesspage(0);	cmt_load_unput_and_put(track_playing);
		#endif
	#endif

	palette_100();

	while(1) {
		#if (GAME == 5)
			// This loop also ignores any ← or → inputs while ↑ or ↓ are held,
			// and vice versa.
			while(1) {
				music_input_sense();
				if(!key_det) {
					break;
				}
				if(frames_since_last_input >= 24) {
					if((key_det == INPUT_UP) || (key_det == INPUT_DOWN)) {
						frames_since_last_input = 20;
						break;
					}
				}
				frames_since_last_input++;
				music_flip();
			}
		#else
			// ZUN bloat: None of this `goto` business would have been
			// necessary if the loop clearly defined its update and render
			// steps. Especially since it does want to render the polygon
			// animation every frame.
			wait_for_key_release_animate();
		#endif
controls:
		// ZUN bloat: We already did that for this frame if we came from above,
		// but not if we came from the `goto` below.
		music_input_sense();

		#if (GAME == 5)
			if(key_det & INPUT_UP) {
				sel_prev = music_sel;
				if(music_sel > 0) {
					music_sel--;
					if(music_sel < track_id_at_top) {
						track_id_at_top = music_sel;
						tracklist_unput_and_put_both_animate(music_sel);

						// ZUN quirk: This prevents game switches via ← or → ,
						// but only in the very specific case of
						// 1) the cursor being at the top of the list,
						// 2) highlighting a track other than the first one of
						//    the respective game, and
						// 3) ←/→ being pressed simultaneously with ↑.
						// In any other case, ←/→ are processed as expected,
						// and override this cursor movement with a game
						// switch.
						goto skip_processing_of_left_and_right;
					} else {
						track_unput_and_put_both_animate(sel_prev, music_sel);
					}
				} else {
					music_sel = SEL_QUIT;
					track_id_at_top = (
						SEL_QUIT - (TRACKLIST_VISIBLE_COUNT - 1)
					);
					tracklist_unput_and_put_both_animate(SEL_QUIT);
				}
			}
			if(key_det & INPUT_DOWN) {
				sel_prev = music_sel;
				if(music_sel < SEL_QUIT) {
					music_sel++;
					if(
						music_sel >=
						(track_id_at_top + TRACKLIST_VISIBLE_COUNT)
					) {
						track_id_at_top = (
							music_sel - (TRACKLIST_VISIBLE_COUNT - 1)
						);
						tracklist_unput_and_put_both_animate(music_sel);

						// Same as the quirk above, applying to the
						// corresponding very specific case of
						// 1) the cursor being at the bottom of the list,
						// 2) highlighting anything except [SEL_QUIT], and
						// 3) ←/→ being pressed simultaneously with ↓.
						goto skip_processing_of_left_and_right;
					} else {
						track_unput_and_put_both_animate(sel_prev, music_sel);
					}
				} else {
					music_sel = 0;
					track_id_at_top = 0;
					tracklist_unput_and_put_both_animate(music_sel);
				}
			}
			if(key_det & INPUT_LEFT) {
				ring_dec(game_sel, (GAME_COUNT - 1));
				game_switch();
			} else if(key_det & INPUT_RIGHT) {
				ring_inc_ge(game_sel, GAME_COUNT);
				game_switch();
			}
		#else
			if(key_det & INPUT_UP) {
				track_put(music_sel, COL_TRACKLIST);
				if(music_sel > 0) {
					music_sel--;
				} else {
					music_sel = SEL_QUIT;
				}

				// Skip over the empty line
				if(music_sel == TRACK_COUNT) {
					music_sel--;
				}

				track_put(music_sel, COL_TRACKLIST_SELECTED);
			}
			if(key_det & INPUT_DOWN) {
				track_put(music_sel, COL_TRACKLIST);
				if(music_sel < SEL_QUIT) {
					music_sel++;
				} else {
					music_sel = 0;
				}

				// Skip over the empty line
				if(music_sel == TRACK_COUNT) {
					music_sel++;
				}

				track_put(music_sel, COL_TRACKLIST_SELECTED);
			}
		#endif
	skip_processing_of_left_and_right:
		if(key_det & INPUT_SHOT || key_det & INPUT_OK) {
			if(music_sel != SEL_QUIT) {
				#if (GAME >= 4)
					snd_kaja_func(KAJA_SONG_FADE, 32);
				#elif (GAME == 3)
					// Avoids the snd_load() landmine that is still present in
					// this game.
					snd_kaja_func(KAJA_SONG_STOP, 0);
				#elif (GAME == 2)
					// ZUN landmine: Should have stopped the currently playing
					// track according to snd_load()'s header comment.
					// Especially since this game simultaneously loads both the
					// PMD and MIDI versions and is therefore inherently slower
					// than the others.
				#endif

				#if (GAME == 5)
					sel_prev = track_playing;
					track_playing = music_sel;
					track_unput_and_put_both_animate(sel_prev, music_sel);
					cmt_load_unput_and_put_both_animate(music_sel);
					snd_load(MUSIC_FILES[game_sel][music_sel], SND_LOAD_SONG);
					snd_kaja_func(KAJA_SONG_PLAY, 0);
				#elif (GAME == 4)
					track_playing = music_sel;
					cmt_load_unput_and_put_both_animate(music_sel);
					snd_load(MUSIC_FILES[music_sel], SND_LOAD_SONG);
					snd_kaja_func(KAJA_SONG_PLAY, 0);
				#else
					#if (GAME == 3)
						snd_load(MUSIC_FILES[music_sel], SND_LOAD_SONG);
					#else
						// Load both the MIDI and PMD versions of the selected
						// track. Makes sense given that the track continues
						// playing when leaving the Music Room – changing the
						// music mode in the Option menu will then play the
						// same selected track.
						bool midi_active = snd_midi_active;
						snd_midi_active = snd_midi_possible;
						snd_load(MUSIC_FILES[music_sel], SND_LOAD_SONG);
						snd_midi_active = 0;
						snd_load(MUSIC_FILES[music_sel], SND_LOAD_SONG);
						snd_midi_active = midi_active;
					#endif
					snd_kaja_func(KAJA_SONG_PLAY, 0);
					track_playing = music_sel;
					cmt_load_unput_and_put(music_sel);
					music_flip();
					cmt_load_unput_and_put(music_sel);
				#endif
			} else {
				break;
			}
		}
		if(key_det & INPUT_CANCEL) {
			break;
		}
		if(!key_det) {
			#if (GAME == 5)
				frames_since_last_input = 0;
			#endif
			music_flip();
			goto controls;
		}
	};
	wait_for_key_release_animate();

	#if (GAME >= 4)
		#if (GAME == 5)
			pfend();
			pfstart(OP_AND_END_PF_FN);
		#endif
		snd_kaja_func(KAJA_SONG_FADE, 16);
		nopoly_B_free();
		graph_showpage(0);
		graph_accesspage(0);
		palette_black_out(1);
		bgimage_free();
		snd_load(BGM_MENU_MAIN_FN, SND_LOAD_SONG);
		snd_kaja_func(KAJA_SONG_PLAY, 0);
	#else
		nopoly_B_free();
		cmt_bg_free();
		graph_showpage(0);

		// ZUN quirk: graph_clear() sets all of VRAM to hardware color #0,
		// which is purple in the original images, not black.
		//
		// ZUN bloat: Unlike the graph_clear() call at the beginning of the
		// function, this one is not useless because we haven't reset the
		// hardware palette yet. Still, setting all hardware colors to color #0
		// would have been a more efficient way to accomplish the same hiding
		// effect before the graph_copy_page() call below.
		graph_accesspage(0);
		graph_clear();

		graph_accesspage(1);

		#if (GAME == 2)
			// ZUN bloat: The call site would have been a better place for this.
			pi_fullres_load_palette_apply_put_free(0, "op2.pi");
			palette_entry_rgb_show("op.rgb");
			graph_copy_page(0);
		#endif

		graph_accesspage(0);
	#endif
}

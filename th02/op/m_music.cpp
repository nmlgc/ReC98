#include <mem.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "master.hpp"
#include "game/coords.hpp"
#include "th02/v_colors.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/formats/musiccmt.hpp"
#if (GAME >= 3)
	#include "th03/math/polar.hpp"
#else
	#include "th01/math/polar.hpp"
#endif
extern "C" {
#if (GAME >= 4)
	#include "th04/hardware/bgimage.hpp"
	#include "th04/hardware/grppsafx.h"
#else
	#include "th01/hardware/grppsafx.h"
#endif
}
#if (GAME == 5)
	#include "th05/op/piano.hpp"
	#include "th05/shiftjis/music.hpp"

	int game_sel = (GAME_COUNT - 1);
	extern const int TRACK_COUNT[GAME_COUNT] = { 14, 18, 24, 28, 23 };
#else
	#if (GAME == 4)
		#include "th04/shiftjis/music.hpp"
	#elif (GAME == 3)
		#include "th03/shiftjis/music.hpp"
	#elif (GAME == 2)
		#include "th02/shiftjis/music.hpp"
	#endif
#endif

// Colors
// ------

static const vc_t COL_TRACKLIST_SELECTED = ((GAME >= 4) ? 3 : V_WHITE);
static const vc_t COL_TRACKLIST          = ((GAME >= 4) ? 5 : 3);
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
static const screen_y_t CMT_TITLE_TOP = 64;
static const screen_x_t CMT_TITLE_RIGHT = (CMT_TITLE_LEFT + CMT_LINE_W);
static const screen_y_t CMT_TITLE_BOTTOM = (CMT_TITLE_TOP + GLYPH_H);

static const screen_x_t CMT_COMMENT_LEFT = (RES_X - GLYPH_FULL_W - CMT_LINE_W);
static const screen_y_t CMT_COMMENT_TOP = CMT_TITLE_BOTTOM;
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
// ---------------

// Backgrounds
// -----------

// B plane of the background image as loaded from the .PI file, without any
// polygons drawn on top of it.
#if (GAME >= 3)
	extern dots8_t __seg* nopoly_B;
#else
	extern dots8_t* nopoly_B;
#endif
#define cmt_bg cmt_back
extern Planar<dots8_t far *> cmt_bg;
// -----------

#define cmt music_cmt
struct cmt_line_t {
	shiftjis_t c[CMT_LINE_SIZE];
};
extern cmt_line_t cmt[CMT_LINES];

#if (GAME == 5)
	// TH05 selection state
	// --------------------

	extern int track_id_at_top;
	extern int track_playing;
	extern int track_count_cur;
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
	center[i].x = (rand() % RES_X); \
	center[i].y.v = center_y; \
	velocity[i].x = velocity_x; \
	if(velocity[i].x == 0) { \
		velocity[i].x = 1; \
	} \
	velocity[i].y.v = (to_sp(2.0f) + TO_SP(rand() & 3)); \
	angle[i] = rand(); \
	angle_speed[i] = (0x04 - (rand() & 0x07)); \
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
			polygon_init(i, (rand() % to_sp(RES_Y)), (4 - (rand() & 7)));
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
			polygon_init(i, to_sp(-100.0f), (8 - (rand() & 15)));
		}

		grcg_polygon_c(points, polygon_vertex_count(i));
	}
}

// ZUN bloat
#if ((GAME == 3) || (GAME == 4))
	#define frame_delay frame_delay_2
#endif
#if (GAME <= 3)
	#undef grcg_off
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
		file_ropen("_MUSIC.TXT\0music.pi");
	#elif (GAME == 3)
		file_ropen(reinterpret_cast<const char *>(MK_FP(_DS, 0x09D1)));
	#elif (GAME == 2)
		file_ropen(reinterpret_cast<const char *>(MK_FP(_DS, 0x0C13)));
	#endif
	file_seek((track * int(sizeof(cmt))), SEEK_SET);
	file_read(cmt, sizeof(cmt));
	file_close();
	for(int i = 0; i < CMT_LINES; i++) {
		cmt[i].c[CMT_LINE_LENGTH] = '\0';
	}
}

/* ReC98
 * -----
 * Code segment #6 of TH02's OP.EXE
 */

#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "libs/kaja/kaja.h"
#include "th01/math/polar.hpp"
extern "C" {
#include "th01/hardware/grppsafx.h"
#include "th02/v_colors.hpp"
#include "th02/math/vector.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"
#include "th02/formats/pi.h"
#include "th02/snd/snd.h"
#include "th02/shiftjis/fns.hpp"

static const int MUSIC_CMT_LINE_LEN = 42;
static const int MUSIC_CMT_LINE_COUNT = 20;

#define TRACK_COUNT sizeof(MUSIC_FILES) / sizeof(MUSIC_FILES[0])
#define SEL_QUIT TRACK_COUNT + 1

#define MUSIC_POLYGONS 16

const shiftjis_t *MUSIC_TITLES[] = {
	"NO.1    東方封魔録　～浄土曼荼羅",
	"NO.2    　 博麗　～Eastern Wind ",
	"NO.3    　   End of Daylight　  ",
	"NO.4    　　　　　幻夢界　　　　",
	"NO.5    ひもろぎ、むらさきにもえ",
	"NO.6    　東方封魔録　～幽幻乱舞",
	"NO.7    　  She's in a temper!! ",
	"NO.8    　  　 やみのちから　　 ",
	"NO.9    　　　　死を賭して　　　",
	"NO.10    　  　 恋色マジック 　 ",
	"NO.11       Complete Darkness   ",
	"NO.12        　　遠野の森　　　 ",
	"NO.13       昔話わんだーらんど  ",
	"NO.14      　 エキストララブ    ",
	"NO.15      戦車むすめのみるゆめ ",
	"           　　                 ",
	"           　　Ｑｕｉｔ         "
};

const char *MUSIC_FILES[] = {
	"op.m",
	"stage0.m",
	"stage1.m",
	"stage2.m",
	"stage3.m",
	"stage4.m",
	"boss1.m",
	"boss4.m",
	"boss2.m",
	"boss3.m",
	"mima.m",
	"end1.m",
	"ending.m",
	"stage5.m",
	"boss5.m"
};

// Polygon state
char initialized = 0;
screen_point_t points[10];
screen_point_t pos[MUSIC_POLYGONS];
point_t move_speed[MUSIC_POLYGONS];
char angle[MUSIC_POLYGONS];
char rot_speed[MUSIC_POLYGONS];

unsigned char music_sel;
page_t music_page;
dots8_t *screen_back_B;
Planar<dots8_t far *> cmt_back;

void pascal near draw_track(unsigned char sel, unsigned char color)
{
	page_t other_page = (1 - music_page);
	graph_accesspage(other_page);
	graph_putsa_fx(
		16, ((sel + 6) * GLYPH_H), (color | FX_WEIGHT_BOLD), MUSIC_TITLES[sel]
	);
	graph_accesspage(music_page);
	graph_putsa_fx(
		16, ((sel + 6) * GLYPH_H), (color | FX_WEIGHT_BOLD), MUSIC_TITLES[sel]
	);
}

void pascal near draw_tracks(unsigned char sel)
{
	int i;
	for(i = 0; i < sizeof(MUSIC_TITLES) / sizeof(MUSIC_TITLES[0]); i++) {
		draw_track(i, (i == sel) ? V_WHITE : 3);
	}
}

void pascal near screen_back_B_snap(void)
{
	screen_back_B = HMem<dots8_t>::alloc(PLANE_SIZE);
	plane_dword_blit(screen_back_B, VRAM_PLANE_B);
}

void pascal near screen_back_B_free(void)
{
	HMem<dots8_t>::free(screen_back_B);
}

void pascal near screen_back_B_put(void)
{
	plane_dword_blit(VRAM_PLANE_B, screen_back_B);
}

void pascal near polygon_build(
	screen_point_t near *pts,
	screen_x_t x,
	screen_y_t y,
	int rad,
	int npoint,
	char angle
)
{
	int i;
	y >>= 4;
	for(i = 0; i < npoint; i++) {
		unsigned char point_angle = ((i << 8) / npoint) + angle;
		pts[i].x = polar_x_fast(x, rad, point_angle);
		pts[i].y = polar_y_fast(y, rad, point_angle);
	}
	pts[i].x = pts[0].x;
	pts[i].y = pts[0].y;
}

#define polygon_init(i, y_, velocity_x) { \
	pos[i].x = (rand() % RES_X); \
	pos[i].y = y_; \
	move_speed[i].x = velocity_x; \
	if(move_speed[i].x == 0) { \
		move_speed[i].x = 1; \
	} \
	move_speed[i].y = (((rand() & 3) << 4) + 32); \
	angle[i] = rand(); \
	rot_speed[i] = 0x04 - (rand() & 0x07); \
	if(rot_speed[i] == 0x00) { \
		rot_speed[i] = 0x04; \
	} \
}

inline int polygon_vertex_count(int i) {
	return ((i / 4) + 3);
}

void pascal near polygons_update_and_render(void)
{
	int i;
	if(!initialized) {
		for(i = 0; i < MUSIC_POLYGONS; i++) {
			polygon_init(i, (rand() % (RES_Y * 16)), (4 - (rand() & 7)));
		}
		initialized = 1;
	}
	for(i = 0; i < MUSIC_POLYGONS; i++) {
		polygon_build(
			points, pos[i].x, pos[i].y,
			(((i & 3) << 4) + 64), polygon_vertex_count(i), angle[i]
		);
		pos[i].x += move_speed[i].x;
		pos[i].y += move_speed[i].y;
		angle[i] += rot_speed[i];
		if(pos[i].x <= 0 || pos[i].x >= 639) {
			move_speed[i].x *= -1;
		}
		if(pos[i].y >= (RES_Y * 20)) {
			polygon_init(i, -(RES_Y * 4), (8 - (rand() & 15)));
		}
		grcg_polygon_c(
			reinterpret_cast<Point *>(points), polygon_vertex_count(i)
		);
	}
}

void pascal near music_flip(void)
{
	screen_back_B_put();
	grcg_setcolor((GC_RMW | GC_B), V_WHITE);
	polygons_update_and_render();
	grcg_off();
	graph_showpage(music_page);
	music_page = 1 - music_page;
	graph_accesspage(music_page);
	frame_delay(1);
}

#define cmt_bg_put_planar(cmt_bg_p, vo, x, dst, dst_p, src, src_p) \
	size_t cmt_bg_p = 0; \
	screen_y_t y; \
	for(y = 64; y < 80; y++) { \
		for(x = 160; x < 480; x += (4 * BYTE_DOTS)) { \
			vo = vram_offset_shift(x, y); \
			*(long*)(dst[PL_B] + dst_p) = *(long*)(src[PL_B] + src_p); \
			*(long*)(dst[PL_R] + dst_p) = *(long*)(src[PL_R] + src_p); \
			*(long*)(dst[PL_G] + dst_p) = *(long*)(src[PL_G] + src_p); \
			*(long*)(dst[PL_E] + dst_p) = *(long*)(src[PL_E] + src_p); \
			cmt_bg_p += 4; \
		} \
	} \
	for(y = 80; y < 384; y++) { \
		for(x = 304; x < 624; x += (4 * BYTE_DOTS)) { \
			vo = vram_offset_shift(x, y); \
			*(long*)(dst[PL_B] + dst_p) = *(long*)(src[PL_B] + src_p); \
			*(long*)(dst[PL_R] + dst_p) = *(long*)(src[PL_R] + src_p); \
			*(long*)(dst[PL_G] + dst_p) = *(long*)(src[PL_G] + src_p); \
			*(long*)(dst[PL_E] + dst_p) = *(long*)(src[PL_E] + src_p); \
			cmt_bg_p += 4; \
		} \
	}

void pascal near cmt_back_snap(void)
{
	screen_x_t x;
	vram_offset_t vo;
	for(int i = 0; i < PLANE_COUNT; i++) {
		cmt_back[i] = HMem<dots8_t>::alloc(
			(304 * (320 / BYTE_DOTS)) + (16 * (320 / BYTE_DOTS))
		);
	}
	cmt_bg_put_planar(cmt_bg_p, vo, x, cmt_back, cmt_bg_p, VRAM_PLANE, vo);
}

#include "th02/op/cmt_load.c"

void pascal near cmt_back_free(void)
{
	HMem<dots8_t>::free(cmt_back.B);
	HMem<dots8_t>::free(cmt_back.R);
	HMem<dots8_t>::free(cmt_back.G);
	HMem<dots8_t>::free(cmt_back.E);
}

void pascal near cmt_back_put(void)
{
	screen_x_t x;
	vram_offset_t vo;
	cmt_bg_put_planar(cmt_bg_p, vo, x, VRAM_PLANE, vo, cmt_back, cmt_bg_p);
}

void pascal near draw_cmt(int track)
{
	int line;
	music_cmt_load(track);
	screen_back_B_put();
	cmt_back_put();

	graph_putsa_fx(160, 64, (V_WHITE | FX_WEIGHT_HEAVY), music_cmt[0]);
	for(line = 1; line < MUSIC_CMT_LINE_COUNT; line++) {
		graph_putsa_fx(
			304, ((line + 4) * GLYPH_H), (13 | FX_WEIGHT_HEAVY), music_cmt[line]
		);
	}
	plane_dword_blit(screen_back_B, VRAM_PLANE_B);
}

void pascal musicroom(void)
{
	static unsigned char track_playing = 0;
	music_page = 1;

	palette_black();

	graph_showpage(0);
	graph_accesspage(0);
	graph_clear();
	graph_accesspage(1);

	pi_load_put_8_free(0, "op3.pi");
	music_sel = track_playing;
	draw_tracks(music_sel);
	graph_copy_page(0);

	graph_accesspage(1);
	graph_showpage(0);
	screen_back_B_snap();
	cmt_back_snap();

	graph_accesspage(1);	draw_cmt(track_playing);
	graph_accesspage(0);	draw_cmt(track_playing);

	palette_100();

	do {
		input_sense();
		if(key_det) {
			music_flip();
			continue;
		}
controls:
		input_sense();
		if(key_det & INPUT_UP) {
			draw_track(music_sel, 3);
			if(music_sel > 0) {
				music_sel--;
			} else {
				music_sel = SEL_QUIT;
			}
			if(music_sel == TRACK_COUNT) {
				music_sel--;
			}
			draw_track(music_sel, V_WHITE);
		}
		if(key_det & INPUT_DOWN) {
			draw_track(music_sel, 3);
			if(music_sel < SEL_QUIT) {
				music_sel++;
			} else {
				music_sel = 0;
			}
			if(music_sel == TRACK_COUNT) {
				music_sel++;
			}
			draw_track(music_sel, V_WHITE);
		}
		if(key_det & INPUT_SHOT || key_det & INPUT_OK) {
			if(music_sel != SEL_QUIT) {
				bool midi_active = snd_midi_active;

				snd_midi_active = snd_midi_possible;
				snd_load(MUSIC_FILES[music_sel], SND_LOAD_SONG);
				snd_midi_active = 0;
				snd_load(MUSIC_FILES[music_sel], SND_LOAD_SONG);
				snd_midi_active = midi_active;
				snd_kaja_func(KAJA_SONG_PLAY, 0);
				track_playing = music_sel;

				draw_cmt(music_sel);
				music_flip();
				draw_cmt(music_sel);
			} else {
				break;
			}
		}
		if(key_det & INPUT_CANCEL) {
			break;
		}
		if(!key_det) {
			music_flip();
			goto controls;
		}
	} while(1);
	while(1) {
		input_sense();
		if(key_det) {
			music_flip();
		} else {
			break;
		}
	};
	screen_back_B_free();
	cmt_back_free();
	graph_showpage(0);
	graph_accesspage(0);
	graph_clear();
	graph_accesspage(1);
	pi_load_put_8_free(0, "op2.pi");
	palette_entry_rgb_show("op.rgb");
	graph_copy_page(0);
	graph_accesspage(0);
}

}

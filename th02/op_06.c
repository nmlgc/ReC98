/* ReC98
 * -----
 * Code segment #6 of TH02's OP.EXE
 */

#include "th02\th02.h"
#include "th02/formats/pi.h"

#define TRACK_COUNT sizeof(MUSIC_FILES) / sizeof(MUSIC_FILES[0])
#define SEL_QUIT TRACK_COUNT + 1

#define MUSIC_POLYGONS 16

const char *MUSIC_TITLES[] = {
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

unsigned char music_sel;
unsigned char music_page;
char *screen_back_B;
char *cmt_back[PL_COUNT];

void pascal near draw_track(unsigned char sel, unsigned char color)
{
	unsigned char other_page = 1 - music_page;
	graph_accesspage(other_page);
	graph_putsa_fx(16, (sel + 6) * 16, FX(color, 2, 0), MUSIC_TITLES[sel]);
	graph_accesspage(music_page);
	graph_putsa_fx(16, (sel + 6) * 16, FX(color, 2, 0), MUSIC_TITLES[sel]);
}

void pascal near draw_tracks(unsigned char sel)
{
	int i;
	for(i = 0; i < sizeof(MUSIC_TITLES) / sizeof(MUSIC_TITLES[0]); i++) {
		draw_track(i, i == sel ? 15 : 3);
	}
}

void pascal near screen_back_B_snap(void)
{
	int p;
	screen_back_B = MK_FP(hmem_allocbyte(PLANE_SIZE), 0);
	PLANE_DWORD_BLIT(screen_back_B, VRAM_PLANE_B);
}

void pascal near screen_back_B_free(void)
{
	hmem_free(FP_SEG(screen_back_B));
}

void pascal near screen_back_B_put(void)
{
	int p;
	PLANE_DWORD_BLIT(VRAM_PLANE_B, screen_back_B);
}

void pascal near polygon_build(Point near *pts, int x, int y, int rad, int npoint, char angle)
{
	int i;
	y >>= 4;
	for(i = 0; i < npoint; i++) {
		unsigned char point_angle = ((i << 8) / npoint) + angle;
		pts[i].x = ((rad * (long)CosTable8[point_angle]) >> 8) + x;
		pts[i].y = ((rad * (long)SinTable8[point_angle]) >> 8) + y;
	}
	pts[i].x = pts[0].x;
	pts[i].y = pts[0].y;
}

void pascal near polygons_update_and_render(void)
{
	#define VERTICES(i) (i / 4) + 3

	#define POLYGON_INIT_PART2 \
		if(move_speed[i].x == 0) { \
			move_speed[i].x = 1; \
		} \
		move_speed[i].y = ((rand() & 3) << 4) + 32; \
		angle[i] = rand(); \
		rot_speed[i] = 4 - (rand() & 7); \
		if(rot_speed[i] == 0) { \
			rot_speed[i] = 4; \
		}

	static char initialized = 0;

	static Point points[10];
	static Point pos[MUSIC_POLYGONS];
	static Point move_speed[MUSIC_POLYGONS];
	static char angle[MUSIC_POLYGONS];
	static char rot_speed[MUSIC_POLYGONS];

	int i;
	if(!initialized) {
		for(i = 0; i < MUSIC_POLYGONS; i++) {
			pos[i].x = rand() % 640;
			pos[i].y = rand() % (400 * 16);
			move_speed[i].x = 4 - (rand() & 7);
			POLYGON_INIT_PART2;
		}
		initialized = 1;
	}
	for(i = 0; i < MUSIC_POLYGONS; i++) {
		polygon_build(
			points, pos[i].x, pos[i].y,
			((i & 3) << 4) + 64, VERTICES(i), angle[i]
		);
		pos[i].x += move_speed[i].x;
		pos[i].y += move_speed[i].y;
		angle[i] += rot_speed[i];
		if(pos[i].x <= 0 || pos[i].x >= 639) {
			move_speed[i].x *= -1;
		}
		if(pos[i].y >= (400 * 20)) {
			pos[i].x = rand() % 640;
			pos[i].y = -1600;
			move_speed[i].x = 8 - (rand() & 15);
			POLYGON_INIT_PART2;
		}
		grcg_polygon_c(points, VERTICES(i));
	}
}

void pascal near music_flip(void)
{
	screen_back_B_put();
	grcg_setcolor(GC_RMW | GC_B, 15);
	polygons_update_and_render();
	grcg_off();
	graph_showpage(music_page);
	music_page = 1 - music_page;
	graph_accesspage(music_page);
	frame_delay(1);
}

#define CMT_BACK_BLIT(dst, dp, src, sp) \
	ps = 0; \
	for(y = 64; y < 80; y++) { \
		for(x = 160; x < 480; x += (4 * 8)) { \
			pd = VRAM_OFFSET(x, y); \
			*(long*)(dst[PL_B] + (dp)) = *(long*)(src[PL_B] + (sp)); \
			*(long*)(dst[PL_R] + (dp)) = *(long*)(src[PL_R] + (sp)); \
			*(long*)(dst[PL_G] + (dp)) = *(long*)(src[PL_G] + (sp)); \
			*(long*)(dst[PL_E] + (dp)) = *(long*)(src[PL_E] + (sp)); \
			ps += 4; \
		} \
	} \
	for(y = 80; y < 384; y++) { \
		for(x = 304; x < 624; x += (4 * 8)) { \
			pd = VRAM_OFFSET(x, y); \
			*(long*)(dst[PL_B] + (dp)) = *(long*)(src[PL_B] + (sp)); \
			*(long*)(dst[PL_R] + (dp)) = *(long*)(src[PL_R] + (sp)); \
			*(long*)(dst[PL_G] + (dp)) = *(long*)(src[PL_G] + (sp)); \
			*(long*)(dst[PL_E] + (dp)) = *(long*)(src[PL_E] + (sp)); \
			ps += 4; \
		} \
	}

void pascal near cmt_back_snap(void)
{
	int ps, x, pd, y;
	int i;
	for(i = 0; i < PL_COUNT; i++) {
		cmt_back[i] = MK_FP(
			hmem_allocbyte(304 * (320 / 8) + 16 * (320 / 8)), 0
		);
	}
	CMT_BACK_BLIT(cmt_back, ps, VRAM_PLANE, pd);
}

#include "th02\music\cmt_load.c"

void pascal near cmt_back_free(void)
{
	hmem_free(FP_SEG(cmt_back[PL_B]));
	hmem_free(FP_SEG(cmt_back[PL_R]));
	hmem_free(FP_SEG(cmt_back[PL_G]));
	hmem_free(FP_SEG(cmt_back[PL_E]));
}

void pascal near cmt_back_put(void)
{
	int ps, x, pd, y;
	CMT_BACK_BLIT(VRAM_PLANE, pd, cmt_back, ps);
}

void pascal near draw_cmt(int track)
{
	int line;
	int p;
	music_cmt_load(track);
	screen_back_B_put();
	cmt_back_put();

	graph_putsa_fx(160, 64, FX(15, 1, 0), music_cmt[0]);
	for(line = 1; line < MUSIC_CMT_LINE_COUNT; line++) {
		graph_putsa_fx(304, (line + 4) * 16, FX(13, 1, 0), music_cmt[line]);
	}
	PLANE_DWORD_BLIT(screen_back_B, VRAM_PLANE_B);
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

	pi_load_put_free(0, "op3.pi");
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
			draw_track(music_sel, 15);
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
			draw_track(music_sel, 15);
		}
		if(key_det & INPUT_SHOT || key_det & INPUT_OK) {
			if(music_sel != SEL_QUIT) {
				char midi_active = snd_midi_active;

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
	pi_load_put_free(0, "op2.pi");
	palette_entry_rgb_show("op.rgb");
	graph_copy_page(0);
	graph_accesspage(0);
}

#pragma option -zCOP_MUSIC_TEXT

#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "libs/kaja/kaja.h"
extern "C" {
#include "th01/hardware/grppsafx.h"
}
#include "th02/v_colors.hpp"
extern "C" {
#include "th02/hardware/input.hpp"
#include "th02/formats/pi.h"
#include "th02/snd/snd.h"
}
#include "th02/shiftjis/fns.hpp"

extern const char* MUSIC_FILES[15];
extern uint8_t track_playing;

static const int MUSIC_CMT_LINE_LEN = 42;
static const int MUSIC_CMT_LINE_COUNT = 20;

#define SEL_QUIT TRACK_COUNT + 1

#define TRACK_COUNT sizeof(MUSIC_FILES) / sizeof(MUSIC_FILES[0])

extern unsigned char music_sel;
extern page_t music_page;
dots8_t *nopoly_B;
Planar<dots8_t far *> cmt_back;

void pascal near track_put(uint8_t sel, vc_t col);
void pascal near tracklist_put(uint8_t sel);
void near nopoly_B_snap(void);
void near nopoly_B_free(void);
void near nopoly_B_put(void);
void near music_flip(void);

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
	nopoly_B_put();
	cmt_back_put();

	graph_putsa_fx(160, 64, (V_WHITE | FX_WEIGHT_HEAVY), music_cmt[0]);
	for(line = 1; line < MUSIC_CMT_LINE_COUNT; line++) {
		graph_putsa_fx(
			304, ((line + 4) * GLYPH_H), (13 | FX_WEIGHT_HEAVY), music_cmt[line]
		);
	}
	plane_dword_blit(nopoly_B, VRAM_PLANE_B);
}

void pascal musicroom(void)
{
	music_page = 1;

	palette_black();

	graph_showpage(0);
	graph_accesspage(0);
	graph_clear();
	graph_accesspage(1);

	pi_load_put_8_free(0, reinterpret_cast<const char *>(MK_FP(_DS, 0x0C1D)));
	music_sel = track_playing;
	tracklist_put(music_sel);
	graph_copy_page(0);

	graph_accesspage(1);
	graph_showpage(0);
	nopoly_B_snap();
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
			track_put(music_sel, 3);
			if(music_sel > 0) {
				music_sel--;
			} else {
				music_sel = SEL_QUIT;
			}
			if(music_sel == TRACK_COUNT) {
				music_sel--;
			}
			track_put(music_sel, V_WHITE);
		}
		if(key_det & INPUT_DOWN) {
			track_put(music_sel, 3);
			if(music_sel < SEL_QUIT) {
				music_sel++;
			} else {
				music_sel = 0;
			}
			if(music_sel == TRACK_COUNT) {
				music_sel++;
			}
			track_put(music_sel, V_WHITE);
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
	nopoly_B_free();
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

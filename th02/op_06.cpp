#pragma option -zCOP_MUSIC_TEXT

#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "libs/kaja/kaja.h"
#include "th02/v_colors.hpp"
extern "C" {
#include "th02/hardware/input.hpp"
#include "th02/formats/pi.h"
#include "th02/snd/snd.h"
}

extern const char* MUSIC_FILES[15];
extern uint8_t track_playing;

static const int MUSIC_CMT_LINE_LEN = 42;
static const int MUSIC_CMT_LINE_COUNT = 20;

#define SEL_QUIT TRACK_COUNT + 1

#define TRACK_COUNT sizeof(MUSIC_FILES) / sizeof(MUSIC_FILES[0])

extern unsigned char music_sel;
extern page_t music_page;
dots8_t *nopoly_B;
Planar<dots8_t far *> cmt_bg;
shiftjis_t music_cmt[MUSIC_CMT_LINE_COUNT][MUSIC_CMT_LINE_LEN];

void pascal near track_put(uint8_t sel, vc_t col);
void pascal near tracklist_put(uint8_t sel);
void near nopoly_B_snap(void);
void near nopoly_B_free(void);
void near music_flip(void);
void near cmt_bg_snap(void);
void near cmt_bg_free(void);
void pascal near cmt_load_unput_and_put(int track);

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
	cmt_bg_snap();

	graph_accesspage(1);	cmt_load_unput_and_put(track_playing);
	graph_accesspage(0);	cmt_load_unput_and_put(track_playing);

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

				cmt_load_unput_and_put(music_sel);
				music_flip();
				cmt_load_unput_and_put(music_sel);
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
	cmt_bg_free();
	graph_showpage(0);
	graph_accesspage(0);
	graph_clear();
	graph_accesspage(1);
	pi_load_put_8_free(0, "op2.pi");
	palette_entry_rgb_show("op.rgb");
	graph_copy_page(0);
	graph_accesspage(0);
}

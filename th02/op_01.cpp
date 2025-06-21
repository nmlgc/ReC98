/* ReC98
 * -----
 * Code segment #1 of TH02's OP.EXE
 */

#include <stddef.h>
#include <process.h>
#include "libs/master.lib/master.hpp"
#include "th01/rank.h"
#include "th01/math/clamp.hpp"
#include "th01/hardware/grppsafx.h"
#include "th02/common.h"
#include "th02/resident.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/grp_rect.h"
#include "th02/hardware/input.hpp"
#include "th02/core/globals.hpp"
#include "th02/core/zunerror.h"
#include "th02/core/initexit.h"
#include "th02/formats/cfg.hpp"
#include "th02/formats/pi.h"
#include "th02/snd/snd.h"
#include "th02/gaiji/gaiji.h"
#include "th02/gaiji/str.hpp"
#include "th02/shiftjis/fns.hpp"
#include "th02/op/op.h"
#include "th02/op/menu.hpp"
#include "th02/op/m_music.hpp"

#pragma option -2 -a2

char menu_sel = 0;
bool in_option = false;
bool quit = false;
char unused_1 = 0; // ZUN bloat

static bool main_input_allowed;
unsigned char snd_bgm_mode;
static int unused_2; // ZUN bloat
unsigned int idle_frames;
unsigned char demo_num;
resident_t __seg *resident_seg;
menu_put_func_t menu_put;

// Apparently, declaring variables with `extern` before defining them for real
// within the same compilation unit causes Turbo C++ to emit *everything* in a
// different order... really, I couldn't make this up.
extern char extra_unlocked;
extern unsigned int score_duration;

void title_flash(void);
void pascal score_menu(void);
void pascal shottype_menu(void);

int cfg_load(void)
{
	cfg_t cfg;
	const char *cfg_fn = CFG_FN;

	if(file_exist(cfg_fn)) {
		file_ropen(cfg_fn);
		file_read(&cfg, sizeof(cfg));
		rank = cfg.opts.rank;
		snd_bgm_mode = cfg.opts.bgm_mode;
		bombs = cfg.opts.bombs;
		lives = cfg.opts.lives;
		resident_seg = cfg.resident;
		if(!resident_seg) {
			return 1;
		}
		resident = resident_seg;
		resident->reduce_effects = cfg.opts.reduce_effects;
		resident->debug = cfg.debug;
		file_close();

		if(snd_bgm_mode == SND_BGM_OFF) {
			snd_fm_possible = false;
			snd_active = false;
		} else if(snd_bgm_mode == SND_BGM_FM) {
			snd_midi_active = false;
			snd_determine_mode();
		} else {
			snd_midi_active = snd_midi_possible;
			snd_determine_mode();
		}
		return 0;
	}
	return 1;
}

void cfg_save(void)
{
	const char *cfg_fn = CFG_FN;
	cfg_t cfg;

	cfg.debug = 0;
	cfg.opts.rank = rank;
	cfg.opts.bgm_mode = snd_bgm_mode;
	cfg.opts.bombs = bombs;
	cfg.opts.lives = lives;
	cfg.opts.reduce_effects = resident->reduce_effects;

	file_create(cfg_fn);
	file_write(&cfg, offsetof(cfg_t, resident));
	file_write(&resident_seg, sizeof(resident_seg));
	file_write(&cfg.debug, sizeof(cfg.debug));
	file_close();
}

void text_wipe(void)
{
	text_clear();
	text_fillca(' ', TX_BLACK | TX_REVERSE);
}

void pascal near pi_load_put_8_free_to(const char near *fn, char page)
{
	pi_load(0, fn);
	graph_accesspage(page);
	pi_palette_apply(0);
	pi_put_8(0, 0, 0);
	pi_free(0);
}

void op_animate(void)
{
	// Sony Vegas calls this a "Barn Door" transition.
	int door_x;
	tram_y_t door_y;
	const char gbZUN[] = { g_chr_3(gb, Z,U,N), '\0' };

	text_wipe();
	snd_load("huuma.efc", SND_LOAD_SE);
	pi_load_put_8_free_to(MENU_MAIN_BG_FN, 1);
	pi_load_put_8_free_to("op.pi", 0);
	pi_load(0, "opa.pi");
	pi_load(1, "opb.pi");
	pi_load(2, "opc.pi");

	// ZUN landmine: The black text layer would cover the fact that this will
	// most certainly happen somewhere within a frame, but not if we
	// immediately start mutating text cells in the loop below.
	palette_settone(200);

	for(door_x = 0; door_x < 40; door_x++) {
		for(door_y = 0; door_y < 25; door_y++) {
			text_putca(39 - door_x, door_y, ' ', TX_WHITE);
			text_putca(door_x + 40, door_y, ' ', TX_WHITE);
		}
		palette_settone(200 - (door_x * 2));
		frame_delay(1);
	}
	for(door_x = 40; door_x < 50; door_x++) {
		palette_settone(200 - (door_x * 2));
		frame_delay(1);
	}
	palette_100();

	if(resident->demo_num == 0) {
		door_x = 0;
		if(snd_midi_possible) {
			door_x = snd_midi_active;
			snd_midi_active = true;
			snd_load(BGM_MENU_MAIN_FN, SND_LOAD_SONG);
		}
		snd_midi_active = false;
		snd_load(BGM_MENU_MAIN_FN, SND_LOAD_SONG);
		snd_midi_active = door_x;
	}

	frame_delay(18);
	title_flash();

	palette_settone(200);
	graph_accesspage(1);

	graph_gaiji_putc(548, 384, gs_COPYRIGHT, 0);
	graph_gaiji_puts(564, 384, 16, gbZUN, 0);
	graph_gaiji_putc(544, 380, gs_COPYRIGHT, 6);
	graph_gaiji_puts(560, 380, 16, gbZUN, 6);
	graph_copy_page(0);

	if(resident->demo_num == 0) {
		snd_kaja_func(KAJA_SONG_PLAY, 0);
	}
	resident->demo_num = 0;
	palette_entry_rgb_show(MENU_MAIN_PALETTE_FN);
	palette_white_in(6);
}

void pascal near start_init(void)
{
	snd_se_play_force(13);
	frame_delay(20);

	resident->rem_lives = lives;
	resident->rem_bombs = bombs;
	resident->start_lives = lives;
	resident->start_bombs = bombs;
	resident->bgm_mode = snd_bgm_mode;
	resident->start_power = 0;
	resident->score = 0;
	resident->continues_used = 0;
	resident->unused_3 = 0;
	resident->unused_1 = 0;
	resident->demo_num = 0;
	resident->score_highest = 0;
}

inline void start_exec() {
	cfg_save();
	pi_load(0, "ts1.pi");

	// ZUN landmine: Screen tearing – we most certainly won't come here during
	// VBLANK.
	text_clear();

	shottype_menu();
	snd_kaja_func(KAJA_SONG_FADE, 15);
	gaiji_restore();
	super_free();
	game_exit();
	if(resident->debug) {
		execl("select", "select", nullptr);
	} else {
		execl("main", "main", nullptr);
	}
}

void start_game(void)
{
	start_init();
	resident->rank = rank;
	resident->stage = 0;
	start_exec();
}

void start_demo(void)
{
	resident->rem_lives = 2;
	resident->rem_bombs = 3;
	resident->start_lives = 2;
	resident->start_bombs = 3;
	resident->bgm_mode = snd_bgm_mode;
	resident->rank = RANK_NORMAL;
	resident->continues_used = 0;
	resident->unused_3 = 0;
	resident->demo_num = demo_num;
	resident->shottype = 0;
	cfg_save();

	// ZUN landmine: Clearing TRAM before gaiji_restore() is correct, but doing
	// this after file I/O means that we most certainly won't come here during
	// VBLANK.
	text_clear();

	pi_free(0);
	pi_free(1);
	pi_free(2);
	gaiji_restore();
	super_free();
	game_exit();
	execl("main", "main", nullptr);
}

void start_extra(void)
{
	start_init();
	resident->rank = RANK_EXTRA;
	resident->stage = 5;
	resident->rem_lives = 2;
	resident->rem_bombs = 1;
	resident->start_lives = 2;
	resident->start_bombs = 1;
	start_exec();
}

#pragma option -d-

#include "th02/gaiji/ranks_c.c"

// ZUN bloat: Fixed-size strings ruin any chance of automatically centering
// these with compile-time calculations.

// A remnant from TH01? Unused in the final game.
const char gbHIT_KEY[] = { g_chr_7(gb, H,I,T,_,K,E,Y), '\0' };
const char gb7SPACES[] = { g_chr_7(gb, _,_,_,_,_,_,_), '\0' };

const char gbSTART[10] = { g_chr_5(gb, S,T,A,R,T), '\0' };
inline char menu_extra_pos() {
	return 1;
}
const char gbEXTRA_START[] = { g_chr_11(gb, E,X,T,R,A,_,S,T,A,R,T), '\0' };
const char gbHISCORE[10] = { g_chr_7(gb, H,I,S,C,O,R,E), '\0' };
const char gbOPTION[10] = { g_chr_6(gb, O,P,T,I,O,N), '\0' };
const char gbQUIT[10] = { g_chr_4(gb, Q,U,I,T), '\0' };
const char gbRANK[10] = { g_chr_4(gb, R,A,N,K), '\0' };
const char gbPLAYER[10] = { g_chr_6(gb, P,L,A,Y,E,R), '\0' };
const char gbMUSIC[10] = { g_chr_5(gb, M,U,S,I,C), '\0' };
const char gbBOMB[10] = { g_chr_4(gb, B,O,M,B), '\0' };
const char gbMUSIC_MODE[] = { g_chr_10(gb, M,U,S,I,C,_,M,O,D,E), '\0' };
const char gbRESET[10] = { g_chr_5(gb, R,E,S,E,T), '\0' };

const char gsRANKS[4][3] = {
	gs_EA, gs_SY, '\0',
	gs_NOR, gs_MAL, '\0',
	gs_HA, gs_RD, '\0',
	gs_LUN, gs_ATIC, '\0',
};

const unsigned char gbcBGM_MODE[3][5] = {
	g_chr_4(gb, O,F,F,_), '\0',
	g_chr_4(gb, _,F,M,_), '\0',
	g_chr_4(gb, M,I,D,I), '\0',
};

#include "th02/shiftjis/op_main.hpp"

#pragma option -d

void pascal near main_put_shadow(void)
{
	graph_gaiji_puts(284, 260, 16, gbSTART, 0);
	graph_gaiji_puts(236, 276, 16, gbEXTRA_START, 0);
	graph_gaiji_puts(268, 292, 16, gbHISCORE, 0);
	graph_gaiji_puts(276, 308, 16, gbOPTION, 0);
	graph_gaiji_puts(244, 324, 16, gbMUSIC_MODE, 0);
	graph_gaiji_puts(292, 340, 16, gbQUIT, 0);

	graph_gaiji_puts(212, 372, 16, gbRANK, 0);
	graph_gaiji_puts(308, 372, 16, gbcRANKS[rank], 0);
}

void pascal near main_put(int sel, tram_atrb2 atrb)
{
	if(sel == 0) {
		gaiji_putsa(35, 16, gbSTART, atrb);
	} else if(sel == 2) {
		gaiji_putsa(33, 18, gbHISCORE, atrb);
	} else if(sel == 3) {
		gaiji_putsa(34, 19, gbOPTION, atrb);
	} else if(sel == 4) {
		gaiji_putsa(30, 20, gbMUSIC_MODE, atrb);
	} else if(sel == 5) {
		gaiji_putsa(36, 21, gbQUIT, atrb);
	}
	if(sel == 1) {
		if(extra_unlocked) {
			gaiji_putsa(29, 17, gbEXTRA_START, atrb);
		} else {
			gaiji_putsa(29, 17, gbEXTRA_START, TX_BLUE);
		}
	}
	gaiji_putsa(26, 23, gbRANK, TX_GREEN);
	gaiji_putsa(38, 23, gbcRANKS[rank], TX_GREEN);
}

void pascal near menu_sel_update_and_render(int8_t max, int8_t direction)
{
	menu_put(menu_sel, TX_YELLOW);
	menu_sel += direction;
	if(!in_option && !extra_unlocked && menu_sel == menu_extra_pos()) {
		menu_sel += direction;
	}
	if(menu_sel < ring_min()) {
		menu_sel = max;
	}
	if(menu_sel > max) {
		menu_sel = 0;
	}
	menu_put(menu_sel, TX_WHITE);
}

inline void menu_init(
	bool& initialized, bool& input_allowed, nearfunc_t_near put_shadow
) {
	input_allowed = false;
	initialized = true;
	text_clear();
	graph_showpage(1);
	graph_copy_page(0);
	put_shadow();
	graph_showpage(0);
}

void main_update_and_render(void)
{
	static bool initialized = false;
	if(!initialized) {
		menu_init(initialized, main_input_allowed, main_put_shadow);
		idle_frames = 0;
		for(int i = 0; i < 6; i++) {
			main_put(i, menu_sel == i ? TX_WHITE : TX_YELLOW);
		}
		menu_put = main_put;
	}
	if(!key_det) {
		main_input_allowed = true;
	}
	if(main_input_allowed) {
		menu_update_vertical(key_det, 6);
		if(key_det & INPUT_SHOT || key_det & INPUT_OK) {
			switch(menu_sel) {
			case 0:
				start_game();
				break;
			case 1:
				start_extra();
				break;
			case 2:
				score_duration = 2000;
				text_clear();
				score_menu();
				graph_accesspage(1);
				graph_showpage(0);

				// ZUN landmine: We come here with [PaletteTone] set to 100,
				// which causes two screen tearing landmines. I've inlined the
				// usual pi_fullres_load_palette_apply_put_free() macro to
				// point this out more clearly:
				// • pi_load() takes a while and returns in the middle of some
				//   frame.
				// • pi_palette_apply() overwrites the hardware palette with
				//   `op2.pi`'s differing one, causing screen tearing.
				// • pi_put_8() also takes a while and returns in the middle of
				//   some frame.
				// • palette_entry_rgb_show() overwrites the hardware palette
				//   with another differing one, also causing screen tearing.
				// Without considering execution times, the pi_palette_apply()
				// call seems redundant, but it does have a visible effect on
				// any PC-98 model that can't run pi_put_8() instantly. This
				// does not include the infinitely fast PC-98 we're assuming
				// over on the `debloated` branch, though.
				pi_load(0, MENU_MAIN_BG_FN);
				pi_palette_apply(0);
				pi_put_8(0, 0, 0);
				pi_free(0);
				palette_entry_rgb_show(MENU_MAIN_PALETTE_FN);

				graph_copy_page(0);
				graph_accesspage(0);
				initialized = false;
				break;
			case 3:
				menu_sel = 0;
				in_option = true;
				initialized = false;
				break;
			case 4:
				text_clear();
				musicroom_menu();
				initialized = false;
				break;
			case 5:
				quit = true;
				break;
			}
		}
		if(key_det & INPUT_CANCEL) {
			quit = true;
		}
		if(key_det) {
			main_input_allowed = false;
			idle_frames = 0;
		}
	}
	if(idle_frames > 640) {
		start_demo();
	}
}

void pascal near option_put_shadow(void)
{
	graph_gaiji_puts(196, 260, 16, gbRANK, 0);
	graph_gaiji_puts(196, 276, 16, gbMUSIC, 0);
	graph_gaiji_puts(196, 292, 16, gbPLAYER, 0);
	graph_gaiji_puts(196, 308, 16, gbBOMB, 0);
	graph_putsa_fx(196, 324, 0, REDUCE_EFFECTS_TITLE);
	graph_gaiji_puts(284, 340, 16, gbRESET, 0);
	graph_gaiji_puts(292, 372, 16, gbQUIT, 0);
}

void pascal near option_put(int sel, tram_atrb2 atrb)
{
	if(sel == 0) {
		gaiji_putsa(24, 16, gbRANK, atrb);
		gaiji_putsa(42, 16, gbcRANKS[rank], atrb);
		graph_copy_rect_1_to_0_16(336, 260, 128, 16);
		graph_gaiji_puts(340, 260, 16, gbcRANKS[rank], 0);
	} else if(sel == 1) {
		gaiji_putsa(24, 17, gbMUSIC, atrb);
		gaiji_putsa(47, 17, gbcBGM_MODE[(char)snd_bgm_mode], atrb);
		graph_copy_rect_1_to_0_16(376, 276, 64, 16);
		graph_gaiji_puts(380, 276, 16, gbcBGM_MODE[(char)snd_bgm_mode], 0);
	} else if(sel == 2) {
		gaiji_putsa(24, 18, gbPLAYER, atrb);
		gaiji_putca(49, 18, lives + 1 + gb_0, atrb);
		graph_copy_rect_1_to_0_16(392, 292, 32, 16);
		graph_gaiji_putc(396, 292, lives + 1 + gb_0, 0);
	} else if(sel == 3) {
		gaiji_putsa(24, 19, gbBOMB, atrb);
		gaiji_putca(49, 19, bombs + gb_0, atrb);
		graph_copy_rect_1_to_0_16(392, 308, 32, 16);
		graph_gaiji_putc(396, 308, bombs + gb_0, 0);
	} else if(sel == 4) {
		text_putsa(24, 20, REDUCE_EFFECTS_TITLE, atrb);
		text_putsa(
			45, 20, REDUCE_EFFECTS_CHOICES[resident->reduce_effects], atrb
		);
		graph_copy_rect_1_to_0_16(360, 324, 128, 16);
		graph_putsa_fx(
			364, 324, 0, REDUCE_EFFECTS_CHOICES[resident->reduce_effects]
		);
	} else if(sel == 5) {
		gaiji_putsa(35, 21, gbRESET, atrb);
	} else if(sel == 6) {
		gaiji_putsa(36, 23, gbQUIT, atrb);
	}
}

void pascal near snd_bgm_restart(void)
{
	if(snd_bgm_mode == SND_BGM_OFF) {
		snd_fm_possible = false;
		snd_kaja_func(KAJA_SONG_STOP, 0);
		snd_active = false;
		return;
	} else if(snd_bgm_mode == SND_BGM_FM) {
		snd_kaja_func(KAJA_SONG_STOP, 0);
		snd_midi_active = false;
		snd_determine_mode();
		snd_kaja_func(KAJA_SONG_PLAY, 0);
	} else if(snd_bgm_mode == SND_BGM_MIDI) {
		snd_kaja_func(KAJA_SONG_STOP, 0);
		snd_midi_active = snd_midi_possible;
		snd_determine_mode();
		snd_kaja_func(KAJA_SONG_PLAY, 0);
	}
}

inline void option_quit(bool &initialized) {
	menu_sel = 3;
	in_option = false;
	initialized = false;
}

// Circumventing 16-bit promotion inside comparisons between two 8-bit values
// in Borland C++'s C++ mode...
inline char option_rank_max()  { return RANK_LUNATIC; }
inline char option_bgm_max()   { return SND_BGM_MIDI; }
inline char option_lives_max() { return CFG_LIVES_MAX; }
inline char option_bombs_max() { return CFG_BOMBS_MAX; }

void option_update_and_render(void)
{
	static bool input_allowed = false;
	static bool initialized = false;

	#define option_change(ring_direction) \
		option_put(menu_sel, TX_YELLOW); \
		switch(menu_sel) { \
		case 0: \
			ring_direction(rank, option_rank_max()); \
			break; \
		case 1: \
			ring_direction((char)snd_bgm_mode, option_bgm_max()); \
			snd_bgm_restart(); \
			break; \
		case 2: \
			ring_direction(lives, option_lives_max()); \
			break; \
		case 3: \
			ring_direction(bombs, option_bombs_max()); \
			break; \
		case 4: \
			resident->reduce_effects = (true - resident->reduce_effects); \
			break; \
		} \
		option_put(menu_sel, TX_WHITE);

	if(!initialized) {
		menu_init(initialized, input_allowed, option_put_shadow);
		for(int i = 0; i < 7; i++) {
			option_put(i, menu_sel == i ? TX_WHITE : TX_YELLOW);
		}
		menu_put = option_put;
	}
	if(!key_det) {
		input_allowed = 1;
	}
	if(input_allowed) {
		menu_update_vertical(key_det, 7);
		if(key_det & INPUT_RIGHT) {
			option_change(ring_inc);
		}
		if(key_det & INPUT_LEFT) {
			option_change(ring_dec);
		}
		if(key_det & INPUT_SHOT || key_det & INPUT_OK) {
			switch(menu_sel) {
			case 5:
				rank = RANK_NORMAL;
				snd_bgm_mode = SND_BGM_FM;
				snd_kaja_func(KAJA_SONG_STOP, 0);
				snd_midi_active = false;
				snd_determine_mode();
				snd_kaja_func(KAJA_SONG_PLAY ,0);
				lives = CFG_LIVES_DEFAULT;
				bombs = CFG_BOMBS_DEFAULT;
				resident->unused_2 = 1;
				resident->reduce_effects = false;
				option_put(0, TX_YELLOW);
				option_put(1, TX_YELLOW);
				option_put(2, TX_YELLOW);
				option_put(3, TX_YELLOW);
				option_put(4, TX_YELLOW);
				break;
			case 6:
				option_quit(initialized);
				break;
			}
		}
		if(key_det & INPUT_CANCEL) {
			option_quit(initialized);
		}
		if(key_det) {
			input_allowed = false;
		}
	}
}

int main(void)
{
	unsigned char ret;
	if(snd_pmd_resident()) {
		snd_mmd_resident();
		if(game_init_op()) {
			zun_error(ERROR_OUT_OF_MEMORY);
			return 1;
		}
		extra_unlocked = cleardata_load();
		if(cfg_load() == 1) {
			return 1;
		}
	} else {
		return 1;
	}
	gaiji_backup();
	gaiji_entry_bfnt("MIKOFT.bft");
	if(resident->demo_num == 0) {
		demo_num = 1;
		snd_kaja_func(KAJA_SONG_STOP, 0);
	} else {
		demo_num = resident->demo_num + 1;
		if(demo_num > 3) {
			demo_num = 1;
		}
		score_duration = 350;
		score_menu();
		graph_showpage(0);
		graph_accesspage(0);
	}
	key_det = 0;

	snd_active = snd_bgm_mode;
	if(!resident->demo_num && snd_midi_possible) {
		char midi_active = snd_midi_active;

		snd_midi_active = 1;
		snd_load("gminit.m", SND_LOAD_SONG);
		snd_kaja_func(KAJA_SONG_PLAY, 0);
		snd_midi_active = midi_active;
	}

	op_animate();

	// ZUN landmine: Screen tearing. Decoding two 192×144 .PI images takes a
	// while and certainly returns with the CRT beam somewhere in the middle of
	// a frame. A bit much to ask main_update_and_render() to then render the
	// Main menu labels to both TRAM and VRAM on the same frame.
	pi_load(2, "ts3.pi");
	pi_load(1, "ts2.pi");
	key_det = 0;
	idle_frames = 0;

	while(!quit) {
		input_reset_sense();
		if(in_option == false) {
			main_update_and_render();
		} else if(in_option == true) {
			option_update_and_render();
		}
		resident->frame++;
		idle_frames++;
		frame_delay(1);
	}

	ret = resident->op_main_retval;
	resident_seg = 0;
	cfg_save();
	text_clear();
	graph_clear();
	game_exit_to_dos();
	gaiji_restore();
	return ret;
}

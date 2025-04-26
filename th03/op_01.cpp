/* ReC98
 * -----
 * Code segment #1 of TH03's OP.EXE
 */

#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/math/clamp.hpp"
#include "th01/core/initexit.hpp"
#include "th02/hardware/frmdelay.h"
#include "th03/common.h"
#include "th03/resident.hpp"
#include "th03/hardware/input.h"
#include "th03/formats/cfg_impl.hpp"
#include "th03/gaiji/str.hpp"
#include "th03/snd/snd.h"
#include "th03/shiftjis/fns.hpp"
#include "th03/op/m_main.hpp"
#include "th03/op/m_select.hpp"
#include <stddef.h>
#include <process.h>

// Proportional gaiji strings
// --------------------------

enum gaiji_th03_mikoft_t {
	gp_1P_vs = 0x88,
	gp_1P_vs_last = ((gp_1P_vs + 4) - 1),
	gp__CPU,
	gp__CPU_last = ((gp__CPU + 4) - 1),
	gp_CPU_vs = 0x92,
	gp_CPU_vs_last = ((gp_CPU_vs + 4) - 1),
	gp__2P,
	gp__2P_last = ((gp__2P + 4) - 1),
};

// Constructs a VS choice string out of its two halves.
#define g_str_vs(first, second) { g_str_4(first), g_str_4(second), '\0' }
// --------------------------

bool snd_sel_disabled = false; // Yes, it's just (!snd_fm_possible).

/// YUME.CFG loading and saving
/// ---------------------------

// These will be removed once the strings can be defined here
#undef CFG_FN
#undef BINARY_MAINL
extern const char CFG_FN[];
extern char BINARY_MAINL[];

void near cfg_load(void)
{
	cfg_t cfg;

	cfg_load_and_set_resident(cfg, CFG_FN);

	resident->bgm_mode = cfg.opts.bgm_mode;
	snd_determine_mode();
	snd_sel_disabled = false;
	if(!snd_active) {
		resident->bgm_mode = SND_BGM_OFF;
		snd_sel_disabled = true;
	} else if(cfg.opts.bgm_mode == SND_BGM_OFF) {
		snd_active = false;
	}

	resident->key_mode = cfg.opts.key_mode;
	resident->rank = cfg.opts.rank;
}

inline void cfg_save_bytes(cfg_t &cfg, size_t bytes) {
	file_append(CFG_FN);
	file_seek(0, SEEK_SET);

	cfg.opts.bgm_mode = resident->bgm_mode;
	cfg.opts.key_mode = resident->key_mode;
	cfg.opts.rank = resident->rank;

	file_write(&cfg.opts, bytes);
	file_close();
}

void near cfg_save(void)
{
	cfg_t cfg;
	cfg_save_bytes(cfg, 4); // MODDERS: Should be `sizeof(cfg.opts)`
}

void near cfg_save_exit(void)
{
	cfg_t cfg = { 0 };
	cfg_save_bytes(cfg, sizeof(cfg));
}
/// ---------------------------

#define resident_reset_scores(i) { \
	/* ZUN bloat: Very unsafe. */ \
	for(i = 0; i < (PLAYER_COUNT * SCORE_DIGITS); i++) { \
		resident->score_last[0].digits[i] = 0; \
	} \
}

inline bool switch_to_mainl(void) {
	cfg_save();
	gaiji_restore();
	snd_kaja_func(KAJA_SONG_STOP, 0);
	game_exit();
	execl(BINARY_MAINL, BINARY_MAINL, 0, 0);
	return false;
}

bool near story_menu(void)
{
	enum {
		RANDOM_OPPONENT_MIN = PLAYCHAR_REIMU,
		RANDOM_OPPONENT_MAX = PLAYCHAR_RIKAKO,
		RANDOM_OPPONENT_COUNT = (
			(RANDOM_OPPONENT_MAX - RANDOM_OPPONENT_MIN) + 1
		),
	};

	// ZUN bloat: Could have been local.
	static bool opponent_seen[RANDOM_OPPONENT_COUNT] = { false };

	// ACTUAL TYPE: playchar_t
	static const uint8_t STAGE7_OPPONENT_FOR[PLAYCHAR_COUNT] = {
		PLAYCHAR_MIMA, // for Reimu
		PLAYCHAR_REIMU, // for Mima
		PLAYCHAR_REIMU, // for Marisa
		PLAYCHAR_MARISA, // for Ellen
		PLAYCHAR_REIMU, // for Kotohime
		PLAYCHAR_ELLEN, // for Kana
		PLAYCHAR_KANA, // for Rikako
		PLAYCHAR_KOTOHIME, // for Chiyuri
		PLAYCHAR_RIKAKO, // for Yumemi
	};

	int stage;
	int candidate;

	resident->demo_num = 0;
	resident->pid_winner = 0;
	resident->story_stage = 0;
	resident->is_cpu[0] = false;
	resident->is_cpu[1] = true;
	resident->game_mode = GM_STORY;
	resident->story_lives = CREDIT_LIVES;
	resident->show_score_menu = false;
	resident->playchar_paletted[1].v = -1;

	if(select_story_menu()) {
		return true;
	}

retry_opponent_selection:
	// ACTUAL TYPE: playchar_t
	int stage7_opponent = STAGE7_OPPONENT_FOR[
		resident->playchar_paletted[0].char_id_16()
	];
	irand_init(resident->rand);

	for(stage = 0; stage < 6; stage++) {
		// Confirmed to terminate for all 2³² possible seeds and all original
		// combinations of player character and Stage 7 opponent.
		do {
			candidate = (
				RANDOM_OPPONENT_MIN + (irand() % RANDOM_OPPONENT_COUNT)
			);
		} while(opponent_seen[candidate] || (stage7_opponent == candidate));
		opponent_seen[candidate] = true;

		// ZUN bloat: Should not change types.
		#define candidate_paletted candidate
		candidate_paletted = TO_OPTIONAL_PALETTED(candidate);
		resident->story_opponents[stage].v = candidate_paletted;

		// ZUN bloat: All of these palette swaps could have been done in a
		// single loop at the end.
		if(candidate_paletted == resident->playchar_paletted[0].v) {
			resident->story_opponents[stage].v = (candidate_paletted + 1);
		}
		#undef candidate_paletted
	}

	resident->playchar_paletted[1] = resident->story_opponents[0];
	resident->story_opponents[6].v = TO_OPTIONAL_PALETTED(stage7_opponent);

	// ZUN bloat: Palette swaps...
	resident->story_opponents[7].set(PLAYCHAR_CHIYURI);
	if(
		resident->playchar_paletted[0].v ==
		TO_OPTIONAL_PALETTED(PLAYCHAR_CHIYURI)
	) {
		resident->story_opponents[7].v++;
	}
	resident->story_opponents[8].set(PLAYCHAR_YUMEMI);
	if(
		resident->playchar_paletted[0].v ==
		TO_OPTIONAL_PALETTED(PLAYCHAR_YUMEMI)
	) {
		resident->story_opponents[8].v++;
	}

	// ZUN bloat: This can never happen.
	for(stage = 0; stage < STAGE_COUNT; stage++) {
		if(resident->story_opponents[stage].char_id_16() >= PLAYCHAR_COUNT) {
			goto retry_opponent_selection;
		}
	}

	resident_reset_scores(stage);
	resident->rem_credits = 3;
	resident->op_skip_animation = false;
	resident->skill = (70 + (resident->rank * 25));
	return switch_to_mainl();
}

inline tram_y_t choice_tram_y(unsigned int line) {
	return ((BOX_TOP / GLYPH_H) + 1 + line);
}

void pascal near vs_choice_put(int sel, tram_atrb2 atrb)
{
	enum {
		W = (8 * GAIJI_W),
		TRAM_LEFT = ((BOX_SUBMENU_CENTER_X - (W / 2)) / GLYPH_HALF_W),
	};
	if(sel == VS_1P_CPU) {
		static const char STR[] = g_str_vs(gp_1P_vs, gp__CPU);
		gaiji_putsa(TRAM_LEFT, choice_tram_y(1), STR, atrb);
	} else if(sel == VS_1P_2P) {
		static const char STR[] = g_str_vs(gp_1P_vs, gp__2P);
		gaiji_putsa(TRAM_LEFT, choice_tram_y(2), STR, atrb);
	} else /* if (sel == VS_CPU_CPU) */ {
		static const char STR[] = g_str_vs(gp_CPU_vs, gp__CPU);
		gaiji_putsa(TRAM_LEFT, choice_tram_y(3), STR, atrb);
	}
}

bool near vs_menu(void)
{
	int sel;
	input_t input_prev = INPUT_NONE;

	// After a match, we come back here, skip the menu, and launch into
	// character selection.
	if(resident->game_mode < GM_VS) {
		text_clear();
		box_main_to_submenu_animate();

		sel = VS_1P_CPU;
		vs_choice_put(VS_1P_CPU, TX_WHITE);
		vs_choice_put(VS_1P_2P, TX_BLACK);
		vs_choice_put(VS_CPU_CPU, TX_BLACK);

		while(1) {
			input_mode_interface();
			if(input_prev == INPUT_NONE) {
				if(input_sp & INPUT_UP) {
					vs_choice_put(sel, TX_BLACK);
					ring_dec(sel, VS_CPU_CPU);
					vs_choice_put(sel, TX_WHITE);
				}
				if(input_sp & INPUT_DOWN) {
					vs_choice_put(sel, TX_BLACK);
					ring_inc(sel, VS_CPU_CPU);
					vs_choice_put(sel, TX_WHITE);
				}
				if((input_sp & INPUT_SHOT) || (input_sp & INPUT_OK)) {
					break;
				}
				// ZUN bug: Should have added a INPUT_CANCEL branch to allow
				// players to quit back to the main menu once they entered this
				// one.
			}
			input_prev = input_sp;
			frame_delay(1);
		}
	} else {
		sel = (resident->game_mode - GM_VS);
	}

	resident->is_cpu[0] = ((sel == VS_CPU_CPU) ? true : false);
	resident->is_cpu[1] = ((sel != VS_1P_2P) ? true : false);
	resident->demo_num = 0;
	resident->pid_winner = 0;
	resident->story_stage = 0;
	resident->game_mode = (GM_VS + sel);
	resident->show_score_menu = false;

	// ZUN bloat: Could be compressed into a single branch.
	if(sel == VS_1P_2P) {
		if(select_1p_vs_2p_menu()) {
			resident->game_mode = GM_NONE;
			return true;
		}
	} else {
		if(select_vs_cpu_menu()) {
			resident->game_mode = GM_NONE;
			return true;
		}
	}

	resident_reset_scores(sel);
	return switch_to_mainl();
}

void near start_demo(void)
{
	static const int8_t PAIRINGS[DEMO_COUNT * PLAYER_COUNT] = {
		TO_OPTIONAL_PALETTED(PLAYCHAR_MIMA),
		TO_OPTIONAL_PALETTED(PLAYCHAR_REIMU),

		TO_OPTIONAL_PALETTED(PLAYCHAR_MARISA),
		TO_OPTIONAL_PALETTED(PLAYCHAR_RIKAKO),

		TO_OPTIONAL_PALETTED(PLAYCHAR_ELLEN),
		TO_OPTIONAL_PALETTED(PLAYCHAR_KANA),

		TO_OPTIONAL_PALETTED(PLAYCHAR_KOTOHIME),
		TO_OPTIONAL_PALETTED(PLAYCHAR_MARISA),
	};
	static const int32_t RAND[DEMO_COUNT] = { 600, 1000, 3200, 500 };

	resident->is_cpu[0] = true;
	resident->is_cpu[1] = true;
	ring_inc_range(resident->demo_num, 1, DEMO_COUNT);
	resident->pid_winner = 0;

	// Critically important to guarantee deterministic demos!
	resident->story_stage = 0;

	resident->game_mode = GM_DEMO;
	resident->show_score_menu = false;

	// ZUN bloat: A two-dimensional array would have been more readable and
	// would have generated better code.
	resident->playchar_paletted[0].v = (
		PAIRINGS[((resident->demo_num - 1) * PLAYER_COUNT) + 0]
	);
	resident->playchar_paletted[1].v = (
		PAIRINGS[((resident->demo_num - 1) * PLAYER_COUNT) + 1]
	);

	resident->rand = RAND[resident->demo_num - 1];
	int i;
	resident_reset_scores(i);
	palette_black_out(1);

	switch_to_mainl();
}

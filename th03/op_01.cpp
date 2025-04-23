/* ReC98
 * -----
 * Code segment #1 of TH03's OP.EXE
 */

#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/core/initexit.hpp"
#include "th03/common.h"
#include "th03/resident.hpp"
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

// extern const playchar_paletted_t demo_chars[DEMO_COUNT][PLAYER_COUNT];
// extern const int32_t demo_rand[DEMO_COUNT];

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
void pascal near start_demo();

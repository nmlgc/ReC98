/* ReC98
 * -----
 * Code segment #1 of TH03's OP.EXE
 */

extern "C" {
#include <stddef.h>
#include <dos.h>
#include "platform.h"
#include "master.hpp"
#include "th03/common.h"
#include "th03/chars.hpp"
#include "th03/score.h"
#include "th03/resident.hpp"
#include "th03/formats/cfg.hpp"
#include "th03/snd/snd.h"

bool snd_sel_disabled = false; // Yes, it's just (!snd_fm_possible).

// extern const playchar_paletted_t demo_chars[DEMO_COUNT][PLAYER_COUNT];
// extern const int32_t demo_rand[DEMO_COUNT];

/// YUME.CFG loading and saving
/// ---------------------------
// These will be removed once the strings can be defined here
#undef CFG_FN
extern const char CFG_FN[];

void near pascal cfg_load(void)
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

void near pascal cfg_save(void)
{
	cfg_t cfg;
	cfg_save_bytes(cfg, 4); // MODDERS: Should be `sizeof(cfg.opts)`
}

void near pascal cfg_save_exit(void)
{
	cfg_t cfg = { 0 };
	cfg_save_bytes(cfg, sizeof(cfg));
}
/// ---------------------------

void pascal near start_demo();
}

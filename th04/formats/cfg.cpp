#include <stddef.h>
#include "th03/formats/cfg_impl.hpp"
#if (GAME == 5)
	#include "th05/resident.hpp"
#else
	#include "th04/resident.hpp"
#endif
#include "th04/snd/snd.h"

#if (GAME == 4)
	bool snd_sel_disabled = false; // ZUN bloat: Unused in this game.
#endif

inline void cfg_options_update_from_resident(cfg_options_t &opts) {
	opts.rank = resident->rank;
	opts.lives = resident->cfg_lives;
	opts.bombs = resident->cfg_bombs;
	opts.bgm_mode = resident->bgm_mode;
	opts.se_mode = resident->se_mode;
	opts.turbo_mode = resident->turbo_mode;
}

void near cfg_load(void)
{
	cfg_t cfg;

	cfg_load_and_set_resident(cfg, CFG_FN);

	// TH05 does this in RES_KSO.COM.
	#if (GAME == 4)
		resident->rank = cfg.opts.rank;
		resident->cfg_lives = cfg.opts.lives;
		resident->cfg_bombs = cfg.opts.bombs;
		resident->bgm_mode = cfg.opts.bgm_mode;
		resident->se_mode = cfg.opts.se_mode;
		resident->turbo_mode = cfg.opts.turbo_mode;
	#endif

	if((resident->cfg_lives > CFG_LIVES_MAX) || (resident->cfg_lives == 0)) {
		resident->cfg_lives = CFG_LIVES_DEFAULT;
	}
	if(resident->cfg_bombs > CFG_BOMBS_MAX) {
		resident->cfg_bombs = CFG_BOMBS_MAX;
	}
	if(resident->bgm_mode >= SND_BGM_MODE_COUNT) {
		resident->bgm_mode = SND_BGM_OFF;
	}
	if(resident->se_mode >= SND_SE_MODE_COUNT) {
		resident->se_mode = SND_SE_OFF;
	}
}

void near cfg_save(void)
{
	union {
		int8_t sum;
		int16_t space; // ZUN bloat
	} u1;
	cfg_options_t opts;

	file_append(CFG_FN); // We don't write the full file here!
	file_seek(0, SEEK_SET);

	cfg_options_update_from_resident(opts);
	file_write(&opts, sizeof(cfg_options_t));

	// Skip over the resident pointer
	file_seek(offsetof(cfg_t, opts_sum), SEEK_SET);

	u1.sum = opts.sum();
	file_write(&u1.sum, sizeof(u1.sum));
	file_close();
}

void near cfg_save_exit(void)
{
	cfg_t cfg = { 0 };

	// ZUN landmine: In contrast to the function above, we do write the entire
	// structure here. Since file_append() will fail if the file doesn't exist,
	// file_create() would have been safer here.
	file_append(CFG_FN);
	file_seek(0, SEEK_SET);

	cfg_options_update_from_resident(cfg.opts);
	cfg.opts_sum = cfg.opts.sum();
	file_write(&cfg, sizeof(cfg));
	file_close();
}

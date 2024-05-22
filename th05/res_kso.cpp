/* ReC98
 * -----
 * TH05 ZUN.COM -S. Initializes the resident structure and configuration file
 * required in order to run TH05.
 */

#pragma option -2 // ZUN bloat

#include <stddef.h>
#include "platform.h"
#include "decomp.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/rank.h"
#include "th04/score.h"
#include "th05/resident.hpp"
#include "th04/snd/snd.h"
#include "th04/formats/cfg.hpp"

char debug = 0;
const cfg_options_t OPTS_DEFAULT = {
	RANK_SHOW_SETUP_MENU, CFG_LIVES_DEFAULT, CFG_BOMBS_DEFAULT,
	SND_BGM_FM26, SND_SE_FM, true
};

char cfg_init(resident_t __seg *resident_seg)
{
	const char *fn = CFG_FN_LOWER;
	cfg_options_t opts = OPTS_DEFAULT;
	cfg_t cfg_in;
	resident_t far *resident = resident_seg;

	if(!file_ropen(fn)) {
recreate:
		if(!file_create(fn)) {
			return 1;
		}
		file_write(&opts, sizeof(opts));
		resident->rank = RANK_SHOW_SETUP_MENU;
		resident->cfg_lives = CFG_LIVES_DEFAULT;
		resident->cfg_bombs = CFG_BOMBS_DEFAULT;
		resident->bgm_mode = SND_BGM_FM26;
		resident->se_mode = SND_SE_FM;
		resident->turbo_mode = true;
	} else {
		file_read(&cfg_in, sizeof(cfg_in));
		file_close();
		if((
			cfg_in.opts.rank
			+ cfg_in.opts.lives
			+ cfg_in.opts.bombs
			+ cfg_in.opts.bgm_mode
			+ cfg_in.opts.se_mode
			+ cfg_in.opts.turbo_mode
		) != cfg_in.opts_sum) {
			goto recreate;
		}
		resident->rank = cfg_in.opts.rank;
		resident->cfg_lives = cfg_in.opts.lives;
		resident->cfg_bombs = cfg_in.opts.bombs;
		resident->bgm_mode = cfg_in.opts.bgm_mode;
		resident->se_mode = cfg_in.opts.se_mode;
		resident->turbo_mode = cfg_in.opts.turbo_mode;
		if(resident->cfg_lives > CFG_LIVES_MAX || resident->cfg_lives == 0) {
			goto recreate;
		}
		if(resident->cfg_bombs > CFG_BOMBS_MAX) {
			goto recreate;
		}
		if(resident->bgm_mode >= SND_BGM_MODE_COUNT) {
			goto recreate;
		}
		if(resident->se_mode >= SND_SE_MODE_COUNT) {
			goto recreate;
		}
		if(!file_append(fn)) {
			return 1;
		}
		file_seek(offsetof(cfg_t, resident), 0);
	}
	if(!file_write(&resident_seg, sizeof(resident_seg))) {
		return 1;
	}
	file_write(&debug, sizeof(debug));
	// Yes, this is uninitialized if the file didn't exist!
	file_write(&cfg_in.opts_sum, sizeof(cfg_in.opts_sum));
	file_close();
	return 0;
}

#define LOGO \
	"東方怪綺談用　 常駐プログラム　                         Version1.00 (c)zun 1998"

#define ERROR_NOT_RESIDENT "まだいませんよぉ"
#define REMOVED "じゃぁねー、また会えるよね"
#define INITIALIZED "おじゃましまーす。"

#define RES_INIT_BOTTOM { \
	if(cfg_init(seg)) { \
		dos_free(seg); \
		dos_puts2("ファイルが書き込めないの～\n\n"); \
		return 1; \
	} \
	resident = reinterpret_cast<resident_t far *>(resident_bytes); \
	if(debug) { \
		resident->debug = true; \
	} \
}

#include "th02/res_init.cpp"

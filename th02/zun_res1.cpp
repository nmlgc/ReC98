/* ReC98
 * -----
 * 1st part of ZUN_RES.COM. Initializes the resident structure and
 * configuration file required in order to run TH02.
 */

#include <dos.h>
#include "platform.h"
#include "master.hpp"
#include "th01/rank.h"
#include "th02/resident.hpp"
#include "th02/snd/snd.h"
#include "th02/formats/cfg.h"

extern "C" int pascal scoredat_verify(void);

char debug = 0;
const cfg_options_t OPTS_DEFAULT = {
	RANK_NORMAL, SND_BGM_FM, CFG_BOMBS_DEFAULT, CFG_LIVES_DEFAULT, 0
};

#include "th02/formats/cfg_init.c"

#define LOGO \
	"東方封魔録用　 常駐プログラム　ZUN_RES.com Version1.01       (c)zun 1997"

#define RES_INIT_TOP \
	if(scoredat_verify() == 1) { \
		dos_puts2("ハイスコアファイルがおかしいの、もう一度実行してね。\n"); \
		return 1; \
	}

#define optimization_barrier_3()

#define RES_INIT_BOTTOM \
	cfg_init(sgm);

#include "th02/res_init.cpp"

#pragma codestring "\x00"

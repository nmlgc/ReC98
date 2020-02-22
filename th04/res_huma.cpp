/* ReC98
 * -----
 * TH04 ZUN.COM -S. Initializes the resident structure and configuration file
 * required in order to run TH04.
 */

#include <ReC98.h>
#include "th01/ranks.h"
#include "th04/score.h"
#include "th04/resident.hpp"
#include "th04/snd/snd.h"
#include "th04/formats/cfg.h"

#pragma option -a1

char debug = 0;
const cfg_options_t OPTS_DEFAULT = {
	RANK_DEFAULT, CFG_LIVES_DEFAULT, CFG_BOMBS_DEFAULT,
	SND_BGM_FM26, SND_SE_FM, true
};

void cfg_init(seg_t resident_sgm)
{
	const char *fn = CFG_FN;
	cfg_options_t opts = OPTS_DEFAULT;
	cfg_t cfg_in;

	if(!file_ropen(fn)) {
recreate:
		file_create(fn);
		file_write(&opts, sizeof(opts));
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
		file_append(fn);
		file_seek(offsetof(cfg_t, resident), 0);
	}
	file_write(&resident_sgm, sizeof(resident_sgm));
	file_write(&debug, sizeof(debug));
	// Yes, this is uninitialized if the file didn't exist!
	file_write(&cfg_in.opts_sum, sizeof(cfg_in.opts_sum));
	file_close();
}

#define LOGO \
	"東方幻想郷用　 常駐プログラム　RES_HUMA.com Version1.00       (c)zun 1998"

#define optimization_barrier_3()

#define RES_INIT_BOTTOM { \
	cfg_init(sgm); \
	\
	resident_t far *resident; \
	resident = reinterpret_cast<resident_t far *>(resident_bytes); \
	if(debug) { \
		resident->debug = true; \
	} \
}

#include "th02/res_init.c"

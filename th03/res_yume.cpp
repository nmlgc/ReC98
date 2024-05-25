/* ReC98
 * -----
 * TH03 ZUN.COM -5. Initializes the resident structure and configuration file
 * required in order to run TH03.
 */

#include <dos.h>
#include "platform.h"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/rank.h"
#include "th02/snd/snd.h"
#include "th03/common.h"
#include "th03/resident.hpp"
#include "th03/formats/cfg.hpp"

char debug = 0;
const cfg_options_t OPTS_DEFAULT = { SND_BGM_FM, KM_KEY_KEY, RANK_NORMAL };

#include "th02/formats/cfg_init.c"

#define LOGO \
	"東方夢時空用　 常駐プログラム　RES_YUME.com Version1.00       (c)zun 1997"

#define optimization_barrier()

#define RES_INIT_BOTTOM \
	cfg_init(seg);

#include "th02/res_init.cpp"

/* ReC98
 * -----
 * TH03 ZUN.COM -5. Initializes the resident structure and configuration file
 * required in order to run TH03.
 */

#include <ReC98.h>
#include "th01/ranks.h"
#include "th02/snd/snd.h"
#include "th03/common.h"
#include "th03/player/score.h"
#include "th03/chars/chars.hpp"
#include "th03/resident.hpp"
#include "th03/formats/cfg.h"

char debug = 0;
const cfg_options_t OPTS_DEFAULT = { SND_BGM_FM, KM_KEY_KEY, RANK_NORMAL };

#include "th02/formats/cfg_init.c"

#define LOGO \
	"東方夢時空用　 常駐プログラム　RES_YUME.com Version1.00       (c)zun 1997"

#define optimization_barrier_3()

#define RES_INIT_BOTTOM \
	cfg_init(sgm);

#include "th02/res_init.c"

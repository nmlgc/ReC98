/* ReC98
 * -----
 * 1st part of ZUN_RES.COM. Initializes the resident structure and
 * configuration file required in order to run TH02.
 */

#include <stddef.h>
#include "th02/th02.h"
#include "th02/snd/snd.h"

#pragma option -a1

char debug = 0;

void cfg_write(seg_t resident_sgm)
{
	static const huuma_options_t opts_default = {
		RANK_NORMAL, SND_BGM_FM, 3, 2, 0
	};
	static const char HUUMA_CFG[] = CFG_FN;

	const char *fn = HUUMA_CFG;
	huuma_options_t opts = opts_default;
	int handle = dos_axdx(0x3D02, fn);
	if(handle > 0) {
		dos_seek(handle, sizeof(opts), SEEK_SET);
	} else {
		handle = dos_create(fn, _A_ARCH);
		dos_write(handle, &opts, sizeof(opts));
	}
	dos_write(handle, &resident_sgm, sizeof(resident_sgm));
	dos_write(handle, &debug, sizeof(debug));
	dos_close(handle);
}

#define LOGO \
	"東方封魔録用　 常駐プログラム　ZUN_RES.com Version1.01       (c)zun 1997"

int main(int argc, const char **argv)
{
	int pascal scoredat_verify(void);

	seg_t sgm;
	const char *res_id = RES_ID;
	int i;
	char far *resident;

	sgm = resdata_exist(res_id, RES_ID_STRLEN, RES_PARASIZE);
	dos_puts2("\n\n" LOGO "\n");
	graph_clear();
	if(scoredat_verify() == 1) {
		dos_puts2("ハイスコアファイルがおかしいの、もう一度実行してね。\n");
		return 1;
	}
	if(argc == 2) {
		#define arg1_is(capital, small) \
			(argv[1][0] == '-' || argv[1][0] == '/') \
			&& (argv[1][1] == (capital) || argv[1][1] == (small))
		if(arg1_is('R', 'r')) {
			if(!sgm) {
				dos_puts2("わたし、まだいませんよぉ\n\n");
				return 1;
			}
			dos_free(sgm);
			dos_puts2("さよなら、また会えたらいいな\n\n");
			return 0;
		} else if(arg1_is('D', 'd')) {
			debug = 1;
		} else {
			dos_puts2("そんなオプション付けられても、困るんですけど\n\n");
			sgm = sgm; /* optimization barrier #1 */
			return 1;
		}
	}
	if(sgm) {
		dos_puts2("わたし、すでにいますよぉ\n\n");
		argv = argv; /* optimization barrier #2 */
		return 1;
	}
	sgm = resdata_create(res_id, RES_ID_STRLEN, RES_PARASIZE);
	if(!sgm) {
		dos_puts2("作れません、わたしの居場所がないの！\n\n");
		return 1;
	}
	resident = MK_FP(sgm, 0);
	dos_puts2("それでは、よろしくお願いします\n\n");
	for(i = offsetof(resident_t, stage); i < sizeof(resident_t); i++) {
		resident[i] = 0;
	}
	cfg_write(sgm);
	return 0;
}

#pragma codestring "\x00"

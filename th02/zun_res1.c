/* ReC98
 * -----
 * 1st part of ZUN_RES.COM. Initializes the resident structure and
 * configuration file required in order to run TH02, and verifies HUUHI.DAT.
 */

#pragma inline

#include <stddef.h>
#include "th02/th02.h"

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

int main(int argc, const char **argv)
{
	int pascal scoredat_verify(void);

	static const char MIKOConfig[] = RES_ID;
	static const char LOGO[] =
		"\n"
		"\n"
		"東方封魔録用　 常駐プログラム　ZUN_RES.com Version1.01       (c)zun 1997\n";
	static const char ERROR_SCOREDAT[] =
		"ハイスコアファイルがおかしいの、もう一度実行してね。\n";
	static const char ERROR_NOT_RESIDENT[] =
		"わたし、まだいませんよぉ\n\n";
	static const char REMOVED[] =
		"さよなら、また会えたらいいな\n\n";
	static const char ERROR_UNKNOWN_OPTION[] =
		"そんなオプション付けられても、困るんですけど\n\n";
	static const char ERROR_ALREADY_RESIDENT[] =
		"わたし、すでにいますよぉ\n\n";
	static const char ERROR_OUT_OF_MEMORY[] =
		"作れません、わたしの居場所がないの！\n\n";
	static const char INITIALIZED[] =
		"それでは、よろしくお願いします\n\n";

	seg_t sgm;
	const char *res_id = MIKOConfig;
	int i;
	char far *resident;

	sgm = resdata_exist(res_id, RES_ID_STRLEN, RES_PARASIZE);
	dos_puts2(LOGO);
	graph_clear();
	// No, I tried all permutations of command-line switches,
	// gotos and returns, and no pure C solution seems to work!
	if(scoredat_verify() == 1) __asm {
		push offset ds:ERROR_SCOREDAT
		jmp error_puts
	}
	if(argc == 2) {
		#define arg1_is(capital, small) \
			(argv[1][0] == '-' || argv[1][0] == '/') \
			&& (argv[1][1] == (capital) || argv[1][1] == (small))
		if(arg1_is('R', 'r')) {
			if(!sgm) {
				dos_puts2(ERROR_NOT_RESIDENT);
asm				jmp error_ret
			}
			dos_free(sgm);
			dos_puts2(REMOVED);
			return 0;
		} else if(arg1_is('D', 'd')) {
			debug = 1;
		} else {
			dos_puts2(ERROR_UNKNOWN_OPTION);
			return 1;
		}
	}
	if(sgm) {
		dos_puts2(ERROR_ALREADY_RESIDENT);
		return 1;
	}
	sgm = resdata_create(res_id, RES_ID_STRLEN, RES_PARASIZE);
	if(!sgm) {
asm		push offset ds:ERROR_OUT_OF_MEMORY
error_puts:
asm		call near ptr dos_puts2
error_ret:
		return 1;
	}
	resident = MK_FP(sgm, 0);
	dos_puts2(INITIALIZED);
	for(i = offsetof(resident_t, stage); i < sizeof(resident_t); i++) {
		resident[i] = 0;
	}
	cfg_write(sgm);
	return 0;
}

#pragma codestring "\x00"

#pragma option -O- -k-

extern char rank;
scoredat_section_t hi;

void pascal scoredat_recreate(void);
void pascal near scoredat_load(void);

unsigned char unused_1 = 0;
const char *SCOREDAT_FN = "huuhi.dat";
unsigned char g_name_first_sum = 0;
unsigned char stage_sum = 0;
unsigned char unused_2 = 0;
long points_sum = 0;
long score_sum = 0;

int pascal scoredat_verify(void)
{
	if(!file_exist(SCOREDAT_FN)) {
		scoredat_recreate();
	} else {
		for(rank = 0; rank < RANK_COUNT; rank++) {
			register int unused;
			register int i;

			scoredat_load();
			_AL = 0;
			g_name_first_sum = _AL;
			stage_sum = _AL;
			_AX = 0;
			asm {
				mov word ptr points_sum + 0, ax
				mov word ptr points_sum + 2, ax
				mov word ptr score_sum + 0, ax
				mov word ptr score_sum + 2, ax
			}
			for(i = 0; i < sizeof(hi.score); i++) {
				score_sum += *((unsigned char*)(&hi.score) + i);
			}
			for(i = 0; i < SCOREDAT_PLACES; i++) {
				points_sum += hi.score.points[i];
				g_name_first_sum += hi.score.g_name[i][0];
				stage_sum += hi.score.stage[i];
			}
			if(
				points_sum != hi.score.points_sum
				|| g_name_first_sum != hi.score.g_name_first_sum
				|| stage_sum != hi.score.stage_sum
				|| score_sum != hi.score_sum
			) {
				goto delete;
			}
		}
	}
	return 0;
delete:
	file_delete(SCOREDAT_FN);
	return 1;
}

#pragma codestring "\x90"

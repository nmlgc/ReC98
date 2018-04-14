#include <stdio.h>
#include <dir.h>
#include <dos.h>

struct {
	const char path[13*3]; // up to 2 subdirectories
	const char symbol[10]; // filename + optional number
} paths[] = {
	{"libs/kaja/ongchk.com", "ONGCHK"},
	{"bin/th01/zunsoft.com", "ZUNSOFT"},
	{"bin/th02/zuninit.com", "ZUNINIT2"},
	{"bin/th02/zun_res.com", "ZUN_RES"},
	{"bin/th03/zunsp.com", "ZUNSP"},
	{"bin/th03/res_yume.com", "RES_YUME"},
	{"bin/th04/zuninit.com", "ZUNINIT4"},
	{"bin/th04/res_huma.com", "RES_HUMA"},
	{"bin/th04/memchk.com", "MEMCHK4"},
	{"bin/th05/zuninit.com", "ZUNINIT5"},
	{"bin/th05/res_kso.com", "RES_KSO"},
	{"bin/th05/gjinit.com", "GJINIT"},
	{"bin/th05/memchk.com", "MEMCHK5"},
};
#define PATHS_COUNT (sizeof(paths)/sizeof(paths[0]))
#define SYMBOL_PREFIX "GENSIZE_"

int main() {
	struct ffblk ff;
	int i;
	for(i=0;i<PATHS_COUNT;i++) {
		if(!findfirst(paths[i].path,&ff,FA_NORMAL)) {
			printf(SYMBOL_PREFIX "%s=%ld\n",paths[i].symbol,ff.ff_fsize);
		}
	}
	return 0;
}

#ifndef ERROR_NOT_RESIDENT
# define ERROR_NOT_RESIDENT "わたし、まだいませんよぉ"
#endif
#ifndef REMOVED
# define REMOVED "さよなら、また会えたらいいな"
#endif
#ifndef INITIALIZED
# define INITIALIZED "それでは、よろしくお願いします"
#endif

int main(int argc, const unsigned char **argv)
{
	seg_t sgm;
#if GAME == 5
	int i;
	resident_t far *resident;
	char far *resident_bytes;
	const char *res_id = RES_ID;
#else
	const char *res_id = RES_ID;
	int i;
	char far *resident_bytes;
#endif

	sgm = resdata_exist(res_id, RES_ID_STRLEN, RES_PARASIZE);
	dos_puts2("\n\n" LOGO "\n");
	graph_clear();
#ifdef RES_INIT_TOP
	RES_INIT_TOP;
#endif
	if(argc == 2) {
		#define arg1_is(capital, small) \
			(argv[1][0] == '-' || argv[1][0] == '/') \
			&& (argv[1][1] == (capital) || argv[1][1] == (small))
		if(arg1_is('R', 'r')) {
			if(!sgm) {
				dos_puts2(ERROR_NOT_RESIDENT "\n\n");
				return 1;
			}
			dos_free(sgm);
			dos_puts2(REMOVED "\n\n");
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
		optimization_barrier_3();
		return 1;
	}
	resident_bytes = (char far *)MK_FP(sgm, 0);
	dos_puts2(INITIALIZED "\n\n");
	for(i = (RES_ID_STRLEN + 1); i < sizeof(resident_t); i++) {
		resident_bytes[i] = 0;
	}
	RES_INIT_BOTTOM;
	return 0;
}

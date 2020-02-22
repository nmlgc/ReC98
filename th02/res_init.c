int main(int argc, const unsigned char **argv)
{
	seg_t sgm;
	const char *res_id = RES_ID;
	int i;
	char far *resident_bytes;

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
	resident_bytes = (char far *)MK_FP(sgm, 0);
	dos_puts2("それでは、よろしくお願いします\n\n");
	for(i = (RES_ID_STRLEN + 1); i < sizeof(resident_t); i++) {
		resident_bytes[i] = 0;
	}
	cfg_init(sgm);
#ifdef RES_INIT_BOTTOM
	RES_INIT_BOTTOM;
#endif
	return 0;
}

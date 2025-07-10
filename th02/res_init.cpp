#include "libs/master.lib/pc98_gfx.hpp"

#ifndef ERROR_NOT_RESIDENT
#define ERROR_NOT_RESIDENT "わたし、まだいませんよぉ"
#endif
#ifndef REMOVED
#define REMOVED "さよなら、また会えたらいいな"
#endif
#ifndef INITIALIZED
#define INITIALIZED "それでは、よろしくお願いします"
#endif

#define arg_is(arg, capital, small) \
	((arg[0] == '-'    ) || (arg[0] == '/'  )) && \
	((arg[1] == capital) || (arg[1] == small))

int main(int argc, const unsigned char **argv)
{
	resident_t __seg *seg;
#if (GAME == 5)
	int i;
	resident_t far *resident;
	uint8_t far *resident_bytes;
	const char *res_id = RES_ID;
#else
	const char *res_id = RES_ID;
	int i;
	uint8_t far *resident_bytes;
#endif

	seg = ResData<resident_t>::exist_with_id_from_pointer(res_id);
	dos_puts2("\n\n" LOGO "\n");
	graph_clear();
#ifdef RES_INIT_TOP
	RES_INIT_TOP;
#endif
	if(argc == 2) {
		if(arg_is(argv[1], 'R', 'r')) {
			if(!seg) {
				dos_puts2(ERROR_NOT_RESIDENT "\n\n");
				return 1;
			}
			dos_free(seg);
			dos_puts2(REMOVED "\n\n");
			return 0;
		} else if(arg_is(argv[1], 'D', 'd')) {
			debug = 1;
		} else {
			dos_puts2("そんなオプション付けられても、困るんですけど\n\n");
			seg = seg; /* optimization barrier #1 */
			return 1;
		}
	}
	if(seg) {
		dos_puts2("わたし、すでにいますよぉ\n\n");
		argv = argv; /* optimization barrier #2 */
		return 1;
	}
	seg = ResData<resident_t>::create_with_id_from_pointer(res_id);
	if(!seg) {
		dos_puts2("作れません、わたしの居場所がないの！\n\n");
		optimization_barrier();
		return 1;
	}
	resident_bytes = reinterpret_cast<uint8_t far *>(seg);
	dos_puts2(INITIALIZED "\n\n");
	for(i = (ResData<resident_t>::id_len() + 1); i < sizeof(resident_t); i++) {
		resident_bytes[i] = 0;
	}
	RES_INIT_BOTTOM;
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "zuncom/common.h"
static const char copyright[] = "comcstm (c)O.Morikawa 1996";
#define HEADER_SIZE (3+2+2+2+4+sizeof(copyright)-1)
int main(int argc, char **argv) {
	FILE *fo;
	long sz_usage, sz_program;
	int tmp;
	if(argc != 6) {
		printf("Usage: comcstm usage.txt prog.com cstmstub.bin timestamp output.com\n");
		return 1;
	}

	sz_usage = filesize(argv[1]);
	if(sz_usage == -1) return 3;
	sz_program = filesize(argv[2]);
	if(sz_program == -1) return 3;
	fo = fopen(argv[5], "wb");
	if(!fo) {
		printf("Error: couldn't open file '%s': %s\n", argv[5], strerror(errno));
		return 2;
	}

	fputc('\xE9', fo); /* jmp rel16 */
	fputw(0x100 + HEADER_SIZE + sz_usage + sz_program - 0x103, fo);
	fputw(0x100 + HEADER_SIZE, fo); /* 103: usage offset */
	fputw(sz_usage, fo); /* 105: usage size */
	fputw(sz_program, fo); /* 107: program size */
	/* 109: looks like an msdos timestamp */
	/* th04: 0x25098623 = 621381155 */
	/* th05: 0x2579AF64 = 628731748 */
	fputd(atol(argv[4]), fo);
	fputs(copyright, fo);
	fflush(fo);
	if(append(argv[1], fo) || append(argv[2], fo) || append(argv[3], fo)) {
		fclose(fo);
		return 3;
	}
	if(fclose(fo)) {
		printf("Error while closing outfile\n");
		return 4;
	}
	return 0;
}

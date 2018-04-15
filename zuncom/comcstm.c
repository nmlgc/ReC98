#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <dir.h>
#include <dos.h>

long filesize(const char *filename) {
	struct ffblk ff;
	if(!findfirst(filename,&ff,FA_NORMAL)) {
		return ff.ff_fsize;
	}
	else {
		printf("Error: couldn't find '%s'\n",filename);
		exit(3);
		return -1;
	}
}

void append(const char *filename, FILE *fo) {
	FILE *fi;
	static char cluster[512];
	int bytesread, byteswrite;
	fi = fopen(filename, "rb");
	if(!fi) {
		printf("Error: couldn't open file '%s': %s\n", filename, strerror(errno));
		fclose(fo);
		exit(2);
	}
	while(!feof(fi)) {
		bytesread = fread(cluster, 1, sizeof(cluster), fi);
		if(bytesread) {
			byteswrite = fwrite(cluster, 1, bytesread, fo);
			if(bytesread != byteswrite) {
				printf("Error: write error\n");
				fclose(fi);
				fclose(fo);
				exit(5);
			}
		}
	}
	fclose(fi);
}

void fputw(int word, FILE *fo) {
	fwrite(&word, sizeof(word), 1, fo);
}
void fputd(long dword, FILE *fo) {
	fwrite(&dword, sizeof(dword), 1, fo);
}
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
	sz_program = filesize(argv[2]);
	fo = fopen(argv[5], "wb");
	if(!fo) {
		printf("Error: couldn't open file '%s': %s\n", argv[5], strerror(errno));
		return 4;
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
	append(argv[1], fo);
	append(argv[2], fo);
	append(argv[3], fo);
	fclose(fo);
	return 0;
}

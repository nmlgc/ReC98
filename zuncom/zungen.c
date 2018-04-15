#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <dir.h>
#include "zuncom/common.h"
int readline(char *path, size_t size, FILE* fl) {
	char *pathp;
	if(!fgets(path, size, fl)) return 1;
	if(*path) {
		pathp = path+strlen(path)-1;
		if(*pathp == '\n') *pathp = '\0';
	}
	return 0;
}
#define MAX_COUNT 32
#define DATA_SIZE (2+MAX_COUNT*10+2+3)
static const char moveup[] = {
	0xF3, 0xA4,       /* REP MOVSB    */
	0x58,             /* POP AX       */
	0xB8, 0x00, 0x01, /* MOV AX, 100h */
	0x50,             /* PUSH AX      */
	0xC3,             /* RETN         */
};
int main(int argc, char** argv) {
	static char path[MAXPATH+1];
	static char names[8*MAX_COUNT];
	static int entries[MAX_COUNT+1];
	FILE *fl, *fo;
	int count;
	int size, stubsize;
	int pathpos;
	int i,j;
	int errval;

	if(argc != 4) {
		printf("Usage: zungen zun_stub.bin listfile.txt outfile.bin\n");
		return 1;
	}
	fl = fopen(argv[2],"r");
	if(!fl) {
		printf("Error: couldn't open listfile: %s\n", strerror(errno));
		return 2;
	}
	fo = fopen(argv[3],"wb");
	if(!fo) {
		fclose(fl);
		printf("Error: couldn't open outfile: %s\n", strerror(errno));
		return 3;
	}

	/* read proc count */
	if(readline(path, sizeof(path), fl)) {
		errval = 4; goto err;
	}
	count = atoi(path);
	if(count < 0 || count > MAX_COUNT) {
		printf("Error: count is too big!\n");
		errval = 5; goto err;
	}

	/* write stub and proc count */
	append(argv[1], fo);
	fputw(count, fo);

	/* read proc names */
	memset(names, ' ', sizeof(names));
	for(i=0;i<count;i++) {
		if(readline(path, sizeof(path), fl)) {
			errval = 6; goto err;
		}
		for(j=0;j<8;j++) {
			if(path[j] == 0) {
				break;
			}
			names[j+i*8] = path[j];
		}
	}

	/* write proc names */
	if(sizeof(names) != fwrite(names, 1, sizeof(names), fo)) {
		printf("Error: write error\n");
		errval = 7; goto err;
	}

	/* save list file position for later */
	pathpos = ftell(fl);

	/* calc offset of first entry */
	stubsize = size = filesize(argv[1]);
	if(size == -1) {
		errval = 8; goto err;
	}
	size += DATA_SIZE + 0x100;

	/* build entry table */
	memset(entries, 0, sizeof(entries));
	for(i=0;i<count;i++) {
		entries[i] = size;
		if(readline(path, sizeof(path), fl)) {
			errval = 9; goto err;
		}
		j = filesize(path);
		if(j == -1) { errval = 10; goto err; }
		size += j;
	}
	entries[i] = size;

	/* write entry table */
	if(sizeof(entries) != fwrite(entries, 1, sizeof(entries), fo)) {
		printf("Error: write error\n");
		errval = 11; goto err;
	}

	/* write moveup_indirect */
	fputc('\xE8', fo); /* call rel16 */
	fputw(size - (stubsize + DATA_SIZE + 0x100), fo);

	/* append com files */
	fseek(fl, pathpos, SEEK_SET);
	for(i=0;i<count;i++) {
		if(readline(path, sizeof(path), fl)) {
			errval = 12; goto err;
		}
		if(append(path, fo)) {
			errval = 13; goto err;
		}
	}

	/* append moveup */
	if(sizeof(moveup) != fwrite(moveup, 1, sizeof(moveup), fo)) {
		printf("Error: write error\n");
		errval = 14; goto err;
	}

	fclose(fl);
	if(fclose(fo)) {
		printf("Error: unsuccessful close\n");
		return 15;
	}
	return 0;
err:
	fclose(fl);
	fclose(fo);
	return errval;
}

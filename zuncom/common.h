#ifndef COMMON_H_
#define COMMON_H_
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dir.h>
#include <dos.h>

long filesize(const char *filename) {
	struct ffblk ff;
	if(!findfirst(filename,&ff,FA_NORMAL)) {
		return ff.ff_fsize;
	}
	else {
		printf("Error: couldn't find '%s'\n",filename);
		return -1;
	}
}

int append(const char *filename, FILE *fo) {
	FILE *fi;
	static char cluster[512];
	int bytesread, byteswrite;
	fi = fopen(filename, "rb");
	if(!fi) {
		printf("Error: couldn't open file '%s': %s\n", filename, strerror(errno));
		return 1;
	}
	while(!feof(fi)) {
		bytesread = fread(cluster, 1, sizeof(cluster), fi);
		if(bytesread) {
			byteswrite = fwrite(cluster, 1, bytesread, fo);
			if(bytesread != byteswrite) {
				printf("Error: write error\n");
				fclose(fi);
				return 1;
			}
		}
	}
	fclose(fi);
	fflush(fo);
	return 0;
}

void fputw(int word, FILE *fo) {
	fwrite(&word, sizeof(word), 1, fo);
}
void fputd(long dword, FILE *fo) {
	fwrite(&dword, sizeof(dword), 1, fo);
}

#endif

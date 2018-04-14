#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <dir.h>

int main(int argc, char** argv) {
	static char path[MAXPATH+1];
	static char cluster[512];

	FILE *fl, *fi, *fo;
	size_t bytesread,byteswrite;
	char *pathp;

	if(argc != 3) {
		printf("Usage: copycat listfile.txt outfile.bin\n");
		return 1;
	}
	fl = fopen(argv[1],"r");
	if(!fl) {
		printf("Error: couldn't open listfile: %s\n", strerror(errno));
		return 2;
	}
	fo = fopen(argv[2],"wb");
	if(!fo) {
		fclose(fl);
		printf("Error: couldn't open outfile: %s\n", strerror(errno));
		return 3;
	}
	
	for(;!feof(fl);) {
		if(!fgets(path, sizeof(path), fl)) break;
		if(*path) {
			pathp = path+strlen(path)-1;
			if(*pathp == '\n') *pathp = '\0';
		}
		if(*path) {
			fi = fopen(path, "rb");
			if(!fi) {
				fclose(fo);
				fclose(fl);
				printf("Error: couldn't open inputfile '%s': %s", path, strerror(errno));
				return 4;
			}
			while(!feof(fi)) {
				bytesread = fread(cluster, 1, sizeof(cluster), fi);
				if(bytesread) {
					byteswrite = fwrite(cluster, 1, bytesread, fo);
					if(byteswrite != bytesread) {
						fclose(fi);
						fclose(fo);
						fclose(fl);
						printf("Error: write error\n");
						return 5;
					}
				}
			}
			fclose(fi);
			fflush(fo);
		}
	}
	fclose(fl);
	if(fclose(fo)) {
		printf("Error: unsuccessful close\n");
		return 6;
	}
	return 0;
}

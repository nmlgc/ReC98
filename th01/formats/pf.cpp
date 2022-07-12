/* ReC98
 * -----
 * C++ reimplementation of master.lib's PAR packfile format, including the
 * modifications for TH01
 */

extern "C" {

#include <ctype.h>
#include <io.h>
#include "platform.h"
#include "master.hpp"
#include "th01/formats/pf.hpp"

#undef arc_file_get

#define FILE_COUNT 64
#define CACHE_SIZE 0x100

typedef struct {
	char type[2]; // �� if RLE-compressed
	char aux; // Always 3, unused
	char fn[PF_FN_LEN];
	int32_t packsize;
	int32_t orgsize;
	int32_t offset; // of the file data within the entire archive
	int32_t reserved; // Always zero
} pf_header_t;

pf_header_t *arc_pfs;
pf_header_t *file_pf;
int cur_file_id;
int arc_pf_count;
char file_compressed;
char arc_key;

char *file_data;
char *cache;
char arc_fn[PF_FN_LEN];
unsigned int file_pos;
unsigned int cache_bytes_read;

void pascal arc_load(const char fn[PF_FN_LEN])
{
	int i, c;

	arc_pfs = new pf_header_t[FILE_COUNT];
	file_ropen(fn);
	for(i = 0; i < PF_FN_LEN; i++) {
		arc_fn[i] = fn[i];
		if(fn[i] == 0) {
			break;
		}
	}
	file_read(arc_pfs, sizeof(pf_header_t) * FILE_COUNT);
	file_close();
	for(i = 0; i < FILE_COUNT; i++) {
		if(arc_pfs[i].type[0] == 0) {
			break;
		}
		for(c = 0; c < PF_FN_LEN; c++) {
			if(arc_pfs[i].fn[c] == 0) {
				break;
			}
			arc_pfs[i].fn[c] = ~arc_pfs[i].fn[c];
		}
	}
	arc_pf_count = i;
}

void pascal arc_free(void)
{
	delete[] arc_pfs;
}

int pascal near at_pos_of(const char fn[PF_FN_LEN])
{
	int i;
	for(i = 0; i < PF_FN_LEN; i++) {
		if(arc_pfs[cur_file_id].fn[i] != toupper(fn[i])) {
			return 0;
		}
		if(fn[i] == 0) {
			return 1;
		}
	}
	return 0;
}

// Get it? En*crap*tion?
void pascal near crapt(char *buf, size_t size)
{
	size_t i;
	for(i = 0; i < size; i++) {
		buf[i] ^= arc_key;
	}
}

unsigned char pascal near cache_next(void)
{
	char b;
	if(cache_bytes_read == 0) {
		file_read(cache, CACHE_SIZE);
	}
	b = cache[cache_bytes_read];
	b ^= arc_key;
	cache_bytes_read++;
	if(cache_bytes_read >= CACHE_SIZE) {
		cache_bytes_read = 0;
	}
	return b;
}

void pascal near unrle(unsigned int input_size)
{
	unsigned char var_1;
	unsigned char runs;
	unsigned char var_3;
	long bytes_read = 0;
	long bytes_written = 0;
	#define NEXT() \
		cache_next(); \
		bytes_read++;
	var_3 = NEXT();
	while(input_size > bytes_read) {
		do {
			file_data[bytes_written] = var_3;
			var_1 = var_3;
			bytes_written++;
			var_3 = NEXT();
		} while(var_1 != var_3);
		file_data[bytes_written] = var_3;
		while(1) {
			bytes_written++;
			runs = NEXT();
			while(runs > 0) {
				file_data[bytes_written] = var_1;
				bytes_written++;
				runs--;
			}
			var_3 = NEXT();
			if(var_3 != var_1) {
				break;
			}
			file_data[bytes_written] = var_1;
		}
	}
	#undef NEXT()
}

void pascal arc_file_load(const char fn[PF_FN_LEN])
{
	const char rle_type[] = {"��"};
	int i;

	cur_file_id = 0;
	for(i = 0; i < arc_pf_count; i++) {
		if(at_pos_of(fn)) {
			break;
		}
		cur_file_id++;
	}
	file_pf = &arc_pfs[cur_file_id];
	file_ropen(arc_fn);
	file_seek(file_pf->offset, SEEK_SET);
	if(file_pf->type[0] == rle_type[0] && file_pf->type[1] == rle_type[1]) {
		file_compressed = 1;
	} else {
		file_compressed = 0;
	}
	file_pos = 0;
	file_data = new char[file_pf->orgsize];
	if(file_compressed) {
		cache = new char[CACHE_SIZE];
		cache_bytes_read = 0;
		unrle(file_pf->packsize);
		delete[] cache;
	} else {
		file_read(file_data, file_pf->packsize);
		crapt(file_data, file_pf->packsize);
	}
	file_close();
}

void pascal arc_file_get(char *buf, size_t size)
{
	char *p = buf;
	size_t i;
	for(i = 0; i < size; i++) {
		if(file_pos >= file_pf->orgsize) {
			break;
		}
		p[i] = file_data[file_pos];
		file_pos++;
	}
}

void pascal arc_file_seek(char pos)
{
	file_pos = pos;
}

void pascal arc_file_free(void)
{
	delete[] file_data;
}

int pascal arc_file_size(void)
{
	return file_pf->orgsize;
}

}

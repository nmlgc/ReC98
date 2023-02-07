/* ReC98
 * -----
 * C++ reimplementation of master.lib's PAR packfile format, including the
 * modifications for TH01
 */

#include <ctype.h>
#include <io.h>
#include "platform.h"
#include "master.hpp"
#include "th01/formats/pf.hpp"

#undef arc_file_get

static const int FILE_COUNT = 64;
static const size_t CACHE_SIZE = 0x100;

#define PF_TYPE_COMPRESSED "\x95\x95" // "封" in Shift-JIS

typedef struct {
	uint8_t type[2]; // PF_TYPE_COMPRESSED if RLE-compressed
	int8_t aux; // Always 3, unused
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
bool file_compressed;
uint8_t arc_key;

uint8_t *file_data;
uint8_t *cache;
char arc_fn[PF_FN_LEN];
size_t file_pos;
size_t cache_bytes_read;

void pascal arc_load(const char fn[PF_FN_LEN])
{
	int i;
	int c;

	arc_pfs = new pf_header_t[FILE_COUNT];
	file_ropen(fn);
	for(i = 0; i < PF_FN_LEN; i++) {
		arc_fn[i] = fn[i];
		if(fn[i] == '\0') {
			break;
		}
	}
	file_read(arc_pfs, (sizeof(pf_header_t) * FILE_COUNT));
	file_close();
	for(i = 0; i < FILE_COUNT; i++) {
		if(arc_pfs[i].type[0] == 0) {
			break;
		}
		for(c = 0; c < PF_FN_LEN; c++) {
			if(arc_pfs[i].fn[c] == '\0') {
				break;
			}
			arc_pfs[i].fn[c] = ~arc_pfs[i].fn[c];
		}
	}
	arc_pf_count = i;
}

void arc_free(void)
{
	delete[] arc_pfs;
}

bool16 pascal near at_pos_of(const char fn[PF_FN_LEN])
{
	for(int i = 0; i < PF_FN_LEN; i++) {
		if(arc_pfs[cur_file_id].fn[i] != toupper(fn[i])) {
			return false;
		}
		if(fn[i] == '\0') {
			return true;
		}
	}
	return false;
}

// Get it? En*crap*tion?
void pascal near crapt(uint8_t *buf, size_t size)
{
	for(size_t i = 0; i < size; i++) {
		buf[i] ^= arc_key;
	}
}

uint8_t pascal near cache_next_raw(void)
{
	uint8_t b;
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

inline void near cache_next(uint8_t& ret, long& bytes_read) {
	ret = cache_next_raw();
	bytes_read++;
}

void pascal near unrle(size_t input_size)
{
	uint8_t var_1;
	uint8_t runs;
	uint8_t var_3;
	long bytes_read = 0;
	long bytes_written = 0;
	cache_next(var_3, bytes_read);
	while(input_size > bytes_read) {
		do {
			var_1 = file_data[bytes_written++] = var_3;
			cache_next(var_3, bytes_read);
		} while(var_1 != var_3);
		file_data[bytes_written++] = var_3;
		while(1) {
			cache_next(runs, bytes_read);
			while(runs > 0) {
				file_data[bytes_written++] = var_1;
				runs--;
			}
			cache_next(var_3, bytes_read);
			if(var_3 != var_1) {
				break;
			}
			file_data[bytes_written++] = var_1;
		}
	}
}

void pascal arc_file_load(const char fn[PF_FN_LEN])
{
	const uint8_t rle_type[] = PF_TYPE_COMPRESSED;

	cur_file_id = 0;
	for(int i = 0; i < arc_pf_count; i++) {
		if(at_pos_of(fn)) {
			break;
		}
		cur_file_id++;
	}
	file_pf = &arc_pfs[cur_file_id];
	file_ropen(arc_fn);
	file_seek(file_pf->offset, SEEK_SET);
	if((file_pf->type[0] == rle_type[0]) && (file_pf->type[1] == rle_type[1])) {
		file_compressed = true;
	} else {
		file_compressed = false;
	}
	file_pos = 0;
	file_data = new uint8_t[file_pf->orgsize];
	if(file_compressed) {
		cache = new uint8_t[CACHE_SIZE];
		cache_bytes_read = 0;
		unrle(file_pf->packsize);
		delete[] cache;
	} else {
		file_read(file_data, file_pf->packsize);
		crapt(file_data, file_pf->packsize);
	}
	file_close();
}

void pascal arc_file_get(uint8_t *buf, size_t size)
{
	uint8_t *p = buf;
	for(size_t i = 0; i < size; i++) {
		if(file_pos >= file_pf->orgsize) {
			break;
		}
		p[i] = file_data[file_pos];
		file_pos++;
	}
}

void pascal arc_file_seek(int8_t pos)
{
	file_pos = pos;
}

void arc_file_free(void)
{
	delete[] file_data;
}

int arc_file_size(void)
{
	return file_pf->orgsize;
}

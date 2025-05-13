/// C++ reimplementation of master.lib's PAR packfile format, including the
/// modifications for TH01
/// --------------------------------------------------------------------------

#include <ctype.h>
#include "libs/master.lib/master.hpp"
#include "th01/formats/pf.hpp"

#undef arc_file_get

static const int FILE_COUNT = 64;
static const size_t CACHE_SIZE = 0x100;

#define PF_TYPE_COMPRESSED "\x95\x95" // "封" in Shift-JIS

struct pf_header_t {
	uint8_t type[2]; // PF_TYPE_COMPRESSED if RLE-compressed
	int8_t aux; // Always 3, unused
	char fn[PF_FN_LEN];
	int32_t packsize;
	int32_t orgsize;
	int32_t offset; // of the file data within the entire archive
	int32_t reserved; // Always zero
};

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

void arc_load(const char fn[PF_FN_LEN])
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

bool16 near at_pos_of(const char fn[PF_FN_LEN])
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
void near crapt(uint8_t *buf, size_t size)
{
	for(size_t i = 0; i < size; i++) {
		buf[i] ^= arc_key;
	}
}

uint8_t near cache_next(void)
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

void near unrle(size_t output_size)
{
	// Simple run-length encoding scheme, compressing runs of three or more
	// identical bytes by replacing arbitrarily many bytes after the third one
	// with a run count. The decompressor always enters run mode after two
	// identical characters; to just output two, run mode must be immediately
	// left by specifying a run length of 0.
	//
	//   Compressed: "zz\x02z\x01yy\x00"
	// Decompressed: "zzzzzzyy"
	//  Explanation: • "zz" (new run)
	//               • 2 more
	//               • "z" (continue run)
	//               • 1 more
	//               • "y" (stop run)
	//               • "y" (new run)
	//               • 0 more

	size_t bytes_written = 0;
	uint8_t run_byte;
	uint8_t next_byte = cache_next();
	uint8_t runs = 0;

	while(bytes_written < output_size) {
		file_data[bytes_written++] = next_byte;

		if(runs == 0) {
			// Literal mode
			run_byte = next_byte;
			next_byte = cache_next();
			if(run_byte == next_byte) {
				runs = cache_next();
			}
		} else {
			// Run mode
			runs--;
		}
	}
}

void arc_file_load(const char fn[PF_FN_LEN])
{
	const uint8_t rle_type[] = PF_TYPE_COMPRESSED;

	cur_file_id = 0;
	for(int i = 0; i < arc_pf_count; i++) {
		if(at_pos_of(fn)) {
			break;
		}
		cur_file_id++;
	}

	// ZUN landmine: Will access the array out of bounds if the file doesn't
	// exist.
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
		unrle(file_pf->orgsize);
		delete[] cache;
	} else {
		file_read(file_data, file_pf->packsize);
		crapt(file_data, file_pf->packsize);
	}
	file_close();
}

void arc_file_get(uint8_t *buf, size_t size)
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

void arc_file_seek(int8_t pos)
{
	file_pos = pos;
}

void arc_file_free(void)
{
	delete[] file_data;
}

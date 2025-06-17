/// C++ reimplementation of master.lib's PAR packfile format, including the
/// modifications for TH01
/// --------------------------------------------------------------------------

#include <ctype.h>
#include "libs/master.lib/master.hpp"
#include "th01/formats/pf.hpp"
#include "platform/array.hpp"

#undef arc_file_read

static const int FILE_COUNT = 64;

static const uint16_t PF_TYPE_COMPRESSED = 0x9595; // "封" in Shift-JIS

struct pf_header_t {
	uint16_t type; // PF_TYPE_COMPRESSED if RLE-compressed
	int8_t aux; // Always 3, unused
	char fn[PF_FN_LEN];
	int32_t packsize;
	int32_t orgsize;
	int32_t offset; // of the file data within the entire archive
	int32_t reserved; // Always zero
};

pf_header_t *arc_pfs;
pf_header_t *file_pf;
int arc_pf_count;
bool file_compressed;
uint8_t arc_key;

Array<uint8_t, 0x100> cache;
char arc_fn[PF_FN_LEN];
size_t file_pos;
size_t cache_bytes_read;

uint8_t rle_runs;
uint8_t rle_next_byte;
uint8_t rle_run_byte;

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
		if(static_cast<uint8_t>(arc_pfs[i].type) == 0) {
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

bool near arc_file_lookup(const char fn[PF_FN_LEN])
{
	file_pf = arc_pfs;
	for(int file_i = 0; file_i < arc_pf_count; (file_i++, file_pf++)) {
		for(int i = 0; i < PF_FN_LEN; i++) {
			if(file_pf->fn[i] != toupper(fn[i])) {
				break;
			}
			if(fn[i] == '\0') {
				return false;
			}
		}
	}
	file_pf = nullptr;
	return true;
}

// Get it? En*crap*tion?
void near crapt(uint8_t *buf, size_t size)
{
	for(size_t i = 0; i < size; i++) {
		buf[i] ^= arc_key;
	}
}

void near cache_refill(void)
{
	file_read(cache.data(), cache.count());
	cache_bytes_read = 0;
}

uint8_t near cache_next(void)
{
	if(cache_bytes_read >= cache.count()) {
		cache_refill();
	}
	return (cache[cache_bytes_read++] ^ arc_key);
}

void near unrle(uint8_t *buf, size_t output_size, int advance_buf)
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
	while(bytes_written < output_size) {
		*buf = rle_next_byte;
		bytes_written++;
		buf += advance_buf;

		if(rle_runs == 0) {
			// Literal mode
			rle_run_byte = rle_next_byte;
			rle_next_byte = cache_next();
			if(rle_run_byte == rle_next_byte) {
				rle_runs = cache_next();
			}
		} else {
			// Run mode
			rle_runs--;
		}
	}
}

void near arc_file_rewind(void)
{
	file_seek(file_pf->offset, SEEK_SET);
	file_pos = 0;
	if(file_compressed) {
		cache_refill();
		rle_runs = 0;
		rle_next_byte = cache_next();
	}
}

bool arc_file_open(const char fn[PF_FN_LEN])
{
	if(arc_file_lookup(fn)) {
		return true;
	}
	file_ropen(arc_fn);
	file_compressed = (file_pf->type == PF_TYPE_COMPRESSED);
	arc_file_rewind();
	return false;
}

size_t arc_file_read(uint8_t *buf, size_t size)
{
	const int delta = (file_pf->orgsize - file_pos);
	if(size > delta) {
		size = delta;
	}
	if(file_compressed) {
		unrle(buf, size, true);
	} else {
		file_read(buf, size);
		crapt(buf, size);
	}
	file_pos += size;
	return size;
}

size_t arc_file_seek(int pos, int dir)
{
	if(dir == SEEK_CUR) {
		pos += file_pos;
	}
	if(pos < 0) {
		pos = 0;
	} else if(pos > file_pf->orgsize) {
		pos = file_pf->orgsize;
	}
	if(file_compressed) {
		const int delta = (pos - file_pos);
		if(delta < 0) {
			// Seeking backwards in a compressed stream is awkward and rarely
			// if ever needed, so let's just rewind.
			arc_file_rewind();
			return arc_file_seek(pos, SEEK_SET);
		} {
			uint8_t temp;
			unrle(&temp, delta, false);
		}
	} else {
		file_seek((file_pf->offset + pos), SEEK_SET);
	}
	file_pos = pos;
	return pos;
}

void arc_file_close(void)
{
	file_close();
}

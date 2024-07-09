/// Broken C++ reimplementation of master.lib's PAR packfile format, including
/// the modifications for TH01
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
	// Simple run-length encoding scheme, compressing runs of three or more
	// identical bytes by replacing arbitrarily many bytes after the third one
	// with a run count. The decompressor always enters run mode after two
	// identical characters; to just output two, run mode must be immediately
	// left by specifying a run length of 0.
	//
	//   Compressed: "zz\x02z\x01yy\x00x"
	// Decompressed: "zzzzzzyy"
	//  Explanation: • "zz" (new run)
	//               • 2 more
	//               • "z" (continue run)
	//               • 1 more
	//               • "y" (stop run)
	//               • "y" (new run)
	//               • 0 more
	//               • (stop run; does *not* output "x" because we've read the
	//                 last input byte to determine that the run should stop?!)

	uint8_t literal_1;
	uint8_t runs;
	uint8_t literal_2;
	long bytes_read = 0;
	long bytes_written = 0;
	cache_next(literal_2, bytes_read);

	while(input_size > bytes_read) {
		// ZUN landmine: This inner loop ignores [input_size]. This causes
		// issues even with the compressed byte streams in the original
		// 東方靈異.伝 archive: BOSS1_3.BOS, for example, ends with the byte
		// sequence 3F FF F0 00, causing this inner loop, and decompression as
		// a whole, to continue into the adjacent BOSS2.BOS. At that point, the
		// outer loop only terminates after the first 0-byte run started by the
		// BOSS format signature (42 4F 53 53), overflowing the output buffer
		// by 4 bytes. The same happens with BOSS8_1.BOS, which ends in
		// 7F FF E0 00, and is followed by BOSS8_E1.BOS.
		//
		// This only does not immediately crash the game when loading SinGyoku
		// or Konngara thanks to two properties of Turbo C++'s 4.0J's C heap
		// implementation:
		//
		// • All allocated blocks are prefixed with a 4-byte linked list header
		//   in the same segment. Since the allocator wants to maintain a
		//   16-byte alignment for every block, the end of a block will be
		//   padded with (15 - (((4 + size + 15) / 16) * 16) % 16) bytes.
		// • That specific file is 28,864 bytes large. This is large enough for
		//   malloc() to place the buffer for the decompressed file at the end
		//   of the heap, with no buffer to overflow into. The 256-byte buffer
		//   for encoded file data is allocated afterwards, but it's small
		//   enough to be placed into an existing hole earlier on the heap.
		do {
			literal_1 = file_data[bytes_written++] = literal_2;
			cache_next(literal_2, bytes_read);
		} while(literal_1 != literal_2);
		file_data[bytes_written++] = literal_2; // Second byte of same-byte run

		// Run mode. [literal_1] == [literal_2] during the whole loop.
		// ZUN landmine: Still no check whether we've reached the end of the
		// input. Thankfully causes no further issues with the original data
		// beyond the previous ZUN bug: The two affected files are followed by
		// .BOS files, whose last two signature bytes (0x53, 0x53) are highly
		// unlikely to be followed by more 0x53 bytes.
		while(1) {
			cache_next(runs, bytes_read);
			while(runs > 0) {
				file_data[bytes_written++] = literal_1;
				runs--;
			}

			// Stay in run mode if the compressed stream continues with the
			// same byte. If it doesn't and we're about to read the last byte
			// from the stream, the new [literal_2] is never written to the
			// decompressed buffer.
			cache_next(literal_2, bytes_read);
			if(literal_2 != literal_1) {
				break;
			}
			file_data[bytes_written++] = literal_1;
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

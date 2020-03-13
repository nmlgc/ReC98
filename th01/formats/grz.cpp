#pragma option -Z

extern "C" {

#include <stddef.h>
#include <string.h>

#include "ReC98.h"
#include "th01/hardware/graph.h"
#include "th01/formats/grz.h"

extern const char HGRZ_MAGIC[4];
extern const char HGRX_MAGIC[4];

extern char planar_stream_id;
extern char grx_col;
extern uint8_t* rle_streams[GRX_COUNT];
// Actually a planar8_t*, but used like a dots8_t* everywhere.
extern dots8_t* planar_streams[GRX_COUNT][PLANAR_STREAM_PER_GRX_COUNT];
extern unsigned char planar_stream_count[GRX_COUNT];

struct grz_header_t {
	char magic[sizeof(HGRZ_MAGIC)];
	uint8_t image_count;
	int8_t padding[3];
	int32_t offsets[GRZ_IMAGE_COUNT];
	int32_t total_size; // including this header
	int8_t unknown[20];
};

struct grx_header_t {
	char magic[sizeof(HGRX_MAGIC)];
	uint8_t planar_stream_count;
	int8_t unused_1[3];
	uint16_t rle_stream_size;
	uint16_t planar_stream_size;
	int8_t unused_2[4];
	Palette4 palette;
};

void grx_put_stream(unsigned int slot, int planar_stream)
{
	if(planar_stream_count[slot] > planar_stream) {
		planar_stream_id = planar_stream;
		grx_put(slot);
		planar_stream_id = 0;
	}
}

void grx_put_col(unsigned int slot, uint4_t col)
{
	grx_col = (col + 1);
	grx_put(slot);
	grx_col = 0;
}

inline void vram_put(seg_t segment, uint16_t offset, dots8_t dots)
{
	*reinterpret_cast<dots8_t far *>(MK_FP(segment, offset)) = dots;
}

void grx_put(unsigned int slot)
{
	uint8_t command;
	uint8_t runs;
	uint8_t *rle = rle_streams[slot];
	dots8_t *planar = planar_streams[slot][planar_stream_id];

#define put(vram_offset, vram_offset_last, planar) \
	if(!grx_col) { \
		vram_put(SEG_PLANE_B, vram_offset, *(planar++)); \
		vram_put(SEG_PLANE_R, vram_offset, *(planar++)); \
		vram_put(SEG_PLANE_G, vram_offset, *(planar++)); \
		vram_put(SEG_PLANE_E, vram_offset_last, *(planar++)); \
	} else { \
		vram_put(SEG_PLANE_B, vram_offset_last, 0xFF); \
	}

	if(grx_col) {
		grcg_setcolor_rmw(grx_col - 1);
	}
	for(uint16_t vram_offset = 0; vram_offset < PLANE_SIZE; vram_offset++) {
		command = *(rle++);
		if(command == GC_RUN) {
			runs = *(rle++);
			if(runs) {
				command = *(rle++);
				while(runs--) {
					if(command == GC_PUT) {
						put(vram_offset, vram_offset++, planar);
					} else {
						vram_offset++;
					}
				}
			}
		}
		// Yes, in case we just did a putting GC_RUN, we are in fact putting
		// one more byte!
		if(command == GC_PUT) {
			put(vram_offset, vram_offset, planar);
		}
	}
	if(grx_col) {
		grcg_off();
	}
#undef put
}

/// Loading and freeing
/// -------------------
#define fail_if(cond) \
	if(cond) { \
		file_close(); \
		return 1; \
	}

#define grx_header_read(grx, slot) \
	file_read(&grx, sizeof(grx)); \
	fail_if(memcmp(grx.magic, HGRX_MAGIC, sizeof(HGRX_MAGIC))); \
	fail_if(grx.planar_stream_count < 1); \
	planar_stream_count[slot] = grx.planar_stream_count; \

#define rle_stream_new(slot, size) \
	if(rle_streams[slot]) { \
		grx_free(slot); \
	} \
	fail_if((rle_streams[slot] = new uint8_t[size]) == NULL);

#define rle_stream_read(slot, size) \
	file_read(rle_streams[slot], size);

#define planar_streams_new(slot, stream_count, size) \
	for(i = 0; i < stream_count; i++) { \
		if(planar_streams[slot][i]) { \
			grx_free(slot); \
		} \
		fail_if((planar_streams[slot][i] = new uint8_t[size]) == NULL); \
	}

#define planar_streams_read(slot, stream_count, size) \
	for(i = 0; i < stream_count; i++) { \
		file_read(planar_streams[slot][i], size); \
	}

union headers_t {
	grz_header_t grz;
	grx_header_t grx;
	int8_t space[100];
};

int grx_load(unsigned int slot, const char *fn)
{
	uint16_t rle_size;
	uint16_t planar_size;

	if(!file_ropen(fn)) {
		return 1;
	}
	headers_t* h = new headers_t[1];
	grx_header_read(h->grx, slot);

	rle_size = h->grx.rle_stream_size;
	planar_size = h->grx.planar_stream_size;

	int i;
	rle_stream_new(slot, rle_size);
	planar_streams_new(slot, h->grx.planar_stream_count, planar_size);

	rle_stream_read(slot, rle_size);
	planar_streams_read(slot, h->grx.planar_stream_count, planar_size);
	delete[] h;
	file_close();
	return 0;
}

int grx_load_noplanar(unsigned int slot, const char *fn)
{
	uint16_t rle_size;

	if(!file_ropen(fn)) {
		return 1;
	}
	headers_t* h = new headers_t[1];
	grx_header_read(h->grx, slot);
	rle_size = h->grx.rle_stream_size;

	rle_stream_new(slot, rle_size);
	rle_stream_read(slot, rle_size);
	delete[] h;
	file_close();
	return 0;
}

void grx_free(unsigned int slot)
{
	if(rle_streams[slot]) {
		delete[] rle_streams[slot];
		rle_streams[slot] = NULL;
	}
	for(int i = 0; i < PLANAR_STREAM_PER_GRX_COUNT; i++) {
		if(planar_streams[slot][i]) {
			delete[] planar_streams[slot][i];
			planar_streams[slot][i] = NULL;
		}
	}
}

int grz_load_single(unsigned int slot, const char *fn, int n)
{
	register int i;
	uint16_t rle_size;
	uint16_t planar_size;

	if(!file_ropen(fn)) {
		return 1;
	}
	headers_t* h = new headers_t[1];

	file_read(&h->grz, sizeof(h->grz));
	fail_if(memcmp(h->grz.magic, HGRZ_MAGIC, sizeof(HGRZ_MAGIC)));

	uint8_t image_count = h->grz.image_count;
	if(image_count > n) {
		// TODO: Srsly?
		i = (offsetof(grz_header_t, offsets) + (n * sizeof(int32_t)));
		int32_t offset = *reinterpret_cast<int32_t *>(&h->space[i]);
		file_seek(offset, 0);

		grx_header_read(h->grx, slot);
		rle_size = h->grx.rle_stream_size;
		planar_size = h->grx.planar_stream_size;

		rle_stream_new(slot, rle_size);
		planar_streams_new(slot, h->grx.planar_stream_count, planar_size);

		rle_stream_read(slot, rle_size);
		planar_streams_read(slot, h->grx.planar_stream_count, planar_size);
	}
	delete[] h;
	file_close();
	return 0;
}
/// -------------------

}

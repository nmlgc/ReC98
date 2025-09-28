#pragma option -zCPTN_GRP_GRZ

#include <mem.h>
#include <stddef.h>
#include "x86real.h"
#include "libs/master.lib/master.hpp"
#include "th01/hardware/graph.h"
#include "th01/formats/grz.h"

static int8_t planar_stream_id = 0;
static vc_t grx_col = 0;
static uint8_t planar_stream_count[GRX_COUNT];
static uint8_t* rle_streams[GRX_COUNT];

// ZUN bloat: Actually a Planar<dots8_t*>, but used like a dots8_t* everywhere.
static dots8_t* planar_streams[GRX_COUNT][PLANAR_STREAM_PER_GRX_COUNT];

void grx_put(unsigned int slot)
{
	uint8_t command;
	uint8_t runs;
	uint8_t *rle = rle_streams[slot];
	dots8_t *planar = planar_streams[slot][planar_stream_id];

#define put(vram_offset, vram_offset_last, planar) \
	if(!grx_col) { \
		pokeb(SEG_PLANE_B, vram_offset, *(planar++)); \
		pokeb(SEG_PLANE_R, vram_offset, *(planar++)); \
		pokeb(SEG_PLANE_G, vram_offset, *(planar++)); \
		pokeb(SEG_PLANE_E, vram_offset_last, *(planar++)); \
	} else { \
		pokeb(SEG_PLANE_B, vram_offset_last, 0xFF); \
	}

	if(grx_col) {
		grcg_setcolor_rmw(grx_col - 1);
	}
	uvram_offset_t vram_offset;
	for(vram_offset = 0; vram_offset < PLANE_SIZE; vram_offset++) {
		// Effectively the same algorithm as used for .GRF files, except for
		// • the fixed RLE run command byte, and
		// • adding another wasteful byte to define whether a run should put
		//   actually the next bytes from the planar stream, or just skip over
		//   them.
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
		grcg_off_func();
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
	fail_if(memcmp(grx.magic, HGRX_MAGIC, (sizeof(HGRX_MAGIC) - 1))); \
	fail_if(grx.planar_stream_count < 1); \
	planar_stream_count[slot] = grx.planar_stream_count; \

#define rle_stream_new(slot, size) \
	if(rle_streams[slot]) { \
		grx_free(slot); \
	} \
	fail_if((rle_streams[slot] = new uint8_t[size]) == nullptr);

#define rle_stream_read(slot, size) \
	file_read(rle_streams[slot], size);

#define planar_streams_new(slot, stream_count, size) \
	for(i = 0; i < stream_count; i++) { \
		if(planar_streams[slot][i]) { \
			grx_free(slot); \
		} \
		fail_if((planar_streams[slot][i] = new uint8_t[size]) == nullptr); \
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

void grx_free(unsigned int slot)
{
	if(rle_streams[slot]) {
		delete[] rle_streams[slot];
		rle_streams[slot] = nullptr;
	}
	for(int i = 0; i < PLANAR_STREAM_PER_GRX_COUNT; i++) {
		if(planar_streams[slot][i]) {
			delete[] planar_streams[slot][i];
			planar_streams[slot][i] = nullptr;
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
	fail_if(memcmp(h->grz.magic, HGRZ_MAGIC, (sizeof(HGRZ_MAGIC) - 1)));

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

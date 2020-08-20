extern "C" {

#include "ReC98.h"
#include "th01/hardware/palette.h"
#include "th01/formats/ptn.hpp"
#include "th01/formats/pf.hpp"

extern int flag_palette_show;

// On-disk .PTN slot file header
// -----------------------------
#define PTN_MAGIC "HPTN"

typedef struct {
	char magic[sizeof(PTN_MAGIC) - 1];
	int8_t unused_one;
	int8_t image_count;
} ptn_header_t;
// -----------------------------

ptn_error_t ptn_load_palette_show(int slot, const char *fn)
{
	union {
		Palette4 pal;
		ptn_header_t header;
	} h;

	int y;
	int i;
	int image_count;
	ptn_t *ptn;

	arc_file_load(fn);
	arc_file_get_far(h.header);

	image_count = h.header.image_count;
	// MODDERS:
	/* if(image_count <= 0 || image_count > PTN_IMAGES_PER_SLOT) {
		return PE_IMAGE_COUNT_INVALID;
	} */
	if(ptn_images[slot]) {
		delete[] ptn_images[slot];
	}
	ptn_images[slot] = new ptn_t[image_count];
	if(!ptn_images[slot]) {
		return PE_OUT_OF_MEMORY;
	}

	arc_file_get_far(h.pal);
	if(flag_palette_show) {
		z_palette_set_all_show(h.pal);
	}

	ptn_image_count[slot] = image_count;
	ptn = ptn_images[slot];
	for(i = 0; i < image_count; i++, ptn++) {
		arc_file_get_far(ptn->unused_zero);
		arc_file_get_far(ptn->planes);
		for(y = 0; y < PTN_H; y++) {
			ptn->alpha[y] = ptn_alpha_from(
				ptn->planes.B[y],
				ptn->planes.R[y],
				ptn->planes.G[y],
				ptn->planes.E[y]
			);
		}
	}
	arc_file_free();
	return PE_OK;
}

ptn_error_t ptn_new(int slot, int image_count)
{
	if(image_count <= 0 || image_count > PTN_IMAGES_PER_SLOT) {
		return PE_IMAGE_COUNT_INVALID;
	}
	if(ptn_images[slot]) {
		delete[] ptn_images[slot];
	}
	ptn_image_count[slot] = image_count;
	ptn_images[slot] = new ptn_t[image_count];
	if(!ptn_images[slot]) {
		return PE_OUT_OF_MEMORY;
	}
	return PE_OK;
}

void ptn_load(int slot, const char *fn)
{
	flag_palette_show = false;
	int ret = ptn_load_palette_show(slot, fn);
	flag_palette_show = true;
	ret;
}

void ptn_free(int slot)
{
	if(ptn_images[slot]) {
		delete[] ptn_images[slot];
		ptn_images[slot] = NULL;
		ptn_image_count[slot] = 0;
	}
}

void ptn_put_noalpha_8(screen_x_t left, vram_y_t top, int ptn_id)
{
	unsigned int vram_offset = vram_offset_shift(left, top);
	ptn_t *ptn = ptn_with_id(ptn_id);
	for(int y = 0; y < PTN_H; y++) {
		#define put_noalpha(vram_offset, w, ptn) \
			VRAM_CHUNK(B, vram_offset, w) = (ptn->planes.B[y]); \
			VRAM_CHUNK(R, vram_offset, w) = (ptn->planes.R[y]); \
			VRAM_CHUNK(G, vram_offset, w) = (ptn->planes.G[y]); \
			VRAM_CHUNK(E, vram_offset, w) = (ptn->planes.E[y]);
		put_noalpha(vram_offset, PTN_W, ptn);
		#undef put_noalpha
		vram_offset += ROW_SIZE;
	}
}

void ptn_put_quarter_noalpha_8(
	screen_x_t left, vram_y_t top, int ptn_id, int quarter
)
{
	int y;
	unsigned int vram_offset = vram_offset_muldiv(left, top);
	PTNQuarter q;
	ptn_t *ptn = ptn_with_id(ptn_id);

	q.init(quarter);
	for(y = q.y; y < (q.y + PTN_QUARTER_H); y++) {
		#define put_quarter_noalpha(vram_offset, w, ptn, q_x) \
			VRAM_CHUNK(B, vram_offset, w) = (ptn->planes.B[y] >> q_x); \
			VRAM_CHUNK(R, vram_offset, w) = (ptn->planes.R[y] >> q_x); \
			VRAM_CHUNK(G, vram_offset, w) = (ptn->planes.G[y] >> q_x); \
			VRAM_CHUNK(E, vram_offset, w) = (ptn->planes.E[y] >> q_x);
		put_quarter_noalpha(vram_offset, PTN_QUARTER_W, ptn, q.x);
		#undef put_quarter_noalpha
		vram_offset += ROW_SIZE;
	}
}

}

#pragma option -zCSHARED

#include <io.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "libs/master.lib/master.hpp"
#include "th03/formats/cdg.h"

// Won't load the alpha plane of the next CDG file if nonzero.
extern bool cdg_noalpha;

#define cdg_allocate_and_read_alpha(cdg) \
	(cdg).seg_alpha() = reinterpret_cast<dots8_t __seg *>(hmem_allocbyte( \
		(cdg).bitplane_size \
	)); \
	file_read((cdg).seg_alpha(), (cdg).bitplane_size);

#define cdg_allocate_and_read_colors(cdg) \
	(cdg).seg_colors() = reinterpret_cast<dots8_t __seg *>(hmem_allocbyte( \
		((cdg).bitplane_size * PLANE_COUNT) \
	)); \
	file_read((cdg).seg_colors(), ((cdg).bitplane_size * PLANE_COUNT)); \

#define cdg_read_header_and_seek_to_image(cdg, n) \
	file_read(&cdg, sizeof(CDG)); \
	\
	uint32_t image_size = (cdg.bitplane_size * (PLANE_COUNT + 1)); \
	file_seek((n * image_size), SEEK_CUR);

void pascal cdg_load_single(int slot, const char *fn, int n)
{
	cdg_free(slot);

	CDG near &cdg = cdg_slots[slot];

	file_ropen(fn);
	cdg_read_header_and_seek_to_image(cdg, n);
	cdg_allocate_and_read_alpha(cdg);
	cdg_allocate_and_read_colors(cdg);
	file_close();
}

void pascal cdg_load_single_noalpha(int slot, const char *fn, int n)
{
	cdg_free(slot);

	CDG near &cdg = cdg_slots[slot];
	file_ropen(fn);

	cdg_read_header_and_seek_to_image(cdg, n);
	file_seek(cdg.bitplane_size, SEEK_CUR);
	cdg.seg_alpha() = nullptr;
	cdg_allocate_and_read_colors(cdg);
	file_close();
}

void pascal cdg_load_all(int slot_first, const char *fn)
{
	file_ropen(fn);
	cdg_free(slot_first);

	CDG near *cdg_p = &cdg_slots[slot_first];
	file_read(cdg_p, sizeof(CDG));

	CDG near &cdg_first = *cdg_p;
	int i;
	for(i = 1; cdg_first.image_count > i; i++) {
		cdg_free(slot_first + i);
	}

	i = 0;
	while(cdg_first.image_count > i) {
		cdg_p->bitplane_size = cdg_first.bitplane_size;
		cdg_p->pixel_w = cdg_first.pixel_w;
		cdg_p->pixel_h = cdg_first.pixel_h;
		cdg_p->offset_at_bottom_left = cdg_first.offset_at_bottom_left;
		cdg_p->vram_dword_w = cdg_first.vram_dword_w;
		cdg_p->image_count = cdg_first.image_count;
		cdg_p->plane_layout = CDG_COLORS_AND_ALPHA;

		if(!cdg_noalpha) {
			cdg_allocate_and_read_alpha(*cdg_p);
		} else {
			cdg_p->seg_alpha() = nullptr;
			file_seek(cdg_p->bitplane_size, SEEK_CUR);
		}
		cdg_allocate_and_read_colors(*cdg_p);
		i++;
		cdg_p++;
	}
	file_close();
}

void pascal cdg_load_all_noalpha(int slot_first, const char *fn)
{
	cdg_noalpha = true;
	cdg_load_all(slot_first, fn);
	cdg_noalpha = false;
}

void pascal cdg_free(int slot)
{
	CDG near *cdg = &cdg_slots[slot];
	for(int i = 0; i < (sizeof(cdg->seg) / sizeof(cdg->seg[0])); i++) {
		if(cdg->seg[i]) {
			hmem_free(cdg->seg[i]);
			cdg->seg[i] = nullptr;
		}
	}
}

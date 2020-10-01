#pragma option -O-

#include "th01/end/pic.hpp"

void pascal end_pics_load_palette_show(const char *fn)
{
	graph_accesspage_func(1);
	grp_put_palette_show(fn);
}

// Avoid symbol duplication...
#define egc_start_copy egc_start_copy_1
#include "th01/hardware/egcstart.c"

static const pixel_t PIC_W = (RES_X / 2);
static const pixel_t PIC_H = (RES_Y / 2);
static const screen_x_t PIC_LEFT = ((RES_X / 2) - (PIC_W / 2));
static const screen_y_t PIC_TOP  = ((RES_Y / 2) - (PIC_H / 2));

static const pixel_t PIC_VRAM_W = (PIC_W / BYTE_DOTS);

void end_pic_show(int quarter)
{
	egc_start_copy();

	pixel_t src_left = ((quarter % 2) * PIC_W);
	pixel_t src_top  = ((quarter / 2) * PIC_H);
	uvram_offset_t vram_offset_src = vram_offset_shift(src_left, src_top);
	uvram_offset_t vram_offset_dst = vram_offset_shift(PIC_LEFT, PIC_TOP);
	vram_word_amount_t vram_x;
	pixel_t y;

	for(y = 0; y < PIC_H; y++) {
		for(vram_x = 0; vram_x < (PIC_VRAM_W / sizeof(dots16_t)); vram_x++) {
			dots16_t d;

			graph_accesspage_func(1); egc_snap(d, vram_offset_src, 16);
			graph_accesspage_func(0); egc_put(vram_offset_dst, d, 16);

			vram_offset_src += sizeof(dots16_t);
			vram_offset_dst += sizeof(dots16_t);
		}
		vram_offset_src += (ROW_SIZE - PIC_VRAM_W);
		vram_offset_dst += (ROW_SIZE - PIC_VRAM_W);
	}
	egc_off();
}

#pragma option -O.

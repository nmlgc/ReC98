#pragma option -O -Z -3 -G

#include "th01/end/pic.hpp"
#include "platform/x86real/flags.hpp"
#include "x86real.h"

void pascal end_pics_load_palette_show(const char *fn)
{
	graph_accesspage_func(1);
	grp_put_palette_show(fn);
}

// Avoid symbol duplication...
#define egc_start_copy egc_start_copy_1
#include "th01/hardware/egcstart.cpp"

void end_pic_show(int quarter)
{
	egc_start_copy();

	pixel_t src_left = ((quarter % 2) * CUTSCENE_PIC_W);
	pixel_t src_top  = ((quarter / 2) * CUTSCENE_PIC_H);
	uvram_offset_t vo_src = vram_offset_shift(src_left, src_top);
	uvram_offset_t vo_dst = vram_offset_shift(
		CUTSCENE_PIC_LEFT, CUTSCENE_PIC_TOP
	);
	vram_word_amount_t vram_x;
	pixel_t y;

	// Mod: Remove unnecessary operations and use pseudoregisters to speed up
	// the loop to 50% of the run time of the original version.
	_ES = SEG_PLANE_B;
	for(y = 0; y < CUTSCENE_PIC_H; y++) {
		_CX = (CUTSCENE_PIC_VRAM_W / EGC_REGISTER_SIZE);
		do {
			_outportb_(0xA6, 1);
			_AX = *reinterpret_cast<dots16_t far *>(MK_FP(_ES, vo_src));
			_outportb_(0xA6, 0);
			*reinterpret_cast<dots16_t far *>(MK_FP(_ES, vo_dst)) = _AX;

			vo_src += sizeof(dots16_t);
			vo_dst += sizeof(dots16_t);
			_CX--;
		} while(!FLAGS_ZERO);
		vo_src += (ROW_SIZE - CUTSCENE_PIC_VRAM_W);
		vo_dst += (ROW_SIZE - CUTSCENE_PIC_VRAM_W);
	}
	egc_off();
}

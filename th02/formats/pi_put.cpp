#pragma codeseg SHARED
#pragma option -3

extern "C" {
#include <dos.h>
#include <mem.h>
#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th02/formats/pi.h"

void pi_palette_apply(int slot)
{
	palette_set_all(pi_headers[slot].palette);
	palette_show();
}

void DEFCONV pi_put_8(screen_x_t left, vram_y_t top, int slot)
{
	char *row_p = reinterpret_cast<char *>(pi_buffers[slot]);
	pixel_t y;
	for(y = 0; y < pi_headers[slot].ysize; y++) {
		graph_pack_put_8(left, top, row_p, pi_headers[slot].xsize);
		top++;
		if(top >= RES_Y) {
			top -= RES_Y;
		}
		row_p += pi_headers[slot].xsize / 2;
		row_p = reinterpret_cast<char far *>(MK_FP(
			(int)((unsigned long)(row_p) >> 16) + (FP_OFF(row_p) >> 4),
			FP_OFF(row_p) & 0xF
		));
	}
}

}

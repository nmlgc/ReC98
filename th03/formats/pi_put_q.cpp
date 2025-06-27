#pragma option -zCSHARED

#include "th03/formats/pi.hpp"
#include "game/cutscene.hpp"

void pascal pi_put_quarter_8(
	screen_x_t left, vram_y_t top, int slot, int quarter
)
{
	pi_buffer_p_t row_p;

	pi_buffer_p_init_quarter(row_p, slot, quarter);
	for(pixel_t row = 0; row < CUTSCENE_PIC_H; row++) {
		graph_pack_put_8(left, top, row_p, CUTSCENE_PIC_W);
		top++;
		if(top >= RES_Y) {
			top -= RES_Y;
		}
		pi_buffer_p_offset(row_p, PI_W, 0);
		pi_buffer_p_normalize(row_p);
	}
}

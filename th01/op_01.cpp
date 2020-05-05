/* ReC98
 * -----
 * Code segment #1 of TH01's OP.EXE
 */

extern "C" {
#include "ReC98.h"
#include "th01/hardware/graph.h"

// Unused. The only thing on the main menu with this color is the "1996 ZUN"
// text at the bottom... probably part of an effect that we never got to see.
void snap_col_4(void)
{
	extern dots8_t* columns[ROW_SIZE];
	register int x;
	register int y;
	int vram_offset;

	for(x = 0; x < ROW_SIZE; x++) {
		columns[x] = new dots8_t[RES_Y];
	}
	grcg_setcolor_tdw(4);
	graph_accesspage_func(1);

	for(x = 0; x < ROW_SIZE; x++) {
		y = 0;
		vram_offset = x;
		while(y < RES_Y) {
			columns[x][y] = VRAM_PLANE_B[vram_offset];
			y++;
			vram_offset += ROW_SIZE;
		}
	}

	grcg_off();
	graph_accesspage_func(0);
}

}

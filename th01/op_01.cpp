/* ReC98
 * -----
 * Code segment #1 of TH01's OP.EXE
 */

#pragma option -Z

extern "C" {
#include <stdio.h>
#include "ReC98.h"
#include "th01/ranks.h"
#include "th01/hardware/graph.h"
#include "th01/formats/cfg.hpp"

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

/// REIIDEN.CFG loading and saving
/// ------------------------------
extern cfg_options_t opts;
// These will be removed once the strings can be defined here
#undef CFG_FN
#undef CFG_ID
extern const char CFG_FN[], CFG_ID[], FOPEN_RB[], FOPEN_WB[];

void cfg_load(void)
{
	cfg_t cfg_in;
	bool read_failure = false;
	FILE* fp;

	if(( fp = fopen(CFG_FN, FOPEN_RB) ) == NULL) {
use_defaults:
		read_failure = true;
	}
	if(!read_failure) {
		fread(&cfg_in, 1, sizeof(cfg_in), fp);
		if(memcmp(cfg_in.id, CFG_ID, sizeof(cfg_in.id))) {
			fclose(fp);
			goto use_defaults;
		}
		opts.rank = cfg_in.opts.rank;
		opts.bgm_mode = cfg_in.opts.bgm_mode;
		opts.bombs = cfg_in.opts.bombs;
		opts.lives_extra = cfg_in.opts.lives_extra;
		fclose(fp);
	} else {
		opts.rank = CFG_RANK_DEFAULT;
		opts.bgm_mode = CFG_BGM_MODE_DEFAULT;
		opts.bombs = CFG_BOMBS_DEFAULT;
		opts.lives_extra = CFG_LIVES_EXTRA_DEFAULT;
	}
}

void cfg_save(void)
{
	bool write_failure = false;
	FILE* fp;

	if(( fp = fopen(CFG_FN, FOPEN_WB) ) == NULL) {
		write_failure = true;
	}
	if(!write_failure) {
		fputs(CFG_ID, fp);
		fputc(opts.rank, fp);
		fputc(opts.bgm_mode, fp);
		fputc(opts.bombs, fp);
		fputc(opts.lives_extra, fp);
		fclose(fp);
	}
}
/// ------------------------------

}

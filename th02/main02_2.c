/* ReC98
 * -----
 * 2nd part of code segment #2 of TH02's MAIN.EXE
 */

#include "th02/th02.h"
#include "th02/formats/pi.h"
#include "th02/mem.h"

#pragma codeseg main_02_TEXT
#pragma option -3

#define frame_delay_2 frame_delay

extern const char pf_fn[];

#include "th02/hardware/input.c"
#include "th02/exit.c"
#include "th02/snd/mmd_res.c"
#include "th02/snd/detmode.c"
#include "th02/snd/pmd_res.c"
#include "th02/snd/delayvol.c"
#include "th02/snd/load.c"

#pragma option -k

void pascal mptn_palette_show(void)
{
	palette_set_all(mptn_palette);
	palette_show();
}

int pascal mptn_load_inner(const char *fn)
{
	mptn_header_t header;

	file_ropen(fn);
	file_read(&header, sizeof(header));
	mptn_count = header.count;
	file_read(&mptn_palette, sizeof(mptn_palette));
	if(mptn_show_palette_on_load) {
		mptn_palette_show();
	}
	if(mptn_buffer) {
		mptn_free();
	}
	mptn_buffer = MK_FP(hmem_allocbyte((mptn_count + 1) * MPTN_SIZE), 0);
	if(!mptn_buffer) {
		file_close();
		return -1;
	}
	file_read(mptn_buffer, (mptn_count + 1) * MPTN_SIZE);
	file_close();
	return 0;
}

#include "th02/initmain.c"
#include "th02/formats/pi_put.c"
#include "th02/snd/kajaint.c"
#include "th02/snd/delaymea.c"
#pragma codestring "\x00"
#include "th02/snd/se.c"

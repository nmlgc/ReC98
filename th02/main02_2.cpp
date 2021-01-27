/* ReC98
 * -----
 * 2nd part of code segment #2 of TH02's MAIN.EXE
 */

#pragma codeseg SHARED
#pragma option -3

extern "C" {
#include <dos.h>
#include <mem.h>
#include "libs/kaja/kaja.h"
#include "th02/th02.h"
#include "master.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/hardware/input.hpp"
#include "th02/snd/snd.h"

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
	mptn_buffer = reinterpret_cast<int *>(reinterpret_cast<int __seg*>(
		hmem_allocbyte((mptn_count + 1) * MPTN_SIZE)
	));
	if(!mptn_buffer) {
		file_close();
		return -1;
	}
	file_read(mptn_buffer, (mptn_count + 1) * MPTN_SIZE);
	file_close();
	return 0;
}
}

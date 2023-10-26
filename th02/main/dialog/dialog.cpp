#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "shiftjis.hpp"
#include "master.hpp"
#include "th02/formats/dialog.hpp"
#include "th02/main/dialog/dialog.hpp"
#include "th02/main/stage/stage.hpp"

// State
// -----

extern shiftjis_t dialog_text[64][DIALOG_BOX_LINES][DIALOG_LINE_SIZE];
// -----

void dialog_load_and_init(void)
{
	extern char dialog_fn[];
	char* fn = dialog_fn;
	fn[5] = ('0' + stage_id);

	file_ropen(fn);

	// ZUN landmine: No check to ensure that the size is ≤ sizeof(dialog_text).
	size_t size = file_size();
	file_read(dialog_text, size);

	file_close();
	dialog_box_cur = 0;
}

// ZUN bloat: Turn into a single global inline function.
#define egc_start_copy	near egc_start_copy_2
#include "th01/hardware/egcstart.cpp"
#undef egc_start_copy

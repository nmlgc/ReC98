#pragma option -zCmain_TEXT

#include <stddef.h>
#include "platform.h"
#include "master.hpp"
#include "th04/score.h"
#include "th04/resident.hpp"
#include "th04/formats/dialog.hpp"

void pascal near dialog_load(const char *fn)
{
	size_t size;

	// While hmem_free() isn't specified to perform a NULL check, it does in
	// practice. So while this is *technically* fine, it's not the cleanest
	// solution. Fixed in TH05.
	hmem_free(reinterpret_cast<void __seg *>(dialog_p));

	file_ropen(fn);
	size = file_size();
	dialog_p = reinterpret_cast<unsigned char far *>(hmem_allocbyte(size));
	file_read(dialog_p, size);
	file_close();
}

void near dialog_load(void)
{
	#define fn dialog_fn
	extern char *fn;
	dialog_fn[3] = resident->playchar_ascii;
	dialog_fn[4] = resident->stage_ascii;
	dialog_load(dialog_fn);
	#undef fn
}

void dialog_load_yuuka5_defeat_bad(void)
{
	#define fn dialog_fn_yuuka5_defeat_bad
	extern char *fn;
	fn[3] = resident->playchar_ascii;
	dialog_load(fn);
	#undef fn
}

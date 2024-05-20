#pragma option -zCmain_TEXT -zPmain_01

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "libs/master.lib/master.hpp"
#include "th04/score.h"
#include "th04/main/stage/stage.hpp"
#include "th05/playchar.h"
#include "th05/resident.hpp"
#include "th05/formats/dialog.hpp"

void pascal dialog_load(const char *fn)
{
	size_t size;
	tx2_header_t header;

	if(dialog_p) {
		// PORTERS: See the note in dialog_free() – and maybe just call that
		// function instead, then.
		hmem_free(reinterpret_cast<void __seg *>(dialog_p));
	}
	file_ropen(fn);
	file_read(&header, sizeof(header));

	// A sanity check here would have been particularly helpful for
	// translators, who tend to start out by just blindly editing a .TX2 file.
	size = (header.offset_for[playchar + 1] - header.offset_for[playchar]);

	dialog_p = reinterpret_cast<unsigned char far *>(hmem_allocbyte(size));
	file_seek(header.offset_for[playchar], SEEK_SET);
	file_read(dialog_p, size);
	file_close();
}

void near dialog_load(void)
{
	#define fn dialog_fn
	extern char *fn;
	fn[4] = ('0' + stage_id);
	dialog_load(fn);
	#undef fn
}

void near dialog_free(void)
{
	if(dialog_p) {
		// PORTERS: Relies on `far` pointer semantics, specifically on the
		// segment part still being identical to what hmem_allocbyte()
		// returned. You'll need to introduce a separate "dialog buffer base
		// pointer" when porting to flat memory models.
		hmem_free(reinterpret_cast<void __seg *>(dialog_p));
		dialog_p = nullptr;
	}
}

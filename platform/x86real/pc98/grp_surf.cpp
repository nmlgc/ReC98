// PC-98 sprite and image management
// ---------------------------------

#include "platform/x86real/pc98/grp_surf.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/piloadc/piloadm.hpp"
#include "x86real.h"

static const uint16_t PILOAD_BUFFER_SIZE = 0x4000;

// Pulling the palette out of the buffer this way might look like reliance on
// implementation details, but it is, in fact, officially sanctioned by
// PILOADC.DOC.
void near piload_maybe_extract_palette(Palette8 *palette, int8_t __seg *buf)
{
	if(palette) {
		*palette = *reinterpret_cast<const Palette8 far *>(MK_FP(buf, 0x100));
	}
}

#ifndef __LARGE__
int far file_read_far(void far *buf, unsigned wsize)
{
	return file_read(buf, wsize);
}
#define file_read file_read_far
#endif

int GrpSurface_BlitBackgroundPI(Palette8 *palette, const char *fn)
{
	int ret;

	if(!file_ropen(fn)) {
		return FileNotFound;
	}

	int8_t __seg *buf = HMem<int8_t>::alloc(PILOAD_BUFFER_SIZE);
	if(!buf) {
		ret = InsufficientMemory;
		goto err_with_file;
	}
	ret = PiBlitL(buf, PILOAD_BUFFER_SIZE, 0, 0, 0, file_read);
	piload_maybe_extract_palette(palette, buf);

	HMem<int8_t>::free(buf);
err_with_file:
	file_close();
	return ret;
}

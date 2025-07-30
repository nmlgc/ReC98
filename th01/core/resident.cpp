// Sane resident structure implementation
// --------------------------------------

#include "libs/master.lib/master.hpp"
#include "th01/resident.hpp"
#include <process.h>

resident_t __seg *resident;

resident_t __seg* resident_get(void)
{
	return ResData<resident_t>::exist(RES_ID);
}

resident_t __seg* resident_get_or_create(void)
{
	resident_t __seg* seg = resident_get();
	if(!seg) {
		seg = ResData<resident_t>::create(RES_ID);
		if(!seg) {
			dos_puts2("Failed to allocate resident structure.\n");
			exit(-1);
		}
		seg->stage_id = 0;
	}
	return seg;
}

void resident_free(void)
{
	resident_t __seg *seg = resident_get();
	if(seg) {
		resdata_free(seg);
	}
}

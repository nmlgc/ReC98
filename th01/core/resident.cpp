// Sane resident structure implementation
// --------------------------------------

#include "libs/master.lib/master.hpp"
#include "th01/resident.hpp"

resident_t __seg *resident;

resident_t __seg* resident_get(void)
{
	return ResData<resident_t>::exist(RES_ID);
}

resident_t __seg* resident_get_or_create(void)
{
	resident_t __seg* seg = resident_get();
	if(!seg) {
		// ZUN landmine: We should be quitting if we can't allocate the resident
		// structure.
		seg = ResData<resident_t>::create(RES_ID);
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

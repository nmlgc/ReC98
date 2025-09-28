// Implementation of cfg_load_resident_ptr().

#include "libs/master.lib/master.hpp"

// Referenced in the headers below.
struct resident_t;
extern resident_t far* resident;

#include "x86real.h"
#if (GAME >= 4)
#include "th04/formats/cfg.hpp"
#else
#include "th03/formats/cfg.hpp"
#endif

static inline resident_t __seg* cfg_load_and_set_resident(
	cfg_t& cfg, const char* fn
) {
	file_ropen(fn);
	file_read(&cfg, sizeof(cfg));
	file_close();

	resident_t __seg *resident_seg = cfg.resident;
	resident = resident_seg;
	return resident_seg;
}

// Implementation of cfg_load_resident_ptr().

// Referenced in the headers below.
struct resident_t;
extern resident_t far* resident;

#include "x86real.h"
#if (GAME >= 4)
	#include "th04/formats/cfg.hpp"
#else
	#include "th03/formats/cfg.hpp"
#endif

#if (GAME == 5)
	static inline resident_t __seg* cfg_load_and_set_resident_dos(
		cfg_t near& cfg, const char near* fn
	) {
		// DOS file open
		_AX = 0x3D00;
		reinterpret_cast<const char near *>(_DX) = fn;
		geninterrupt(0x21);
		_BX = _AX;

		// DOS file read
		_AH = 0x3F;
		reinterpret_cast<cfg_t near *>(_DX) = &cfg;
		_CX = sizeof(cfg);
		geninterrupt(0x21);

		// DOS file close
		_AH = 0x3E;
		geninterrupt(0x21);

		resident = cfg.resident;
		return cfg.resident;
	}
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

#pragma option -k-

#include "platform.h"
#include "x86real.h"
#include "master.hpp"
#include "th04/score.h"
#include "th05/resident.hpp"
#include "th04/formats/cfg.hpp"

resident_t __seg* near cfg_load_resident_ptr(void)
{
	#undef CFG_FN
	extern const char CFG_FN[];
	extern cfg_t cfg;

	// DOS file open
	_AX = 0x3D00;
	reinterpret_cast<const char near *>(_DX) = CFG_FN;
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
#pragma codestring "\x90"

#include "th03/formats/cfg_impl.hpp"

resident_t __seg* near cfg_load_resident_ptr(void)
{
	#undef CFG_FN
	extern const char CFG_FN[];
	extern cfg_t cfg;

	return cfg_load_and_set_resident_dos(cfg, CFG_FN);
}

#include "th03/formats/cfg_impl.hpp"

resident_t __seg* near cfg_load_resident_ptr(void)
{
	#undef CFG_FN
	extern const char CFG_FN[];
	cfg_t cfg;
	return cfg_load_and_set_resident(cfg, CFG_FN);
}

// TH02 packfile declarations.

#include "libs/master.lib/master.hpp"

static inline void game_pfopen(void) {
	extern const char pf_fn[];
	pfkey = 0x12;
	pfstart(pf_fn);
}

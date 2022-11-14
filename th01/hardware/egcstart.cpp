#ifndef DECOMP_HPP
	#include "decomp.hpp"
#endif
#include "th01/hardware/egc.h"

void egc_start_copy(void)
{
	egc_on();
	egc_setup_copy();
}

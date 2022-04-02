#include "decomp.hpp"
extern "C" {
#include "th01/hardware/egc.h"
}

void egc_start_copy(void)
{
	egc_on();
	egc_setup_copy();
}

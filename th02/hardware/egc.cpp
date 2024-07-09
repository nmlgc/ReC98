#include "th01/hardware/egc_impl.hpp"

#pragma option -k-

void egc_start_copy_noframe(void)
{
	egc_on();
	egc_setup_copy();
}

#pragma option -k.

#include "th01/hardware/egc_impl.hpp"

void egc_start_copy(void)
{
	egc_on();
	egc_setup_copy();
}

#include "th01/hardware/egc.h"
#include "decomp.h"

void pascal egc_start_copy(void)
{
	egc_on();
	egc_setup_copy();
}

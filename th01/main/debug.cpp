#include "th01/main/debug.hpp"
#include "th01/shiftjis/debug.hpp"

void out_of_memory_exit(void)
{
	puts(ERROR_OUT_OF_MEMORY);
	exit(1);
}

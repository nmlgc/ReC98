#include "th02/shiftjis/fns.hpp"
#include "th02/gaiji/loadfree.h"

void near gaiji_load(void)
{
	#undef GAIJI_FN
	extern const char GAIJI_FN[];

	gaiji_backup();
	gaiji_entry_bfnt(GAIJI_FN);
}

void near gaiji_free(void)
{
	gaiji_restore();
}

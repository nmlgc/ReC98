#include <stddef.h>
#include "platform.h"
#include "master.hpp"
#include "shiftjis.hpp"
#include "th02/formats/end.hpp"

// State
// -----

shiftjis_t end_text[100][END_LINE_SIZE];
// -----

void pascal near end_load(const char *fn)
{
	file_ropen(fn);

	// ZUN landmine: No check to ensure that the size is ≤ sizeof(end_text).
	// Dynamic allocation would have made more sense...
	size_t size = file_size();
	file_read(end_text, size);

	file_close();
}

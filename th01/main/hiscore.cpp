#include "th01/main/hiscore.hpp"

void hiscore_load(void)
{
	scoredat_load();
	resident->hiscore = scoredat_hiscore_get();
	scoredat_free();
}

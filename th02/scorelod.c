#include "libs/master.lib/master.hpp"

extern const char* SCOREDAT_FN_PTR;

void near scoredat_load(void)
{
	int byte;
	file_ropen(SCOREDAT_FN_PTR);
	file_seek(rank * sizeof(hi), 0);
	file_read(&hi, sizeof(hi));
	for(byte = 0; byte < sizeof(hi.score); byte++) {
		*((uint8_t *)(&hi.score) + byte) -= 0x12;
	}
	file_close();
}

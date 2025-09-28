#pragma option -zCSCORE_TEXT

#include "th04/formats/scoredat/scoredat.hpp"
#include "th04/formats/scoredat/impl.hpp"

uint8_t pascal near scoredat_decode(void)
{
	int i;
	int sum;
	scoredat_decode_section(hi, sum, i);
#if (BINARY == 'O')
	if(hi.score_sum != sum) {
		return 1;
	}
	scoredat_decode_section(hi2, sum, i);
	return (hi2.score_sum - sum);
#else
	return (hi.score_sum - sum);
#endif
}

#pragma option -zCSCORE_TEXT

#include "th04/formats/scoredat/scoredat.hpp"
#include "th04/formats/scoredat/impl.hpp"

uint8_t pascal near scoredat_decode(scoredat_section_t& section)
{
	int i;
	int sum;
	scoredat_decode_section(section, sum, i);
	return (section.score_sum - sum);
}

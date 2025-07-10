#pragma option -zCSCORE_TEXT

#include "th04/formats/scoredat/scoredat.hpp"
#include "th04/formats/scoredat/impl.hpp"
#include "libs/master.lib/master.hpp"

void pascal near scoredat_encode(void)
{
	int i;
	scoredat_sum(hi.score_sum, i, hi);

	hi.key1 = irand();
	hi.key2 = irand();

	uint8_t feedback = 0;
	i = (sizeof(scoredat_section_t) - 1);
	while(i >= offsetof(scoredat_section_t, score)) {
		scoredat_encode_byte_at(
			(reinterpret_cast<uint8_t *>(&hi) + i), feedback, hi.key1, hi.key2
		);
		i--;
	}
}

#pragma option -zCSCORE_TEXT

#include "th04/formats/scoredat/scoredat.hpp"
#include "th04/formats/scoredat/impl.hpp"
#include "libs/master.lib/master.hpp"

void pascal near scoredat_encode(scoredat_section_t& section)
{
	int i;
	scoredat_sum(section.score_sum, i, section);

	section.key1 = irand();
	section.key2 = irand();

	uint8_t feedback = 0;
	i = (sizeof(scoredat_section_t) - 1);
	while(i >= offsetof(scoredat_section_t, score)) {
		scoredat_encode_byte_at(
			(reinterpret_cast<uint8_t *>(&section) + i),
			feedback,
			section.key1,
			section.key2
		);
		i--;
	}
}

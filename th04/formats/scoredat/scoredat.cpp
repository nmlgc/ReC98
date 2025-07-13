#pragma option -zCSCORE_TEXT

#include "th04/formats/scoredat/scoredat.hpp"
#include "th04/formats/scoredat/impl.hpp"
#include "th04/shiftjis/fnshared.hpp"
#include "libs/master.lib/master.hpp"

uint8_t pascal near scoredat_decode(scoredat_section_t& section)
{
	int i;
	int sum;
	scoredat_decode_section(section, sum, i);
	return (section.score_sum - sum);
}

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

inline int scoredat_section_i(playchar_t playchar, rank_t rank) {
	return ((playchar * RANK_COUNT) + rank);
}

size_t pascal near scoredat_section_offset(playchar_t playchar, rank_t rank)
{
	return (scoredat_section_i(playchar, rank) * sizeof(scoredat_section_t));
}

bool pascal near scoredat_load(playchar_t playchar, rank_t rank)
{
	if(file_ropen(SCOREDAT_FN)) {
		file_seek(scoredat_section_offset(playchar, rank), SEEK_SET);
		file_read(&hi, sizeof(scoredat_section_t));
		file_close();

		if(scoredat_decode(hi) == 0) {
			return false;
		}
	}
	scoredat_recreate();
	return true;
}

void pascal near scoredat_save(playchar_t playchar, rank_t rank)
{
	scoredat_encode(hi);

	file_append(SCOREDAT_FN);
	file_seek(scoredat_section_offset(playchar, rank), SEEK_SET);
	file_write(&hi, sizeof(scoredat_section_t));
	file_close();
}

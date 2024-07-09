#include "th03/formats/scorecry.hpp"

void pascal near scoredat_encode_and_save(rank_t rank)
{
	uint8_t near *p;
	int i;
	uint8_t feedback;
	uint16_t sum = 0;

	hi.score.key1 = irand();
	hi.score.key2 = irand();
	hi.score.unknown = irand();

	#if (BINARY == 'L')
		if(
			(resident->story_stage == STAGE_ALL) &&
			(resident->rem_credits == 3)
		) {
			hi.score.cleared = SCOREDAT_CLEARED;
		}
	#endif

	scoredat_sum(sum, p, i);
	hi.sum = sum;

	// Encraption
	p = reinterpret_cast<uint8_t near *>(&hi.score.key1);
	p--;
	feedback = hi.score.key2;
	i = (sizeof(hi.score) - 1);
	while(i >= 0) {
		scoredat_encode_byte_at(p, feedback, hi.score.key1, hi.score.key2);
		i--;
		p--;
	}

	// Save
	file_append(SCOREDAT_FN);
	file_seek((rank * sizeof(scoredat_section_t)), SEEK_SET);
	file_write(&hi, sizeof(scoredat_section_t));
	file_close();
}

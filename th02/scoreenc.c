/* ReC98
 * -----
 * TH02 high score pre-save encoding
 */

#define SCOREDAT_ENCODE() \
	int i; \
	hi.score.score_sum = 0; \
	hi.score.g_name_first_sum = 0; \
	hi.score.stage_sum = 0; \
	hi.section_sum = 0; \
	for(i = 0; i < SCOREDAT_PLACES; i++) { \
		hi.score.score_sum += hi.score.score[i]; \
		hi.score.g_name_first_sum += hi.score.g_name[i][0]; \
		hi.score.stage_sum += hi.score.stage[i]; \
	} \
	for(i = 0; i < sizeof(hi.score); i++) { \
		hi.section_sum += *((uint8_t *)(&hi.score) + i); \
		*((uint8_t *)(&hi.score) + i) += 0x12; \
	}
